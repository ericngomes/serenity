/* serenity-paths.c
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

#include "serenity-paths.h"

/**
 * serenity_paths_get_data_dir:
 *
 * Retrieves the directory containing data information for the application.
 *
 * Return value: a string containing the data directory.  This value should
 *   not be modified or freed.
 */
const gchar *
serenity_paths_get_data_dir (void)
{
	const gchar *data_dir = NULL;

	if (G_UNLIKELY (!data_dir)) {
#ifndef G_OS_WIN32
		gchar *root = (gchar*)g_getenv ("SERENITY_DATA_PATH");
		if (!root)
			root = PACKAGE_DATA_DIR;
		data_dir = g_build_filename (root, "serenity", NULL);
#else
		gchar *win32_dir;

		win32_dir = g_win32_get_package_installation_directory_of_module (NULL);
		data_dir = g_build_filename (win32_dir, "share", "serenity", NULL);

		g_free (win32_dir);
#endif
	}

	return data_dir;
}

const gchar *
serenity_dirs_get_locale_dir (void)
{
	static gchar *locale_dir = NULL;

	if (!G_UNLIKELY (locale_dir)) {
#ifndef G_OS_WIN32
		locale_dir = g_build_filename (PACKAGE_DATA_DIR, "locale", NULL);
#else
		gchar *win32_dir;

		win32_dir = g_win32_get_package_installation_directory_of_module (NULL);
		locale_dir = g_build_filename (win32_dir, "share", "locale", NULL);
		g_free (win32_dir);
#endif
	}

	return locale_dir;
}