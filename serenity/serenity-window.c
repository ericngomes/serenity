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

#include "serenity-paths.h"
#include "serenity-window.h"

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
	GtkWidget *child;
	gchar *path;

	window->priv = G_TYPE_INSTANCE_GET_PRIVATE(window,
	                                           SERENITY_TYPE_WINDOW,
	                                           SerenityWindowPrivate);

	gtk_window_set_title(GTK_WINDOW(window), _("Serenity"));
	gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

	path = serenity_paths_build_data_path("ui", "serenity.ui", NULL);
	window->priv->builder = gtk_builder_new();
	gtk_builder_add_from_file(window->priv->builder, path, NULL);
	g_free(path);

	child = GTK_WIDGET(gtk_builder_get_object(window->priv->builder,
	                                          "window-child"));
	g_assert(child);
	gtk_widget_reparent(child, GTK_WIDGET(window));
}
