#! /usr/bin/env python3
# -*- python -*-

####################################################################################################
#
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

from pathlib import Path
import argparse
import os

####################################################################################################

argument_parser = argparse.ArgumentParser(description='Fix Copyright Header')

argument_parser.add_argument(
    '--source-path',
    default=None,
    help='root path'
)

argument_parser.add_argument(
    '--dry-run',
    default=False,
    action='store_true',
    help='dry run mode'
)

args = argument_parser.parse_args()

####################################################################################################

NEW_LICENSE = """
This file is part of the Alpine Toolkit software.
Copyright (C) {year} Fabrice Salvaire
Contact: http://www.fabrice-salvaire.fr
SPDX-License-Identifier: GPL-3.0-only
""".rstrip()

SUFFIXES = ('.py', '.c', '.h', '.cpp', '.hpp')

C_SUFFIXES = ('.c', '.h', '.cpp', '.hpp')

####################################################################################################

def process_file(absolut_file_name: Path, dry_run=False) -> None:
    if absolut_file_name.suffix in C_SUFFIXES:
        COMMENT = '**'
    else:
        COMMENT = '#'
    new_license = NEW_LICENSE.replace(os.linesep, os.linesep + COMMENT + ' ').lstrip()
    year = None
    # print(new_license)
    BEFORE_LICENSE, IN_LICENSE, AFTER_LICENSE = list(range(3))
    state = BEFORE_LICENSE
    lines = []
    with open(absolut_file_name) as fh:
        for line in fh.readlines():
            # continue is used to ged first lines
            if state == BEFORE_LICENSE:
                if '_BEGIN_LICENSE' in line:
                    # print("IN_LICENSE")
                    state = IN_LICENSE
                    continue
            elif state == IN_LICENSE:
                if '20' in line:
                    i = line.find('(C) ')
                    i += 4
                    year = line[i:i+4]
                if '_END_LICENSE' in line:
                    state = AFTER_LICENSE
                    # print("AFTER_LICENSE")
                    lines.append(new_license.format(year=year) + os.linesep)
                continue
            lines.append(line)
    content = ''.join(lines)
    if state == AFTER_LICENSE:
        print(f"> {absolut_file_name}")
        if dry_run:
            rule = '/' * 100
            print(rule)
            print(content)
            print(rule)
        else:
            absolut_file_name.rename(str(absolut_file_name) + '~')
            with open(absolut_file_name, 'w') as fh:
                fh.write(content)

####################################################################################################

THIS_FILE = Path(__file__).absolute()

def filter_file(file_name: Path) -> bool:
    # return True
    return file_name != THIS_FILE and (file_name.name == 'CMakeLists.txt' or file_name.suffix in SUFFIXES)

####################################################################################################

def walk(source_path: Path) -> None:
    for path, directories, files in os.walk(source_path):
        path = Path(path)
        for file_name in files:
            file_name = Path(file_name)
            if filter_file(file_name):
                absolut_file_name = path.joinpath(file_name)
                process_file(absolut_file_name, dry_run=args.dry_run)

####################################################################################################

if args.source_path:
    source_path = Path(args.source_path).absolute()
    if source_path.exists():
        print(source_path)
        if source_path.is_dir():
            walk(source_path)
        elif filter_file(source_path):
            process_file(source_path, dry_run=args.dry_run)
