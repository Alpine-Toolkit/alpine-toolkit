###################################################################################################
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

import json

####################################################################################################

class ThirdPartyLicense:

    ##############################################

    def __init__(self, **kwargs):

        for key, value in kwargs.items():
            setattr(self, key, value)

####################################################################################################

with open('third_party_licenses.json') as f:
    data = json.load(f)
    third_parties = [ThirdPartyLicense(**third_party)
                     for third_party in data]

with open('third_party_licenses.html', 'w') as f:
    f.write("""
<!doctype html>
<html lang="en" prefix="og: http://ogp.me/ns#">
<head>
  <meta charset="utf-8">
</head>
<body>
""")
    for third_party in third_parties:
        f.write("""
<h1>{0.third_party_name}</h1>
<ul>
  <li>is used: {0.used}</li>
  <li>is shown: {0.show}</li>
  <li><a href="{0.third_party_url}">Home page</a></li>
  <li>Version: {0.third_party_version}</li>
  <li>License Name: {0.license_name}</li>
  <li><a href="{0.license_url}">License link</a></li>
</ul>
        <div style="background: white; width: 50em">{0.license_text}</div>
<div style="background: wheat; width: 50em">{0.license_note}</div>
""".format(third_party))
    f.write("""
</body>
</html>
""")
