#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
out vec2 tc;

uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 proj_matrix;
layout (binding = 0) uniform sampler2D samp;


void main(void)
{
	mat4 mv_matrix = view_matrix * model_matrix;
	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
	tc = texCoord;
}