/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <proj.h>

/**************************************************************************************************/

int
main(int argc, char *argv[])
{
  // https://proj.org/development/quickstart.html
  // https://proj.org/development/reference/index.html

  // PJ *proj_create(PJ_CONTEXT *ctx, const char *definition)
  // PJ *proj_create_crs_to_crs(PJ_CONTEXT *ctx, const char *source_crs, const char *target_crs, PJ_AREA *area)
  // PJ *proj_create_crs_to_crs_from_pj(PJ_CONTEXT *ctx, PJ *source_crs, PJ *target_crs, PJ_AREA *area, const char *const *options)
  // int proj_trans_array(PJ *P, PJ_DIRECTION direction, size_t n, PJ_COORD *coord)
  // PJ_COORD proj_coord(double x, double y, double z, double t)

  // or you may set context=PJ_DEFAULT_CTX
  // if you are sure you will use PJ objects from only one thread
  PJ_CONTEXT * context = proj_context_create();

  PJ * transformation;

  transformation = proj_create_crs_to_crs(context,
                                          "EPSG:4326", // WGS 84 - World Geodetic System 1984, used in GPS
                                          "EPSG:3857", // WGS 84 / Pseudo-Mercator
                                          // "+proj=utm +zone=32 +datum=WGS84", // or EPSG:32632
                                          // an optional description of the area of use.
                                          NULL);
  if (transformation == NULL) {
    fprintf(stderr, "Failed to create transformation object.\n");
    return EXIT_FAILURE;
  }

  // 4326 "+proj=longlat +datum=WGS84 +no_defs"
  PJ * crs_4326 = proj_create(context, "EPSG:4326");
  // 3857 "+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +wktext +no_defs"
  PJ * crs_3857 = proj_create(context, "EPSG:3857");
  transformation = proj_create_crs_to_crs_from_pj(context, crs_4326, crs_3857, NULL,NULL);

  // For geographic CRS defined by the EPSG authority, the order of coordinates is latitude first, longitude second.
  // When using a PROJ string, the order is the reverse; longitude first, latitude second.

  // For projected CRS defined by the EPSG authority, and with EAST / NORTH directions,
  // the order might be easting first, northing second, or the reverse.
  // When using a PROJ string, the order will be easting first, northing second,
  // except if the +axis parameter modifies it.

  // This will ensure that the order of coordinates for the input CRS will be longitude, latitude,
  // whereas EPSG:4326 mandates latitude, longitude
  PJ * normalised_transformation = proj_normalize_for_visualization(context, transformation);
  if (normalised_transformation == NULL) {
    fprintf(stderr, "Failed to normalize transformation object.\n");
    return EXIT_FAILURE;
  }
  proj_destroy(transformation);
  transformation = normalised_transformation;

  // creates a coordinate for Paris
  //   latitude: 48.85°N longitude: 2.34°E
  //   web mercator: x=261_315 y=6_250_834 m
  //   https://epsg.io/transform#s_srs=4326&t_srs=3857&x=2.3515530&y=48.8559390
  double latitude  = 48.855939; // N
  double longitude =  2.351553; // E
  PJ_COORD coordinate_4326 = proj_coord(longitude, latitude, 0, 0); // using normalised_transformation
  // PJ_COORD coordinate_4326 = proj_coord(latitude, longitude, 0, 0);
  printf("longitude/easting: %.3f, latitude/northing: %.3f\n", coordinate_4326.enu.e, coordinate_4326.enu.n);
  PJ_COORD coordinate_3857 = proj_trans(transformation, PJ_FWD, coordinate_4326);
  printf("x: %.3f, y: %.3f\n", coordinate_3857.xy.x, coordinate_3857.xy.y);
  // longitude/easting: 2.352, latitude/northing: 48.856
  // x: 261773.683, y: 6250452.514

  proj_destroy(transformation);
  proj_context_destroy(context); // may be omitted in the single threaded case

  return EXIT_SUCCESS;
}
