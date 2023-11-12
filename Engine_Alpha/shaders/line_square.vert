#version 430

uniform float x_offset;
uniform float y_offset;

void main(void)
{
	if(gl_VertexID == 0)
	{
		gl_Position = vec4 (-0.25 + x_offset ,0.25 + y_offset ,0.0f ,1.0f);
	}
	else if(gl_VertexID == 1)
	{
		gl_Position = vec4 (0.25 + x_offset ,0.25 + y_offset ,0.0f ,1.0f);
	}
	else if(gl_VertexID == 2)
	{
		gl_Position = vec4 (0.25 + x_offset ,-0.25 + y_offset ,0.0f ,1.0f);
	}
	else 
	{
		gl_Position = vec4 (-0.25 + x_offset ,-0.25 + y_offset ,0.0f ,1.0f);
	}
}