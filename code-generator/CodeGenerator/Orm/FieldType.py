####################################################################################################
#
# $QTCARTO_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2016 Fabrice Salvaire
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
# $QTCARTO_END_LICENSE$
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
