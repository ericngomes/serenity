/* serenity.c
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
#include <glib/gthread.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "serenity-document.h"
#include "serenity-paths.h"
#include "serenity-prefs.h"
#include "serenity-runtime.h"

static gboolean
open_uri_cb (const gchar *uri)
{
	SerenityDocument *doc;
	GError *error = NULL;
	GFile *file;

	file = g_file_new_for_commandline_arg(uri);
	doc = serenity_document_new();

	if (!serenity_document_load_from_file(doc, file, &error)) {
		g_warning("Error loading \"%s\": %s.", uri, error->message);
		g_error_free(error);
		goto finish;
	}

	serenity_runtime_show_document(doc);

finish:
	g_object_unref(file);
	g_object_unref(doc);
	return FALSE;
}

gint
main (gint   argc,
      gchar *argv[])
{
	const gchar *data_dir = NULL;
	GError *error = NULL;
	gint i;

	/* initialize i18n */
	data_dir = PACKAGE_LOCALE_DIR;
	bindtextdomain(GETTEXT_PACKAGE, data_dir);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);

	/* initialize threading */
	g_thread_init(NULL);

	/* parse command line arguments */
	if (!serenity_prefs_init(&argc, &argv, &error)) {
		g_printerr ("%s\n", error->message);
		return EXIT_FAILURE;
	}

	/* initialize runtime */
	serenity_runtime_initialize();

	/* open requested documents after mainloop starts */
	for (i = 1; i < argc; i++) {
		g_timeout_add(0, (GSourceFunc)open_uri_cb, argv[i]);
	}

	/* block on mainloop */
	serenity_runtime_run();

	/* cleanup after runtime */
	serenity_runtime_shutdown();

	return EXIT_SUCCESS;
}
