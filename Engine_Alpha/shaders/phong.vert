#version 430

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 vertNormal;

out vec3 varyingNormal;
out vec3 varyingLightDir;
out vec3 varyingVertPos;
out vec3 varyingHalfVector;
out vec2 tc;



struct PositionalLight
{ 
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};
struct Material
{ 
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};
uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 norm_matrix; // for transforming normals

layout (binding = 0) uniform sampler2D samp;

//in vec2 tc;

//layout (binding = 0) uniform sampler2D samp;

void main(void)
{ 

	mat4 mv_matrix = view_matrix * model_matrix;
	
	varyingVertPos = (mv_matrix * vec4(vertNormal,1.0)).xyz;
	varyingLightDir = light.position - varyingVertPos;
	varyingNormal = (norm_matrix * vec4(vertNormal,1.0)).xyz;
	varyingHalfVector = (varyingLightDir + (-varyingVertPos)).xyz;

	gl_Position = proj_matrix *mv_matrix * vec4(vertPos, 1.0);

	tc = texCoord;

}