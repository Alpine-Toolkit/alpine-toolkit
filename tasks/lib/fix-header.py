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

argument_parser.add_argument(
    '--check-c',
    default=False,
    action='store_true',
    help='check C header'
)

args = argument_parser.parse_args()

####################################################################################################

NEW_LICENSE = """
This file is part of the Alpine Toolkit software.
Copyright (C) {year} Fabrice Salvaire
Contact: http://www.fabrice-salvaire.fr
SPDX-License-Identifier: GPL-3.0-only
""".rstrip()

SUFFIXES = ('.py', '.c', '.h', '.cpp', '.hpp', '.hxx', '.cmake', '.js', '.qml', '.java', '.jinja')

C_SUFFIXES = ('.c', '.h', '.cpp', '.hpp', '.hxx', '.js', '.qml', '.java')

####################################################################################################

def change_to_spdx(absolut_file_name: Path, dry_run=False) -> None:
    if absolut_file_name.suffix in C_SUFFIXES:
        COMMENT = ' *'
    else:
        # COMMENT = ' #'
        COMMENT = '#'
    new_license = NEW_LICENSE.replace(os.linesep, os.linesep + COMMENT + ' ').lstrip()
    # new_license = ' ' + new_license
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

def check_c_header(absolut_file_name: Path, dry_run=False) -> None:
    if absolut_file_name.suffix not in C_SUFFIXES:
        return

    with open(absolut_file_name) as fh:
        lines = fh.readlines()
    number_of_lines = len(lines)

    spdx_line_number = None
    for i, line in enumerate(lines):
        if 'SPDX-License-Identifier:' in line:
            spdx_line_number = i
            break

    if spdx_line_number and spdx_line_number < 10:
        # print(f"> {absolut_file_name}")
        header_start = spdx_line_number -1
        while header_start > 0:
            if '/*' in lines[header_start]:
                break
            header_start -= 1
        header_stop = spdx_line_number +1
        while header_stop < number_of_lines:
            if '*/' in lines[header_stop]:
                break
            header_stop += 1

        # print(header_start, spdx_line_number, header_stop)

        changed = False
        for i in range(header_start+1, header_stop+1):
        # for i in range(header_start, header_stop+1):
            line = lines[i].strip()
            if line.startswith('* ') or line == '*':
                line = '*' + line
            line += os.linesep
            if lines[i] != line:
                lines[i] = line
                changed = True
                
        if changed:
            print(f"> {absolut_file_name}")
            content = ''.join(lines)
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
    return (file_name.resolve().exists() and
            file_name != THIS_FILE and
            (file_name.name == 'CMakeLists.txt' or file_name.suffix in SUFFIXES))

####################################################################################################

def walk(source_path: Path, process_file) -> None:
    for path, directories, files in os.walk(source_path):
        path = Path(path)
        for file_name in files:
            file_name = path.joinpath(file_name)
            if filter_file(file_name):
                absolut_file_name = path.joinpath(file_name)
                process_file(absolut_file_name, dry_run=args.dry_run)

####################################################################################################

if args.source_path:
    source_path = Path(args.source_path).absolute()
    if source_path.exists():
        print(source_path)

        if args.check_c:
            process_file = check_c_header
        else:
            process_file = change_to_spdx

        if source_path.is_dir():
            walk(source_path, process_file)
        # elif filter_file(source_path):
        else:
            process_file(source_path, dry_run=args.dry_run)


