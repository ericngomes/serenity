/* serenity-document.c
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

#include "serenity-document.h"

G_DEFINE_TYPE(SerenityDocument, serenity_document, G_TYPE_OBJECT)

/**
 * SECTION:serenity-document
 * @title: SerenityDocument
 * @short_description: 
 *
 * 
 */

struct _SerenityDocumentPrivate
{
	GFile     *file;
	gint       width;
	gint       height;
	GPtrArray *slides;
};

enum
{
	SIZE_CHANGED,
	LAST_SIGNAL
};

static guint signals[LAST_SIGNAL] = {0};

/**
 * serenity_document_new:
 *
 * Creates a new instance of #SerenityDocument.
 *
 * Return value: the newly created #SerenityDocument instance.
 */
SerenityDocument*
serenity_document_new (void)
{
	return g_object_new (SERENITY_TYPE_DOCUMENT, NULL);
}

/**
 * serenity_document_load_from_file:
 * @document: A #SerenityDocument.
 * @file: A #GFile.
 * @error: A location for a #GError; or %NULL.
 *
 * Loads a #SerenityDocument from a #GFile.
 *
 * Returns: %TRUE if successful; otherwise %FALSE and @error is set.
 */
gboolean
serenity_document_load_from_file (SerenityDocument  *document,
                                  GFile             *file,
                                  GError           **error)
{
	SerenityDocumentPrivate *priv;

	g_return_val_if_fail(SERENITY_IS_DOCUMENT(document), FALSE);
	g_return_val_if_fail(G_IS_FILE(file), FALSE);

	priv = document->priv;

	priv->file = g_object_ref(file);

	return TRUE;
}

static void
serenity_document_finalize (GObject *object)
{
	G_OBJECT_CLASS(serenity_document_parent_class)->finalize(object);
}

static void
serenity_document_class_init (SerenityDocumentClass *klass)
{
	GObjectClass *object_class;

	object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = serenity_document_finalize;
	g_type_class_add_private(object_class, sizeof(SerenityDocumentPrivate));

	signals[SIZE_CHANGED] = g_signal_new("size-changed",
	                                     SERENITY_TYPE_DOCUMENT,
	                                     G_SIGNAL_RUN_FIRST,
	                                     0,
	                                     NULL,
	                                     NULL,
	                                     g_cclosure_marshal_VOID__VOID,
	                                     G_TYPE_NONE,
	                                     0);
}

static void
serenity_document_init (SerenityDocument *document)
{
	document->priv = G_TYPE_INSTANCE_GET_PRIVATE(document,
	                                             SERENITY_TYPE_DOCUMENT,
	                                             SerenityDocumentPrivate);

	document->priv->width = 1024;
	document->priv->height = 768;
}
