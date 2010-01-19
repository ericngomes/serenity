/* serenity-document.h
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

#ifndef __SERENITY_DOCUMENT_H__
#define __SERENITY_DOCUMENT_H__

#include <gio/gio.h>

G_BEGIN_DECLS

#define SERENITY_TYPE_DOCUMENT            (serenity_document_get_type())
#define SERENITY_DOCUMENT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), SERENITY_TYPE_DOCUMENT, SerenityDocument))
#define SERENITY_DOCUMENT_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), SERENITY_TYPE_DOCUMENT, SerenityDocument const))
#define SERENITY_DOCUMENT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  SERENITY_TYPE_DOCUMENT, SerenityDocumentClass))
#define SERENITY_IS_DOCUMENT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SERENITY_TYPE_DOCUMENT))
#define SERENITY_IS_DOCUMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  SERENITY_TYPE_DOCUMENT))
#define SERENITY_DOCUMENT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  SERENITY_TYPE_DOCUMENT, SerenityDocumentClass))

typedef struct _SerenityDocument        SerenityDocument;
typedef struct _SerenityDocumentClass   SerenityDocumentClass;
typedef struct _SerenityDocumentPrivate SerenityDocumentPrivate;

struct _SerenityDocument
{
	GObject parent;

	/*< private >*/
	SerenityDocumentPrivate *priv;
};

struct _SerenityDocumentClass
{
	GObjectClass parent_class;
};

GType             serenity_document_get_type       (void) G_GNUC_CONST;
SerenityDocument* serenity_document_new            (void);
gboolean          serenity_document_load_from_file (SerenityDocument  *document,
                                                    GFile             *file,
                                                    GError           **error);

G_END_DECLS

#endif /* __SERENITY_DOCUMENT_H__ */
