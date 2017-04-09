SELECT load_extension('mod_spatialite');
SELECT spatialite_version();

-- SELECT InitSpatialMetaData();
SELECT InitSpatialMetaData(1); -- faster

CREATE TABLE places (
  name TEXT NOT NULL
);

SELECT AddGeometryColumn('places', 'geometry', 4326, 'POINT', 'XY');
-- the last (optional) arguments actually means: NOT NULL
-- setting a value ZERO (assumed to be the default value if omitted) then the Geometry column will accept NULL values.
-- otherwise only NOT NULL geometries will be accepted.

INSERT INTO places (name, geometry) values ('place3', MakePoint(4.1, 3.2, 4326));
-- INSERT INTO places (name, geometry) values ('place4', '\x00\x01\xE6\x10\x00\x00\x9A\x99\x99\x99\x99\x99\xF1?\x9A\x99\x99\x99\x99\x99\x01@\x9A\x99\x99\x99\x99\x99\xF1?\x9A\x99\x99\x99\x99\x99\x01@|\x01\x00\x00\x00\x9A\x99\x99\x99\x99\x99\xF1?\x9A\x99\x99\x99\x99\x99\x01@\xFE');

SELECT name, geometry FROM places;
SELECT name, AsText(geometry) FROM places;
