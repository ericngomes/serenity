/* serenity-runtime.c
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

#include <stdlib.h>
#include <gtk/gtk.h>

#include "serenity-panels.h"
#include "serenity-prefs.h"
#include "serenity-runtime.h"
#include "serenity-window.h"

/**
 * SECTION:serenity-runtime
 * @title: Serenity
 * @short_description: runtime helpers for serenity
 *
 * 
 */

static GList    *windows = NULL;
static gboolean  started = FALSE;

/**
 * serenity_runtime_initialize:
 *
 * Initializes the runtime system.
 */
gboolean
serenity_runtime_initialize (gint     *argc,
                             gchar  ***argv,
                             GError  **error)
{
	if (!serenity_prefs_init(argc, argv, error)) {
		return FALSE;
	}

	serenity_panels_init();

	started = TRUE;
}

/**
 * serenity_runtime_run:
 *
 * Starts the runtime system.  This method will block using a main loop for the
 * duration of applications life-time.
 */
void
serenity_runtime_run (void)
{
	gtk_main();
}

/**
 * serenity_runtime_quit:
 *
 * Stops the runtime system and gracefully shuts down the application.
 */
void
serenity_runtime_quit (void)
{
	if (!started) {
		exit(EXIT_FAILURE);
	}

	gtk_main_quit();
}

/**
 * serenity_runtime_shutdown:
 *
 * Gracefully cleans up after the runtime.  This should be called in the
 * main thread after the runtim has quit.
 */
void
serenity_runtime_shutdown (void)
{
}

/**
 * serenity_runtime_get_windows:
 *
 * Retrieves a #GList containing the #SerenityWindow instances.
 *
 * Returns: A #GList.
 */
GList*
serenity_runtime_get_windows (void)
{
	return windows;
}

/**
 * serenity_runtime_show_document:
 * @document: A #SerenityDocument.
 *
 * Shows the #SerenityDocument in a new window.
 */
void
serenity_runtime_show_document (SerenityDocument *document)
{
	GtkWidget *window;

	/* TODO: Show existing window for document. */

	window = serenity_window_new();
	serenity_window_set_document(SERENITY_WINDOW(window), document);
	windows = g_list_prepend(windows, window);
	gtk_widget_show(window);
}
