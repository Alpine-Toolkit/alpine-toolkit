# -*- CMake -*-

####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the QtCarto library.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# $ALPINE_TOOLKIT_END_LICENSE$
#
####################################################################################################

####################################################################################################

set(GEOS_SOURCE_PATH "geos-sources")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${GEOS_SOURCE_PATH}/cmake/modules" ${CMAKE_MODULE_PATH})

####################################################################################################

# GEOS release version
# GEOS C++ library SONAME will use these encoding ABI break at every release
set(VERSION_MAJOR 3)
set(VERSION_MINOR 6)
set(VERSION_PATCH 1)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# GEOS C API version
set(CAPI_INTERFACE_CURRENT 11)
set(CAPI_INTERFACE_REVISION 1)
set(CAPI_INTERFACE_AGE 10)

math(EXPR CAPI_VERSION_MAJOR "${CAPI_INTERFACE_CURRENT} - ${CAPI_INTERFACE_AGE}")
set(CAPI_VERSION_MINOR ${CAPI_INTERFACE_AGE})
set(CAPI_VERSION_PATCH ${CAPI_INTERFACE_REVISION})
set(CAPI_VERSION "${CAPI_VERSION_MAJOR}.${CAPI_VERSION_MINOR}.${CAPI_VERSION_PATCH}")
message(STATUS "Setting GEOS C API version ${CAPI_VERSION}")

####################################################################################################

option(GEOS_ENABLE_INLINE
  "Set to OFF|ON (default) to control GEOS compilation with small functions inlining" ON)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  option(GEOS_ENABLE_FLOATSTORE
    "Set to OFF|ON (default) to control IEEE754 conformance and remove extra precision" ON)
endif()

####################################################################################################

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # General options
  set(CMAKE_CXX_FLAGS "-pedantic -ansi ${CMAKE_CXX_FLAGS}")

  # Numerical stability
  if(GEOS_ENABLE_FLOATSTORE)
    # Remove extra precision by forcing conformance to IEEE 754 rather than IEEE 854
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffloat-store")
  endif()
  message(STATUS
    "Forcing IEEE 754 using flag -ffloat-store - ${GEOS_ENABLE_FLOATSTORE}")

  # Warnings specification
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long")

  # Turn on Position Independent Code generation for GEOS C shared library
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

  # Enable glibc ISO C99 features (macros isfinite, isnan)
  set(CMAKE_REQUIRED_DEFINITIONS "${CMAKE_REQUIRED_DEFINITIONS} -D_ISOC99_SOURCE=1")
endif()

if(GEOS_ENABLE_INLINE)
  add_definitions(-DGEOS_INLINE)
endif()
message(STATUS "Setting GEOS compilation with small functions inlining - ${GEOS_ENABLE_INLINE}")

####################################################################################################
#
# Setup C/C++ library features
#

# check header files
include(CheckIncludeFiles)

check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(ieeefp.h HAVE_IEEEFP_H)

# check types and sizes
include(CheckTypeSize)

if(HAVE_STDINT_H OR HAVE_INTTYPES_H)
  check_type_size("int64_t" HAVE_INT64_T_64)
else()
  check_type_size("long long int" HAVE_LONG_LONG_INT_64)
endif()

# check functions and macros
include(CheckPrototypeExists)
include(CheckSymbolExists)

check_prototype_exists(isnan cmath HAVE_STD_ISNAN)
if(NOT HAVE_STD_ISNAN)
  check_symbol_exists(isnan math.h HAVE_ISNAN)
endif()

check_prototype_exists(isfinite cmath HAVE_STD_ISFINITE)

if(NOT HAVE_STD_ISFINITE)
  #CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  check_symbol_exists(isfinite math.h HAVE_ISFINITE)
endif()

####################################################################################################

message(STATUS "Generating GEOS ${CMAKE_CURRENT_BINARY_DIR}/include/geos/platform.h")
configure_file(${GEOS_SOURCE_PATH}/include/geos/platform.h.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/include/geos/platform.h)

message(STATUS "Generating GEOS ${CMAKE_CURRENT_BINARY_DIR}/include/geos/version.h")
configure_file(${GEOS_SOURCE_PATH}/include/geos/version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/geos/version.h @ONLY)

message(STATUS "Generating GEOS ${CMAKE_CURRENT_BINARY_DIR}/capi/geos_c.h")
configure_file(${GEOS_SOURCE_PATH}/capi/geos_c.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/capi/geos_c.h @ONLY)

####################################################################################################

include_directories(${GEOS_SOURCE_PATH}/include)

# for including build-specific GEOS C API headers
include_directories(${CMAKE_CURRENT_BINARY_DIR}/capi)

# for including build-specific version.h, platform.h and geos_c.h
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

####################################################################################################

ADD_DEFINITIONS(
  -DHAVE_LONG_LONG_INT_64
  )

# capi
SET(GEOS_CAPI_SOURCES
  geos_c.cpp
  geos_ts_c.cpp
  )

# src
SET(GEOS_SOURCES
  algorithm/distance/DiscreteHausdorffDistance.cpp
  algorithm/distance/DistanceToPoint.cpp
  algorithm/locate/IndexedPointInAreaLocator.cpp
  algorithm/locate/PointOnGeometryLocator.cpp
  algorithm/locate/SimplePointInAreaLocator.cpp
  algorithm/Angle.cpp
  algorithm/BoundaryNodeRule.cpp
  algorithm/Centroid.cpp
  algorithm/CentroidArea.cpp
  algorithm/CentroidLine.cpp
  algorithm/CentroidPoint.cpp
  algorithm/CGAlgorithms.cpp
  algorithm/ConvexHull.cpp
  algorithm/HCoordinate.cpp
  algorithm/InteriorPointArea.cpp
  algorithm/InteriorPointLine.cpp
  algorithm/InteriorPointPoint.cpp
  algorithm/LineIntersector.cpp
  algorithm/MCPointInRing.cpp
  algorithm/MinimumDiameter.cpp
  algorithm/NotRepresentableException.cpp
  algorithm/PointLocator.cpp
  algorithm/RayCrossingCounter.cpp
  algorithm/RobustDeterminant.cpp
  algorithm/SimplePointInRing.cpp
  algorithm/SIRtreePointInRing.cpp
  geom/prep/AbstractPreparedPolygonContains.cpp
  geom/prep/BasicPreparedGeometry.cpp
  geom/prep/PreparedGeometry.cpp
  geom/prep/PreparedGeometryFactory.cpp
  geom/prep/PreparedLineString.cpp
  geom/prep/PreparedLineStringIntersects.cpp
  geom/prep/PreparedPoint.cpp
  geom/prep/PreparedPolygon.cpp
  geom/prep/PreparedPolygonContains.cpp
  geom/prep/PreparedPolygonContainsProperly.cpp
  geom/prep/PreparedPolygonCovers.cpp
  geom/prep/PreparedPolygonIntersects.cpp
  geom/prep/PreparedPolygonPredicate.cpp
  geom/util/ComponentCoordinateExtracter.cpp
  geom/util/CoordinateOperation.cpp
  geom/util/GeometryCombiner.cpp
  geom/util/GeometryEditor.cpp
  geom/util/GeometryTransformer.cpp
  geom/util/LinearComponentExtracter.cpp
  geom/util/PointExtracter.cpp
  geom/util/PolygonExtracter.cpp
  geom/util/ShortCircuitedGeometryVisitor.cpp
  geom/util/SineStarFactory.cpp
  geom/Coordinate.cpp
  geom/CoordinateArraySequence.cpp
  geom/CoordinateArraySequenceFactory.cpp
  geom/CoordinateSequence.cpp
  geom/CoordinateSequenceFactory.cpp
  geom/Dimension.cpp
  geom/Envelope.cpp
  geom/Geometry.cpp
  geom/GeometryCollection.cpp
  geom/GeometryComponentFilter.cpp
  geom/GeometryFactory.cpp
  geom/GeometryList.cpp
  geom/IntersectionMatrix.cpp
  geom/LinearRing.cpp
  geom/LineSegment.cpp
  geom/LineString.cpp
  geom/Location.cpp
  geom/MultiLineString.cpp
  geom/MultiPoint.cpp
  geom/MultiPolygon.cpp
  geom/Point.cpp
  geom/Polygon.cpp
  geom/PrecisionModel.cpp
  geom/Triangle.cpp
  geomgraph/index/MonotoneChainEdge.cpp
  geomgraph/index/MonotoneChainIndexer.cpp
  geomgraph/index/SegmentIntersector.cpp
  geomgraph/index/SimpleEdgeSetIntersector.cpp
  geomgraph/index/SimpleMCSweepLineIntersector.cpp
  geomgraph/index/SimpleSweepLineIntersector.cpp
  geomgraph/index/SweepLineEvent.cpp
  geomgraph/index/SweepLineSegment.cpp
  geomgraph/Depth.cpp
  geomgraph/DirectedEdge.cpp
  geomgraph/DirectedEdgeStar.cpp
  geomgraph/Edge.cpp
  geomgraph/EdgeEnd.cpp
  geomgraph/EdgeEndStar.cpp
  geomgraph/EdgeIntersectionList.cpp
  geomgraph/EdgeList.cpp
  geomgraph/EdgeNodingValidator.cpp
  geomgraph/EdgeRing.cpp
  geomgraph/GeometryGraph.cpp
  geomgraph/GraphComponent.cpp
  geomgraph/Label.cpp
  geomgraph/Node.cpp
  geomgraph/NodeFactory.cpp
  geomgraph/NodeMap.cpp
  geomgraph/PlanarGraph.cpp
  geomgraph/Position.cpp
  geomgraph/Quadrant.cpp
  geomgraph/TopologyLocation.cpp
  index/bintree/Bintree.cpp
  index/bintree/Interval.cpp
  index/bintree/Key.cpp
  index/bintree/Node.cpp
  index/bintree/NodeBase.cpp
  index/bintree/Root.cpp
  index/chain/MonotoneChainBuilder.cpp
  index/chain/MonotoneChain.cpp
  index/chain/MonotoneChainOverlapAction.cpp
  index/chain/MonotoneChainSelectAction.cpp
  index/intervalrtree/IntervalRTreeBranchNode.cpp
  index/intervalrtree/IntervalRTreeLeafNode.cpp
  index/intervalrtree/IntervalRTreeNode.cpp
  index/intervalrtree/SortedPackedIntervalRTree.cpp
  index/quadtree/DoubleBits.cpp
  index/quadtree/IntervalSize.cpp
  index/quadtree/Key.cpp
  index/quadtree/NodeBase.cpp
  index/quadtree/Node.cpp
  index/quadtree/Quadtree.cpp
  index/quadtree/Root.cpp
  index/strtree/AbstractNode.cpp
  index/strtree/AbstractSTRtree.cpp
  index/strtree/BoundablePair.cpp
  index/strtree/GeometryItemDistance.cpp
  index/strtree/Interval.cpp
  index/strtree/ItemBoundable.cpp
  index/strtree/SIRtree.cpp
  index/strtree/STRtree.cpp
  index/sweepline/SweepLineEvent.cpp
  index/sweepline/SweepLineIndex.cpp
  index/sweepline/SweepLineInterval.cpp
  io/ByteOrderDataInStream.cpp
  io/ByteOrderValues.cpp
  io/CLocalizer.cpp
  io/ParseException.cpp
  io/StringTokenizer.cpp
  io/Unload.cpp
  io/WKBReader.cpp
  io/WKBWriter.cpp
  io/WKTReader.cpp
  io/WKTWriter.cpp
  io/Writer.cpp
  linearref/ExtractLineByLocation.cpp
  linearref/LengthIndexedLine.cpp
  linearref/LengthIndexOfPoint.cpp
  linearref/LengthLocationMap.cpp
  linearref/LinearGeometryBuilder.cpp
  linearref/LinearIterator.cpp
  linearref/LinearLocation.cpp
  linearref/LocationIndexOfLine.cpp
  linearref/LocationIndexOfPoint.cpp
  noding/snapround/HotPixel.cpp
  noding/snapround/MCIndexPointSnapper.cpp
  noding/snapround/MCIndexSnapRounder.cpp
  noding/snapround/SimpleSnapRounder.cpp
  noding/BasicSegmentString.cpp
  noding/FastNodingValidator.cpp
  noding/FastSegmentSetIntersectionFinder.cpp
  noding/GeometryNoder.cpp
  noding/IntersectionAdder.cpp
  noding/IntersectionFinderAdder.cpp
  noding/IteratedNoder.cpp
  noding/MCIndexNoder.cpp
  noding/MCIndexSegmentSetMutualIntersector.cpp
  noding/NodedSegmentString.cpp
  noding/NodingValidator.cpp
  noding/Octant.cpp
  noding/OrientedCoordinateArray.cpp
  noding/ScaledNoder.cpp
  noding/SegmentIntersectionDetector.cpp
  noding/SegmentNode.cpp
  noding/SegmentNodeList.cpp
  noding/SegmentString.cpp
  noding/SegmentStringUtil.cpp
  noding/SimpleNoder.cpp
  noding/SingleInteriorIntersectionFinder.cpp
  operation/buffer/BufferBuilder.cpp
  operation/buffer/BufferInputLineSimplifier.cpp
  operation/buffer/BufferOp.cpp
  operation/buffer/BufferParameters.cpp
  operation/buffer/BufferSubgraph.cpp
  operation/buffer/OffsetCurveBuilder.cpp
  operation/buffer/OffsetCurveSetBuilder.cpp
  operation/buffer/OffsetSegmentGenerator.cpp
  operation/buffer/RightmostEdgeFinder.cpp
  operation/buffer/SubgraphDepthLocater.cpp
  operation/distance/ConnectedElementLocationFilter.cpp
  operation/distance/ConnectedElementPointFilter.cpp
  operation/distance/DistanceOp.cpp
  operation/distance/FacetSequence.cpp
  operation/distance/FacetSequenceTreeBuilder.cpp
  operation/distance/GeometryLocation.cpp
  operation/intersection/Rectangle.cpp
  operation/intersection/RectangleIntersection.cpp
  operation/intersection/RectangleIntersectionBuilder.cpp
  operation/linemerge/EdgeString.cpp
  operation/linemerge/LineMergeDirectedEdge.cpp
  operation/linemerge/LineMergeEdge.cpp
  operation/linemerge/LineMergeGraph.cpp
  operation/linemerge/LineMerger.cpp
  operation/linemerge/LineSequencer.cpp
  operation/overlay/snap/GeometrySnapper.cpp
  operation/overlay/snap/LineStringSnapper.cpp
  operation/overlay/snap/SnapIfNeededOverlayOp.cpp
  operation/overlay/snap/SnapOverlayOp.cpp
  operation/overlay/validate/FuzzyPointLocator.cpp
  operation/overlay/validate/OffsetPointGenerator.cpp
  operation/overlay/validate/OverlayResultValidator.cpp
  operation/overlay/EdgeSetNoder.cpp
  operation/overlay/ElevationMatrixCell.cpp
  operation/overlay/ElevationMatrix.cpp
  operation/overlay/LineBuilder.cpp
  operation/overlay/MaximalEdgeRing.cpp
  operation/overlay/MinimalEdgeRing.cpp
  operation/overlay/OverlayNodeFactory.cpp
  operation/overlay/OverlayOp.cpp
  operation/overlay/PointBuilder.cpp
  operation/overlay/PolygonBuilder.cpp
  operation/polygonize/EdgeRing.cpp
  operation/polygonize/PolygonizeDirectedEdge.cpp
  operation/polygonize/PolygonizeEdge.cpp
  operation/polygonize/PolygonizeGraph.cpp
  operation/polygonize/Polygonizer.cpp
  operation/predicate/RectangleContains.cpp
  operation/predicate/RectangleIntersects.cpp
  operation/predicate/SegmentIntersectionTester.cpp
  operation/relate/EdgeEndBuilder.cpp
  operation/relate/EdgeEndBundle.cpp
  operation/relate/EdgeEndBundleStar.cpp
  operation/relate/RelateComputer.cpp
  operation/relate/RelateNode.cpp
  operation/relate/RelateNodeFactory.cpp
  operation/relate/RelateNodeGraph.cpp
  operation/relate/RelateOp.cpp
  operation/sharedpaths/SharedPathsOp.cpp
  operation/union/CascadedPolygonUnion.cpp
  operation/union/CascadedUnion.cpp
  operation/union/PointGeometryUnion.cpp
  operation/union/UnaryUnionOp.cpp
  operation/valid/ConnectedInteriorTester.cpp
  operation/valid/ConsistentAreaTester.cpp
  operation/valid/IndexedNestedRingTester.cpp
  operation/valid/IsValidOp.cpp
  operation/valid/QuadtreeNestedRingTester.cpp
  operation/valid/RepeatedPointTester.cpp
  operation/valid/SimpleNestedRingTester.cpp
  operation/valid/SweeplineNestedRingTester.cpp
  operation/valid/TopologyValidationError.cpp
  operation/GeometryGraphOperation.cpp
  operation/IsSimpleOp.cpp
  planargraph/algorithm/ConnectedSubgraphFinder.cpp
  planargraph/DirectedEdge.cpp
  planargraph/DirectedEdgeStar.cpp
  planargraph/Edge.cpp
  planargraph/Node.cpp
  planargraph/NodeMap.cpp
  planargraph/PlanarGraph.cpp
  planargraph/Subgraph.cpp
  precision/CommonBits.cpp
  precision/CommonBitsOp.cpp
  precision/CommonBitsRemover.cpp
  precision/EnhancedPrecisionOp.cpp
  precision/GeometryPrecisionReducer.cpp
  precision/MinimumClearance.cpp
  precision/PrecisionReducerCoordinateOperation.cpp
  precision/SimpleGeometryPrecisionReducer.cpp
  simplify/DouglasPeuckerLineSimplifier.cpp
  simplify/DouglasPeuckerSimplifier.cpp
  simplify/LineSegmentIndex.cpp
  simplify/TaggedLineSegment.cpp
  simplify/TaggedLinesSimplifier.cpp
  simplify/TaggedLineString.cpp
  simplify/TaggedLineStringSimplifier.cpp
  simplify/TopologyPreservingSimplifier.cpp
  triangulate/quadedge/LastFoundQuadEdgeLocator.cpp
  triangulate/quadedge/LocateFailureException.cpp
  triangulate/quadedge/QuadEdge.cpp
  triangulate/quadedge/QuadEdgeLocator.cpp
  triangulate/quadedge/QuadEdgeSubdivision.cpp
  triangulate/quadedge/TrianglePredicate.cpp
  triangulate/quadedge/TriangleVisitor.cpp
  triangulate/quadedge/Vertex.cpp
  triangulate/DelaunayTriangulationBuilder.cpp
  triangulate/IncrementalDelaunayTriangulator.cpp
  triangulate/VoronoiDiagramBuilder.cpp
  util/Assert.cpp
  util/GeometricShapeFactory.cpp
  util/Interrupt.cpp
  util/math.cpp
  util/Profiler.cpp
  inlines.cpp
  )

PREPEND(GEOS_CAPI_SOURCES ${GEOS_SOURCE_PATH}/capi ${GEOS_CAPI_SOURCES})
PREPEND(GEOS_SOURCES ${GEOS_SOURCE_PATH}/src ${GEOS_SOURCES})

add_library(geos
  SHARED
  ${GEOS_CAPI_SOURCES}
  ${GEOS_SOURCES}
  )
# target_link_libraries()

####################################################################################################
#
# End
#
####################################################################################################
