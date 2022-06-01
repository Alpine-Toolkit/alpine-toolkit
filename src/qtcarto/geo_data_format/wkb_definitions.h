struct Point {
  double x;
  double y;
};

struct LinearRing {
  uint32_t number_of_points;
  Point points[number_of_points];
};

struct WkbPoint {
  char byte_order;
  uint32_t wkb_type; // 1
  Point point;
};

struct WkbLineString {
  uint8_t byte_order;
  uint32_t wkb_type; // 2
  uint32_t number_of_points;
  Point points[number_of_points];
};

struct WkbPolygon {
  uint8_t byte_order;
  uint32_t wkb_type; // 3
  uint32_t number_of_rings;
  LinearRing rings[number_of_rings];
};

struct WkbMultiPoint {
  uint8_t byte_order;
  uint32_t wkb_type; // 4
  uint32_t number_of_points;
  WkbPoint WkbPoints[number_of_points];
};

struct WkbMultiLineString {
  uint8_t byte_order;
  uint32_t wkb_type; // 5
  uint32_t number_of_line_strings;
  WkbLineString WkbLineStrings[number_of_line_strings];
};

struct wkbMultiPolygon {
  uint8_t byte_order;
  uint32_t wkb_type; // 6
  uint32_t number_of_polygons;
  WkbPolygon wkbPolygons[number_of_polygons];
};

WkbGeometry {
  union {
    WkbPoint point;
    WkbLineString line_string;
    WkbPolygon polygon;
    WkbGeometryCollection collection;
    WkbMultiPoint multi_point;
    WkbMultiLineString multi_line_string;
    WkbMultiPolygon multi_polygon;
  }
};

struct WkbGeometryCollection {
  uint8_t byte_order;
  uint32_t wkb_type; // 7
  uint32_t number_of_geometries;
  WkbGeometry geometries[number_of_geometries]
};
