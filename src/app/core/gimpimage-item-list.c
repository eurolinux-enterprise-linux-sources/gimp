/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

#include "config.h"

#include <gegl.h>

#include "core-types.h"

#include "gimpcontext.h"
#include "gimpimage.h"
#include "gimpimage-item-list.h"
#include "gimpimage-undo.h"
#include "gimpitem.h"
#include "gimpprogress.h"

#include "gimp-intl.h"


/*  public functions  */

void
gimp_image_item_list_translate (GimpImage *image,
                                GList     *list,
                                gint       offset_x,
                                gint       offset_y,
                                gboolean   push_undo)
{
  g_return_if_fail (GIMP_IS_IMAGE (image));

  if (list)
    {
      GList *l;

      if (push_undo)
        gimp_image_undo_group_start (image, GIMP_UNDO_GROUP_ITEM_DISPLACE,
                                     C_("undo-type", "Translate Items"));

      for (l = list; l; l = g_list_next (l))
        gimp_item_translate (GIMP_ITEM (l->data),
                             offset_x, offset_y, push_undo);

      if (push_undo)
        gimp_image_undo_group_end (image);
    }
}

void
gimp_image_item_list_flip (GimpImage           *image,
                           GList               *list,
                           GimpContext         *context,
                           GimpOrientationType  flip_type,
                           gdouble              axis,
                           gboolean             clip_result)
{
  g_return_if_fail (GIMP_IS_IMAGE (image));
  g_return_if_fail (GIMP_IS_CONTEXT (context));

  if (list)
    {
      GList *l;

      gimp_image_undo_group_start (image, GIMP_UNDO_GROUP_TRANSFORM,
                                   C_("undo-type", "Flip Items"));

      for (l = list; l; l = g_list_next (l))
        gimp_item_flip (GIMP_ITEM (l->data), context,
                        flip_type, axis, clip_result);

      gimp_image_undo_group_end (image);
    }
}

void
gimp_image_item_list_rotate (GimpImage        *image,
                             GList            *list,
                             GimpContext      *context,
                             GimpRotationType  rotate_type,
                             gdouble           center_x,
                             gdouble           center_y,
                             gboolean          clip_result)
{
  g_return_if_fail (GIMP_IS_IMAGE (image));
  g_return_if_fail (GIMP_IS_CONTEXT (context));

  if (list)
    {
      GList *l;

      gimp_image_undo_group_start (image, GIMP_UNDO_GROUP_TRANSFORM,
                                   C_("undo-type", "Rotate Items"));

      for (l = list; l; l = g_list_next (l))
        gimp_item_rotate (GIMP_ITEM (l->data), context,
                          rotate_type, center_x, center_y, clip_result);

      gimp_image_undo_group_end (image);
    }
}

void
gimp_image_item_list_transform (GimpImage              *image,
                                GList                  *list,
                                GimpContext            *context,
                                const GimpMatrix3      *matrix,
                                GimpTransformDirection  direction,
                                GimpInterpolationType   interpolation_type,
                                gint                    recursion_level,
                                GimpTransformResize     clip_result,
                                GimpProgress           *progress)
{
  g_return_if_fail (GIMP_IS_IMAGE (image));
  g_return_if_fail (GIMP_IS_CONTEXT (context));
  g_return_if_fail (progress == NULL || GIMP_IS_PROGRESS (progress));

  if (list)
    {
      GList *l;

      gimp_image_undo_group_start (image, GIMP_UNDO_GROUP_TRANSFORM,
                                   C_("undo-type", "Transform Items"));

      for (l = list; l; l = g_list_next (l))
        gimp_item_transform (GIMP_ITEM (l->data), context,
                             matrix, direction,
                             interpolation_type, recursion_level,
                             clip_result, progress);

      gimp_image_undo_group_end (image);
    }
}

/**
 * gimp_image_item_list_get_list:
 * @image:   An @image.
 * @exclude: An item to exclude.
 * @type:    Which type of items to return.
 * @set:     Set the returned items are part of.
 *
 * This function returns a #GList of #GimpItem<!-- -->s for which the
 * @type and @set criterions match.
 *
 * Return value: The list of items, excluding @exclude.
 **/
GList *
gimp_image_item_list_get_list (const GimpImage  *image,
                               const GimpItem   *exclude,
                               GimpItemTypeMask  type,
                               GimpItemSet       set)
{
  GList *all_items;
  GList *list;
  GList *return_list = NULL;

  g_return_val_if_fail (GIMP_IS_IMAGE (image), NULL);
  g_return_val_if_fail (exclude == NULL || GIMP_IS_ITEM (exclude), NULL);

  if (type & GIMP_ITEM_TYPE_LAYERS)
    {
      all_items = gimp_image_get_layer_list (image);

      for (list = all_items; list; list = g_list_next (list))
        {
          GimpItem *item = list->data;

          if (item != exclude && gimp_item_is_in_set (item, set))
            return_list = g_list_prepend (return_list, item);
        }

      g_list_free (all_items);
    }

  if (type & GIMP_ITEM_TYPE_CHANNELS)
    {
      all_items = gimp_image_get_channel_list (image);

      for (list = all_items; list; list = g_list_next (list))
        {
          GimpItem *item = list->data;

          if (item != exclude && gimp_item_is_in_set (item, set))
            return_list = g_list_prepend (return_list, item);
        }

      g_list_free (all_items);
    }

  if (type & GIMP_ITEM_TYPE_VECTORS)
    {
      all_items = gimp_image_get_vectors_list (image);

      for (list = all_items; list; list = g_list_next (list))
        {
          GimpItem *item = list->data;

          if (item != exclude && gimp_item_is_in_set (item, set))
            return_list = g_list_prepend (return_list, item);
        }

      g_list_free (all_items);
    }

  return g_list_reverse (return_list);
}

static GList *
gimp_image_item_list_remove_children (GList          *list,
                                      const GimpItem *parent)
{
  GList *l = list;

  while (l)
    {
      GimpItem *item = l->data;

      l = g_list_next (l);

      if (gimp_viewable_is_ancestor (GIMP_VIEWABLE (parent),
                                     GIMP_VIEWABLE (item)))
        {
          list = g_list_remove (list, item);
        }
    }

  return list;
}

GList *
gimp_image_item_list_filter (const GimpItem *exclude,
                             GList          *list,
                             gboolean        remove_children,
                             gboolean        remove_locked)
{
  GList *l;

  g_return_val_if_fail (exclude == NULL || GIMP_IS_ITEM (exclude), NULL);

  if (! list)
    return NULL;

  if (remove_children)
    {
      if (exclude)
        list = gimp_image_item_list_remove_children (list, exclude);

      for (l = list; l; l = g_list_next (l))
        {
          GimpItem *item = l->data;
          GList    *next;

          next = gimp_image_item_list_remove_children (g_list_next (l), item);

          l->next = next;
          if (next)
            next->prev = l;
        }
    }

  if (remove_locked)
    {
      l = list;

      while (l)
        {
          GimpItem *item = l->data;

          l = g_list_next (l);

          if (gimp_item_is_content_locked (item))
            list = g_list_remove (list, item);
        }
    }

  return list;
}
