/* serenity-runtime.h
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

#if !defined (__SERENE_INSIDE__) && !defined (SERENE_COMPILATION)
#error "Only <serenity/serenity.h> can be included directly."
#endif

#ifndef __SERENITY_RUNTIME_H__
#define __SERENITY_RUNTIME_H__

#include <glib-object.h>

#include "serenity-document.h"

G_BEGIN_DECLS

gboolean serenity_runtime_initialize    (gint     *argc,
                                         gchar  ***argv,
                                         GError  **error);
void     serenity_runtime_shutdown      (void);
void     serenity_runtime_run           (void);
void     serenity_runtime_quit          (void);
GList*   serenity_runtime_get_windows   (void);
void     serenity_runtime_show_document (SerenityDocument *document);

G_END_DECLS

#endif /* __SERENITY_RUNTIME_H__ */
