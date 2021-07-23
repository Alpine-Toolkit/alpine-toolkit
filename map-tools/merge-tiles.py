#! /usr/bin/env python3

####################################################################################################

from pathlib import Path
import os
import sqlite3

# from ArithmeticInterval import IntervalInt2D

####################################################################################################

source_path = Path('/home/vps-vm/fabrice/cache-QtCarto/sources')
cache_directory = Path('/home/vps-vm/fabrice/cache-QtCarto/QtCarto/geoportail/offline')

####################################################################################################

for i in range(1, 18 +1):
    _ = cache_directory.joinpath(str(i))
    if not _.exists():
        os.mkdir(_)

####################################################################################################

def split_tile_filename(tilename):
    _ = provider, map_id, level, row, column = tilename[:-len('.jpeg')].split('-')
    return _

####################################################################################################

def read_binary(path):
    with open(path, 'rb') as fh:
        data = fh.read()
    return data

def compare(path1, path2):
    return read_binary(path1) == read_binary(path2)

####################################################################################################

def handle_tile(path):
    tilename = path.name
    level = path.parent.name
    provider, map_id, level, row, column = split_tile_filename(tilename)
    dst = cache_directory.joinpath(level, tilename)
    if not dst.exists():
        print(f'level: {level}   tilename: {tilename}')
        print(f'{path} -> {dst}')
        os.rename(path, dst)
    else:
        if compare(path, dst):
            print(f'== {path}   {dst}')
            os.unlink(path)
        else:
            print(f'!= {path}\n   {dst}')
            path_stat = path.stat()
            dst_stat = path.stat()
            if path_stat.st_ctime > dst_stat.st_ctime:
                print('  more recent')
                os.rename(path, dst)
            else:
                print('  older')
                os.unlink(path)

####################################################################################################

def walk():
    for directory, dirnames, filenames in os.walk(source_path, topdown=True, onerror=None, followlinks=False):
        directory = Path(directory)
        for filename in filenames:
            # if filename.startswith('geoportail-') and filename.endswith('.jpg'):
            #     old_filename = filename
            #     filename = old_filename[:-len('.jpg')] + '.jpeg'
            #     os.rename(directory.joinpath(old_filename), directory.joinpath(filename))
            #     print(f'RENAME {old_filename}   {filename}')
            if filename.startswith('geoportail-') and filename.endswith('.jpeg'):
                _ = directory.joinpath(filename)
                handle_tile(_)

####################################################################################################

def init_database(path):

    con = sqlite3.connect(path)
    cur = con.cursor()

    sqlite_schema = '''
    CREATE TABLE metadata (version INTEGER);
    INSERT INTO metadata VALUES(1);

    CREATE TABLE provider (provider_id INTEGER PRIMARY KEY AUTOINCREMENT,name TEXT NOT NULL);
    INSERT INTO provider VALUES(1,'geoportail');

    CREATE TABLE map_level (map_level_id INTEGER PRIMARY KEY AUTOINCREMENT,provider_id INTEGER, map_id INTEGER, level INTEGER, FOREIGN KEY(provider_id) REFERENCES provider_id(provider_id));

    CREATE TABLE tile (map_level_id INTEGER, row INTEGER, column INTEGER, offline_count INTEGER, FOREIGN KEY(map_level_id) REFERENCES map_level(map_level_id));
    '''

    for line in sqlite_schema.splitlines():
        print(line)
        cur.execute(line)

    for level in range(6, 18 +1):
        line = f'INSERT INTO map_level (provider_id, map_id, level) VALUES(1,0,{level});'
        print(line)
        cur.execute(line)

    con.commit()
    con.close()

####################################################################################################

def register_tile(sqlite_path, cache_directory):

    con = sqlite3.connect(sqlite_path)
    cur = con.cursor()

    for directory, dirnames, filenames in os.walk(cache_directory, topdown=True, onerror=None, followlinks=False):
        for filename in filenames:
            if filename.startswith('geoportail-') and filename.endswith('.jpeg'):
                provider, map_id, level, row, column = split_tile_filename(filename)
                # map_id - level - x - y
                # row = x   column = y
                # INSERT INTO tile VALUES(11,33291,23443,1);
                map_level_id = int(level) -6 +1
                line = f'INSERT INTO tile (map_level_id, row, column, offline_count) VALUES({map_level_id}, {row}, {column}, 1);'
                print(line)
                cur.execute(line)

    con.commit()
    con.close()

####################################################################################################

if False:
    walk()

####################################################################################################

if True:
    sqlite_path = Path('/home/vps-vm/fabrice/cache-QtCarto/QtCarto/geoportail/offline/offline_cache.sqlite')
    if sqlite_path.exists():
        os.unlink(sqlite_path)
    init_database(sqlite_path)
    register_tile(sqlite_path, cache_directory)
