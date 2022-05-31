####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the Alpine Toolkit software.
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

import math

####################################################################################################

class FuelModel:

    ##############################################

    def  __init__(self, **kwargs):

        self.__dict__.update(kwargs)

    ##############################################

    def fuel_area(self):
        return math.pi * self.diameter * self.diameter / 4

    ##############################################

    def compute_capacity(self, weight=None, depth=None):

        # P = π r^2 h / 1000 - Pcap

        package_weight = self.total_weight - self.net_weight
        weight = 0

        if depth is not None:
            # 1L = 10 x 10 x 10 cm = 1e6 mm^3 = 1 Kg = 1000 g
            # 1000 mm^3 = 1g
            # fuel weight = displaced - cap  water weight
            weight = self.fuel_area() * depth * 1e-3 - self.cap_weight

        weight = min(weight, self.total_weight)
        capacity = max((weight - package_weight) / self.net_weight, 0)

        return capacity * 100

    ##############################################

    def compute_immersion_depth(self, capacity):

        weight = self.total_weight - (100 - capacity) / 100 * self.net_weight
        return (weight + self.cap_weight) / (self.fuel_area() * 1e-3)

    ##############################################

    def compute_cap_weight(self, weight, depth):

        return self.fuel_area() * depth * 1e-3 - weight

    ##############################################

    def tikz_gauge(self, options, mask):

        capacities = range(0, 110, 20)
        depths = [fuel_model.compute_immersion_depth(capacity) for capacity in capacities]

        code = r'\begin{{scope}}[{0}]'.format(options) + '\n'
        y0 = depths[0]
        y1 = depths[-1]
        if mask:
            code += r'\draw[line width=.1mm,dashed,fill=gray!10] (-4mm,{0:.0f}mm) rectangle (0,{1:.0f}mm);'.format(y0 -1, y1 +1) + '\n'
        y = y1 + 2
        code += r'\draw[line width=1mm] (0,0) -- (0,{0:.0f}mm);'.format(y) + '\n'
        code += r'\draw[line width=1mm] (12mm,0) -- ++(0,{0:.0f}mm);'.format(y) + '\n'
        code += r'\node[rotate=90, anchor=south west] at (12mm,0) {{{0}}};'.format(self.name) + '\n'
        for capacity, depth in zip(capacities, depths):
            code += r'\draw[line width=.5mm] (0,{0:.0f}mm) -- (5mm,{0:.0f}mm);'.format(depth) + '\n'
            code += r'\draw (12mm,{0:.0f}mm) node[anchor=east] {{{1}}};'.format(depth, capacity) + '\n'
        code += r'\end{scope}' + '\n'

        return code

####################################################################################################

cv_470 = FuelModel(
    name='CV 470 Plus',
    total_weight=630, # measured
    net_weight=450, # specified
    # package_weight=180 # 630 - 450 = 180
    diameter=110, # mm
    cap_weight=115, # g TO BE COMFIRMED
    depth_measure=(
        (575, 77),
        (485, 65),
    ),
)

cv_300 = FuelModel(
    name='CV 300 Plus',
    total_weight=365, # to be verified (358 g ?)
    net_weight=240, # specified
    # package_weight=150 # 360 - 240 = 120
    diameter=90, # mm
    cap_weight=50, # g TO BE COMFIRMED
    depth_measure=(
        (320, 54),
    ),
)

msr_227 = FuelModel(
    name='MSR IsoPro 227', # g
    total_weight=374, # specified
    net_weight=227, # specified
    diameter=110, # mm
    cap_weight=125, # g TO BE COMFIRMED
    depth_measure=(
        (325, 48),
    )
)

####################################################################################################

for fuel_model in (cv_300, cv_470, msr_227):
    print('\n')
    print(fuel_model.name)
    for capacity in range(0, 110, 20):
        depth = fuel_model.compute_immersion_depth(capacity)
        print("capacity {} % : {:.0f} mm ({:.0f} %)".format(capacity, depth, fuel_model.compute_capacity(depth=depth)))
    for weight, depth in fuel_model.depth_measure:
        print('Cap weight {:.0f} g'.format(fuel_model.compute_cap_weight(weight, depth)))

####################################################################################################

code = r'''
\documentclass{article}
\usepackage{geometry}
\geometry{a4paper, margin=1cm, headheight=0mm}
\usepackage{tikz}
\usepackage[hidelinks]{hyperref}
\usepackage{qrcode}
\renewcommand{\familydefault}{\sfdefault}
\begin{document}
\pagestyle{empty}
\begin{tikzpicture}[]
\draw (0,0) rectangle ++(6cm,10cm);
\node[anchor=north] at (30mm,100mm) {\Large Alpine Toolkit Fuel Gauge};
\node[anchor=center,inner sep=0pt] at (30mm,82mm) {\includegraphics[height=20mm]{../../ressources/application-icons/icon-transparent-512.png}};
% http://alpine-toolkit.bleausard.fr/fuel-gauge.pdf
\node[anchor=south west, rotate=90] at (60mm,2mm) {\tiny \url{https://bleausard.fr/alpine-toolkit/fuel-gauge} Copyright Fabrice Salvaire V1 2017};
\node[anchor=center] at (50mm,85mm) {\qrcode[height=15mm]{https://bleausard.fr/alpine-toolkit/fuel-gauge}};
\begin{scope}[shift={(42mm,59mm)}]
\draw[line width=.2mm,fill=gray!25] (0,0) rectangle (10mm,8mm);
\draw[line width=.2mm,fill=gray!60] (2mm,10mm) -- (2mm,3mm) -- (8mm,3mm) --(8mm,10mm) .. controls (8mm,12mm) and (2mm,12mm) .. (2mm,10mm);
\draw[line width=.5mm] (0,1cm) -- (0,0) -- (1cm,0) -- (1cm,1cm);
% \draw[line width=.2mm] (0,8mm) -- (2mm,8mm);
% \draw[line width=.2mm] (8mm,8mm) -- (10mm,8mm);
\end{scope}
'''

x_shift = 0
for fuel_model in (
        cv_470,
        cv_300,
        msr_227,
):
    options = 'shift={{({0}mm,0)}}'.format(x_shift * 20 + .5)
    code += fuel_model.tikz_gauge(options, x_shift > 0)
    x_shift += 1

code += '''
\end{tikzpicture}
\end{document}
'''

with open('fuel-gauge.tex', 'w') as f:
    f.write(code)
