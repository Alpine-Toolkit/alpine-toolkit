####################################################################################################

all: \
	location_circle_shader.h \
	path_shader.h \
	point_shader.h

####################################################################################################

%_shader.h : %_fragment_shader.glsl %_vertex_shader.glsl
	make-shader $^ -o $@
