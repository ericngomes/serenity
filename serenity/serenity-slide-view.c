/* serenity-slide-view.c
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

#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/clutter-gtk.h>

#include "serenity-slide_view.h"

G_DEFINE_TYPE(SerenitySlideView, serenity_slide_view, G_TYPE_OBJECT)

/**
 * SECTION:serenity-slide_view
 * @title: SerenitySlideView
 * @short_description: 
 *
 * 
 */

struct _SerenitySlideViewPrivate
{
    gpointer dummy;
};

/*
 *-----------------------------------------------------------------------------
 *
 * Public Methods
 *
 *-----------------------------------------------------------------------------
 */

/**
 * serenity_slide_view_new:
 *
 * Creates a new instance of #SerenitySlideView.
 *
 * Return value: the newly created #SerenitySlideView instance.
 */
SerenitySlideView*
serenity_slide_view_new (void)
{
	return g_object_new (SERENITY_TYPE_SLIDE_VIEW, NULL);
}

/*
 *-----------------------------------------------------------------------------
 *
 * Class Methods
 *
 *-----------------------------------------------------------------------------
 */

static void
serenity_slide_view_finalize (GObject *object)
{
	SerenitySlideViewPrivate *priv;

	g_return_if_fail (SERENITY_IS_SLIDE_VIEW (object));

	priv = SERENITY_SLIDE_VIEW (object)->priv;

	G_OBJECT_CLASS (serenity_slide_view_parent_class)->finalize (object);
}

static void
serenity_slide_view_class_init (SerenitySlideViewClass *klass)
{
	GObjectClass *object_class;

	object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = serenity_slide_view_finalize;
	g_type_class_add_private (object_class, sizeof (SerenitySlideViewPrivate));
}

static void
serenity_slide_view_init (SerenitySlideView *slide_view)
{
	slide_view->priv = G_TYPE_INSTANCE_GET_PRIVATE (slide_view,
	                                                SERENITY_TYPE_SLIDE_VIEW,
	                                                SerenitySlideViewPrivate);
}
