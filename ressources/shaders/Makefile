####################################################################################################

# https://doc.qt.io/qt-6/qtshadertools-qsb.html

# https://developer.android.com/guide/topics/graphics/opengl
# https://www.khronos.org/registry/OpenGL/specs/es/3.1/GLSL_ES_Specification_3.10.pdf
# OpenGL ES 3.1 - This API specification is supported by Android 5.0 (API level 21) and higher.
# The OpenGL ES 3.1 API is designed to work with GLSL ES v1.00, GLSL ES 3.00 and GLSL ES 3.10.

# To dump a shader
#   qsb -d point.vert.qsb

####################################################################################################

all: \
	location_circle.frag.qsb \
	location_circle.vert.qsb \
	path.frag.qsb \
	path.vert.qsb \
	point.frag.qsb \
	point.vert.qsb

clear:
	rm -f *.vert.qsb *.frag.qsb

####################################################################################################

GL_VERSION="120es, 310es"

%.vert.qsb : %.vert
	qsb --glsl ${GL_VERSION} -o $@ $^
%.frag.qsb : %.frag
	qsb --glsl ${GL_VERSION} -o $@ $^

