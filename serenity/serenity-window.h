/* serenity-window.h
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

#ifndef __SERENITY_WINDOW_H__
#define __SERENITY_WINDOW_H__

#include <gtk/gtk.h>

#include "serenity-document.h"

G_BEGIN_DECLS

#define SERENITY_TYPE_WINDOW            (serenity_window_get_type())
#define SERENITY_WINDOW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), SERENITY_TYPE_WINDOW, SerenityWindow))
#define SERENITY_WINDOW_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), SERENITY_TYPE_WINDOW, SerenityWindow const))
#define SERENITY_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  SERENITY_TYPE_WINDOW, SerenityWindowClass))
#define SERENITY_IS_WINDOW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SERENITY_TYPE_WINDOW))
#define SERENITY_IS_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  SERENITY_TYPE_WINDOW))
#define SERENITY_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  SERENITY_TYPE_WINDOW, SerenityWindowClass))

typedef struct _SerenityWindow        SerenityWindow;
typedef struct _SerenityWindowClass   SerenityWindowClass;
typedef struct _SerenityWindowPrivate SerenityWindowPrivate;

struct _SerenityWindow
{
	GtkWindow parent;

	/*< private >*/
	SerenityWindowPrivate *priv;
};

struct _SerenityWindowClass
{
	GtkWindowClass parent_class;
};

GType             serenity_window_get_type     (void) G_GNUC_CONST;
GtkWidget*        serenity_window_new          (void);
void              serenity_window_set_document (SerenityWindow   *window,
                                                SerenityDocument *document);
SerenityDocument* serenity_window_get_document (SerenityWindow   *window);

G_END_DECLS

#endif /* __SERENITY_WINDOW_H__ */
