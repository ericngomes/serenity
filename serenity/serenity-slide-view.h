/* serenity-slide-view.h
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

#ifndef __SERENITY_SLIDE_VIEW_H__
#define __SERENITY_SLIDE_VIEW_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define SERENITY_TYPE_SLIDE_VIEW            (serenity_slide_view_get_type())
#define SERENITY_SLIDE_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), SERENITY_TYPE_SLIDE_VIEW, SerenitySlideView))
#define SERENITY_SLIDE_VIEW_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), SERENITY_TYPE_SLIDE_VIEW, SerenitySlideView const))
#define SERENITY_SLIDE_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  SERENITY_TYPE_SLIDE_VIEW, SerenitySlideViewClass))
#define SERENITY_IS_SLIDE_VIEW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SERENITY_TYPE_SLIDE_VIEW))
#define SERENITY_IS_SLIDE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  SERENITY_TYPE_SLIDE_VIEW))
#define SERENITY_SLIDE_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  SERENITY_TYPE_SLIDE_VIEW, SerenitySlideViewClass))

typedef struct _SerenitySlideView        SerenitySlideView;
typedef struct _SerenitySlideViewClass   SerenitySlideViewClass;
typedef struct _SerenitySlideViewPrivate SerenitySlideViewPrivate;

struct _SerenitySlideView
{
	GObject parent;

	/*< private >*/
	SerenitySlideViewPrivate *priv;
};

struct _SerenitySlideViewClass
{
	GObjectClass parent_class;
};

GType serenity_slide_view_get_type (void) G_GNUC_CONST;
SerenitySlideView *serenity_slide_view_new      (void);

G_END_DECLS

#endif /* __SERENITY_SLIDE_VIEW_H__ */
