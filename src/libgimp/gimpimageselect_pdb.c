/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpimageselect_pdb.c
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* NOTE: This file is auto-generated by pdbgen.pl */

#include "config.h"

#include "gimp.h"


/**
 * SECTION: gimpimageselect
 * @title: gimpimageselect
 * @short_description: Modify the image's selection.
 *
 * Functions to modify the image's selection.
 **/


/**
 * gimp_image_select_color:
 * @image_ID: The affected image.
 * @operation: The selection operation.
 * @drawable_ID: The affected drawable.
 * @color: The color to select.
 *
 * Create a selection by selecting all pixels (in the specified
 * drawable) with the same (or similar) color to that specified.
 *
 * This tool creates a selection over the specified image. A by-color
 * selection is determined by the supplied color under the constraints
 * of the current context settings. Essentially, all pixels (in the
 * drawable) that have color sufficiently close to the specified color
 * (as determined by the threshold and criterion context values) are
 * included in the selection. To select transparent regions, the color
 * specified must also have minimum alpha. This procedure is affected
 * by the following context setters: gimp_context_set_antialias(),
 * gimp_context_set_feather(), gimp_context_set_feather_radius(),
 * gimp_context_set_sample_merged(),
 * gimp_context_set_sample_criterion(),
 * gimp_context_set_sample_threshold(),
 * gimp_context_set_sample_transparent(). In the case of a merged
 * sampling, the supplied drawable is ignored.
 *
 * Returns: TRUE on success.
 *
 * Since: GIMP 2.8
 **/
gboolean
gimp_image_select_color (gint32          image_ID,
                         GimpChannelOps  operation,
                         gint32          drawable_ID,
                         const GimpRGB  *color)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-select-color",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_INT32, operation,
                                    GIMP_PDB_DRAWABLE, drawable_ID,
                                    GIMP_PDB_COLOR, color,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_select_contiguous_color:
 * @image_ID: The affected image.
 * @operation: The selection operation.
 * @drawable_ID: The affected drawable.
 * @x: x coordinate of initial seed fill point: (image coordinates).
 * @y: y coordinate of initial seed fill point: (image coordinates).
 *
 * Create a selection by selecting all pixels around specified
 * coordinates with the same (or similar) color to that at the
 * coordinates.
 *
 * This tool creates a contiguous selection over the specified image. A
 * contiguous color selection is determined by a seed fill under the
 * constraints of the current context settings. Essentially, the color
 * at the specified coordinates (in the drawable) is measured and the
 * selection expands outwards from that point to any adjacent pixels
 * which are not significantly different (as determined by the
 * threshold and criterion context settings). This process continues
 * until no more expansion is possible. If antialiasing is turned on,
 * the final selection mask will contain intermediate values based on
 * close misses to the threshold bar at pixels along the seed fill
 * boundary. This procedure is affected by the following context
 * setters: gimp_context_set_antialias(), gimp_context_set_feather(),
 * gimp_context_set_feather_radius(), gimp_context_set_sample_merged(),
 * gimp_context_set_sample_criterion(),
 * gimp_context_set_sample_threshold(),
 * gimp_context_set_sample_transparent(). In the case of a merged
 * sampling, the supplied drawable is ignored. If the sample is merged,
 * the specified coordinates are relative to the image origin;
 * otherwise, they are relative to the drawable's origin.
 *
 * Returns: TRUE on success.
 *
 * Since: GIMP 2.8
 **/
gboolean
gimp_image_select_contiguous_color (gint32         image_ID,
                                    GimpChannelOps operation,
                                    gint32         drawable_ID,
                                    gdouble        x,
                                    gdouble        y)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-select-contiguous-color",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_INT32, operation,
                                    GIMP_PDB_DRAWABLE, drawable_ID,
                                    GIMP_PDB_FLOAT, x,
                                    GIMP_PDB_FLOAT, y,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_select_rectangle:
 * @image_ID: The image.
 * @operation: The selection operation.
 * @x: x coordinate of upper-left corner of rectangle.
 * @y: y coordinate of upper-left corner of rectangle.
 * @width: The width of the rectangle.
 * @height: The height of the rectangle.
 *
 * Create a rectangular selection over the specified image;
 *
 * This tool creates a rectangular selection over the specified image.
 * The rectangular region can be either added to, subtracted from, or
 * replace the contents of the previous selection mask. This procedure
 * is affected by the following context setters:
 * gimp_context_set_feather(), gimp_context_set_feather_radius().
 *
 * Returns: TRUE on success.
 *
 * Since: GIMP 2.8
 **/
gboolean
gimp_image_select_rectangle (gint32         image_ID,
                             GimpChannelOps operation,
                             gdouble        x,
                             gdouble        y,
                             gdouble        width,
                             gdouble        height)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-select-rectangle",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_INT32, operation,
                                    GIMP_PDB_FLOAT, x,
                                    GIMP_PDB_FLOAT, y,
                                    GIMP_PDB_FLOAT, width,
                                    GIMP_PDB_FLOAT, height,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_select_round_rectangle:
 * @image_ID: The image.
 * @operation: The selection operation.
 * @x: x coordinate of upper-left corner of rectangle.
 * @y: y coordinate of upper-left corner of rectangle.
 * @width: The width of the rectangle.
 * @height: The height of the rectangle.
 * @corner_radius_x: The corner radius in X direction.
 * @corner_radius_y: The corner radius in Y direction.
 *
 * Create a rectangular selection with round corners over the specified
 * image;
 *
 * This tool creates a rectangular selection with round corners over
 * the specified image. The rectangular region can be either added to,
 * subtracted from, or replace the contents of the previous selection
 * mask. This procedure is affected by the following context setters:
 * gimp_context_set_antialias(), gimp_context_set_feather(),
 * gimp_context_set_feather_radius().
 *
 * Returns: TRUE on success.
 *
 * Since: GIMP 2.8
 **/
gboolean
gimp_image_select_round_rectangle (gint32         image_ID,
                                   GimpChannelOps operation,
                                   gdouble        x,
                                   gdouble        y,
                                   gdouble        width,
                                   gdouble        height,
                                   gdouble        corner_radius_x,
                                   gdouble        corner_radius_y)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-select-round-rectangle",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_INT32, operation,
                                    GIMP_PDB_FLOAT, x,
                                    GIMP_PDB_FLOAT, y,
                                    GIMP_PDB_FLOAT, width,
                                    GIMP_PDB_FLOAT, height,
                                    GIMP_PDB_FLOAT, corner_radius_x,
                                    GIMP_PDB_FLOAT, corner_radius_y,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_select_ellipse:
 * @image_ID: The image.
 * @operation: The selection operation.
 * @x: x coordinate of upper-left corner of ellipse bounding box.
 * @y: y coordinate of upper-left corner of ellipse bounding box.
 * @width: The width of the ellipse.
 * @height: The height of the ellipse.
 *
 * Create an elliptical selection over the specified image.
 *
 * This tool creates an elliptical selection over the specified image.
 * The elliptical region can be either added to, subtracted from, or
 * replace the contents of the previous selection mask. This procedure
 * is affected by the following context setters:
 * gimp_context_set_antialias(), gimp_context_set_feather(),
 * gimp_context_set_feather_radius().
 *
 * Returns: TRUE on success.
 *
 * Since: GIMP 2.8
 **/
gboolean
gimp_image_select_ellipse (gint32         image_ID,
                           GimpChannelOps operation,
                           gdouble        x,
                           gdouble        y,
                           gdouble        width,
                           gdouble        height)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-select-ellipse",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_INT32, operation,
                                    GIMP_PDB_FLOAT, x,
                                    GIMP_PDB_FLOAT, y,
                                    GIMP_PDB_FLOAT, width,
                                    GIMP_PDB_FLOAT, height,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_select_polygon:
 * @image_ID: The image.
 * @operation: The selection operation.
 * @num_segs: Number of points (count 1 coordinate as two points).
 * @segs: Array of points: { p1.x, p1.y, p2.x, p2.y, ..., pn.x, pn.y}.
 *
 * Create a polygonal selection over the specified image.
 *
 * This tool creates a polygonal selection over the specified image.
 * The polygonal region can be either added to, subtracted from, or
 * replace the contents of the previous selection mask. The polygon is
 * specified through an array of floating point numbers and its length.
 * The length of array must be 2n, where n is the number of points.
 * Each point is defined by 2 floating point values which correspond to
 * the x and y coordinates. If the final point does not connect to the
 * starting point, a connecting segment is automatically added. This
 * procedure is affected by the following context setters:
 * gimp_context_set_antialias(), gimp_context_set_feather(),
 * gimp_context_set_feather_radius().
 *
 * Returns: TRUE on success.
 *
 * Since: GIMP 2.8
 **/
gboolean
gimp_image_select_polygon (gint32          image_ID,
                           GimpChannelOps  operation,
                           gint            num_segs,
                           const gdouble  *segs)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-select-polygon",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_INT32, operation,
                                    GIMP_PDB_INT32, num_segs,
                                    GIMP_PDB_FLOATARRAY, segs,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_image_select_item:
 * @image_ID: The image.
 * @operation: The desired operation with current selection.
 * @item_ID: The item to render to the selection.
 *
 * Transforms the specified item into a selection
 *
 * This procedure renders the item's outline into the current selection
 * of the image the item belongs to. What exactly the item's outline is
 * depends on the item type: for layers, it's the layer's alpha
 * channel, for vectors the vector's shape. This procedure is affected
 * by the following context setters: gimp_context_set_antialias(),
 * gimp_context_set_feather(), gimp_context_set_feather_radius().
 *
 * Returns: TRUE on success.
 *
 * Since: GIMP 2.8
 **/
gboolean
gimp_image_select_item (gint32         image_ID,
                        GimpChannelOps operation,
                        gint32         item_ID)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-image-select-item",
                                    &nreturn_vals,
                                    GIMP_PDB_IMAGE, image_ID,
                                    GIMP_PDB_INT32, operation,
                                    GIMP_PDB_ITEM, item_ID,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}
