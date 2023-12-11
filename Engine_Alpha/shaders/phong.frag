#version 430

in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec3 varyingVertPos;
in vec3 varyingHalfVector;
in vec2 tc;

out vec4 fragColor;

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
uniform mat4 norm_matrix;

layout (binding = 0) uniform sampler2D samp;

void main(void)
{

	mat4 mv_matrix = view_matrix * model_matrix;
	
	vec3 L = normalize(varyingLightDir);
	vec3 N = normalize(varyingNormal);
	vec3 V = normalize(-varyingVertPos);

	vec3 H = normalize(varyingHalfVector);

	float cosTheta = dot(L,N);

	float cosPhi = dot(H,N);

	vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
	vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(cosTheta ,0.0);
	vec3 specular = light.specular.xyz * material.specular.xyz * pow(max(cosPhi,0.0), material.shininess * 3.0);

	vec4 texColor = texture(samp ,tc);
	
	fragColor = texColor * (globalAmbient + light.ambient +light.diffuse * max(dot(L,N),0.0)) 
					+ light.specular * pow(max(dot(H,N),0.0), material.shininess * 3.0);
}