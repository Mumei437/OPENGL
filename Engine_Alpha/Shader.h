#pragma once
#include"OpenGL.h"
#include"math.h"

class Shader
{
public:
	Shader(const char* vertexShaderfilename, const char* fragmentShaderfilename);
	~Shader();

	void Use();

	void setBool(const char* name, bool value);
	void setInt(const char* name, int value);
	void setFloat(const char* name, float value);
	void setVector2(const char* name, const Vector2& vec2);
	void setVector3(const char* name, const Vector3& vec3);
	void setVector4(const char* name, const Vector4& vec4);
	void setMatrix4(const char* name, const Matrix4& mat4);

private:
	bool checkUniform(GLint* location, const char* name);

private:
	//登録したシェーダーの識別番号
	GLuint mID;
};

