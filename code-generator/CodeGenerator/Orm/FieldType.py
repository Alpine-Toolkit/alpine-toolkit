####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

class FieldType:

    __type_conversion__ = None

    ##############################################

    def __init__(self, sql_type, qt_type):

        self._sql_type = sql_type
        self._qt_type = qt_type

    ##############################################

    def __repr__(self):

        return '{0.__class__.__name__} sql: {0._sql_type} qt: {0._qt_type}'.format(self)

    ##############################################

    @property
    def sql_type(self):
        return self._sql_type

    @property
    def qt_type(self):
        return self._qt_type

    @property
    def type_conversion(self):
        return self.__type_conversion__
