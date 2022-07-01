###################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
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
