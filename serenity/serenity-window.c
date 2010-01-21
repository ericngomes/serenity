/* serenity-window.c
 *
 * Copyright (C) 2010 Christian Hergert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib/gi18n.h>
#include <clutter-gtk/clutter-gtk.h>

#include "serenity-paths.h"
#include "serenity-window.h"
#include "serenity-runtime.h"

G_DEFINE_TYPE(SerenityWindow, serenity_window, GTK_TYPE_WINDOW)

/**
 * SECTION:serenity-window
 * @title: SerenityWindow
 * @short_description: 
 *
 * 
 */

struct _SerenityWindowPrivate
{
	SerenityDocument *document;
	GtkBuilder *builder;
	ClutterStage *stage;
};

/**
 * serenity_window_new:
 *
 * Creates a new instance of #SerenityWindow.
 *
 * Return value: the newly created #SerenityWindow instance.
 */
GtkWidget*
serenity_window_new (void)
{
	return g_object_new (SERENITY_TYPE_WINDOW, NULL);
}

static void
serenity_window_load_document (SerenityWindow   *window,
                               SerenityDocument *document)
{
	SerenityWindowPrivate *priv = window->priv;

	priv->document = g_object_ref(document);
}

static void
serenity_window_unload_document (SerenityWindow *window)
{
	SerenityWindowPrivate *priv = window->priv;

	if (priv->document) {
		/* TODO: Show save dialog if needs save. */
		g_object_unref(priv->document);
	}
}

/**
 * serenity_window_get_document:
 * @window: A #SerenityWindow
 *
 * Retrieves the #SerenityDocument displayed by the window.
 *
 * Return value: A #SerenityDocument.
 */
SerenityDocument*
serenity_window_get_document (SerenityWindow *window)
{
	g_return_val_if_fail(SERENITY_IS_WINDOW(window), NULL);
	return window->priv->document;
}

/**
 * serenity_window_set_document:
 * @window: A #SerenityWindow
 * @document: A #SerenityDocument
 *
 * Sets the current document for the window.
 */
void
serenity_window_set_document (SerenityWindow   *window,
                              SerenityDocument *document)
{
	SerenityWindowPrivate *priv;

	g_return_if_fail(SERENITY_IS_WINDOW(window));
	g_return_if_fail(SERENITY_IS_DOCUMENT(document));

	priv = window->priv;

	serenity_window_unload_document(window);
	serenity_window_load_document(window, document);
}

static gboolean
on_configure (GtkWidget *window,
              gpointer   user_data)
{
	GdkWindow *gdkwindow;

	gdkwindow = gtk_widget_get_window(window);
	if (gdk_window_get_state(gdkwindow) == GDK_WINDOW_STATE_MAXIMIZED) {
		gtk_window_fullscreen(GTK_WINDOW(window));
	}

	return FALSE;
}

void
serenity_window_close_button_pressed (ClutterActor *actor,
                                      ClutterEvent *event,
                                      gpointer      user_data)
{
	serenity_runtime_quit();
}

static void
serenity_window_finalize (GObject *object)
{
	G_OBJECT_CLASS(serenity_window_parent_class)->finalize(object);
}

static void
serenity_window_class_init (SerenityWindowClass *klass)
{
	GObjectClass *object_class;

	object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = serenity_window_finalize;
	g_type_class_add_private(object_class, sizeof(SerenityWindowPrivate));
}

static void
serenity_window_init (SerenityWindow *window)
{
	GtkWidget *embed;
	ClutterActor *stage, *toplevel;
	ClutterScript *script;
	ClutterColor black = {0x00, 0x00, 0x00, 0xFF};
	gchar *path;

	window->priv = G_TYPE_INSTANCE_GET_PRIVATE(window,
	                                           SERENITY_TYPE_WINDOW,
	                                           SerenityWindowPrivate);

	gtk_window_set_title(GTK_WINDOW(window), _("Serenity"));
	gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
	g_signal_connect(window,
	                 "configure-event",
	                 G_CALLBACK(on_configure),
	                 NULL);

	embed = gtk_clutter_embed_new();
	stage = gtk_clutter_embed_get_stage(GTK_CLUTTER_EMBED(embed));
	clutter_stage_set_color(CLUTTER_STAGE(stage), &black);
	gtk_container_add(GTK_CONTAINER(window), embed);
	gtk_widget_show(embed);

	path = serenity_paths_build_data_path("ui", "stage.ui", NULL);
	script = clutter_script_new();
	clutter_script_add_search_paths(script, (const gchar * const *)&path, 1);
	clutter_script_load_from_file(script, path, NULL);
	clutter_script_connect_signals(script, NULL);
	toplevel = CLUTTER_ACTOR(clutter_script_get_object(script, "toplevel"));
	clutter_container_add_actor(CLUTTER_CONTAINER(stage), toplevel);
	clutter_actor_show(toplevel);
	g_free(path);
}
