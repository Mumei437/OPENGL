#include "Shader.h"
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<typeinfo>

Shader::Shader(const char* vertexShaderfilename, const char* fragmentShaderfilename)
{
	//�t�@�C���̃V�F�[�_�[�R�[�h��ǂݍ��݁A�ۑ����镶����^
	std::string vertexCode;
	std::string fragmentCode;
	
	//���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�̂��ꂼ��̃V�F�[�_�[�t�@�C���̓ǂݍ��ݗp
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//ifstream �I�u�W�F�N�g����O���X���[�ł���悤�ɂ���
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//�t�@�C���̓ǂݍ���
		vShaderFile.open(vertexShaderfilename);
		fShaderFile.open(fragmentShaderfilename);
		
		std::stringstream vShaderStream{}, fShaderStream;
		//�t�@�C���̓��e���X�g���[���ɓǂݍ���
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//�t�@�C�������
		vShaderFile.close();
		fShaderFile.close();

		//�X�g���[���𕶎���ɕϊ�
		vertexCode = vShaderStream.str().c_str();
		fragmentCode = fShaderStream.str().c_str();

	}
	catch (std::ifstream::failure message)
	{
		std::cerr << "�G���[�F�V�F�[�_�[�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B�V�F�[�_�[���F" << vertexShaderfilename << "," << fragmentShaderfilename << "\n";
		exit(EXIT_FAILURE);

	}

	//������^����char�^�̔z��ɕϊ�
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//���_,�t���O�����g�̃V�F�[�_�[�I�u�W�F�N�g
	GLuint vertex, fragment;
	//�R���p�C���A�����N�̐�������
	GLint success;
	//�G���[���O
	GLchar infoLog[512];

	//���_�V�F�[�_�[�̓ǂݍ���
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	//�R���p�C���G���[�̊m�F
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)//�R���p�C���Ɏ��s���Ă����ꍇ
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "�G���[�F���_�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\nShader Info Log:" << infoLog << "\n";
		//exit(EXIT_FAILURE);
	}

	//�t���O�����g�V�F�[�_�̓ǂݍ���
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	//�R���p�C���G���[�̊m�F
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)//�R���p�C���Ɏ��s���Ă����ꍇ
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cerr << "�G���[�F�t���O�����g�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B\nShader Info Log:" << infoLog << "\n";
		//exit(EXIT_FAILURE);
	}

	//�V�F�[�_�[�̓������
	mID = glCreateProgram();
	glAttachShader(mID, vertex);
	glAttachShader(mID, fragment);
	glLinkProgram(mID);
	
	//�����N�G���[�̊m�F
	glGetProgramiv(mID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mID, 512, NULL, infoLog);
		std::cerr << "�G���[�F�����N�Ɏ��s���܂����B\nShader Info Log:" << infoLog << "\n";

	}


	//�s�v�ɂȂ����V�F�[�_�[�̍폜
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

Shader::~Shader()
{
}

void Shader::Use()
{
	glUseProgram(mID);
}

void Shader::setBool(const char* name, bool value)
{
	GLint location = glGetUniformLocation(mID, name);

	if (location != -1)
	{
		glUniform1i(location, (int)value);
	}
	else
	{
		std::cerr << "uniform�� \"" << name << "\"�̗l�ȕϐ��͂���܂���B\n";
	}

	
}
void Shader::setInt(const char* name, int value)
{
	GLint location = NULL;

	if (checkUniform(&location, name))
	{
		glUniform1i(glGetUniformLocation(mID, name), value);
	}
}

void Shader::setFloat(const char* name, float value)
{

	GLint location = NULL;

	if (checkUniform(&location, name))
	{
		glUniform1f(location, value);
	}
}

void Shader::setVector2(const char* name, const Vector2& vec2)
{
	GLint location = NULL;

	if (checkUniform(&location, name))
	{
		glUniform2f(location, vec2.x, vec2.y);
	}
}

void Shader::setVector3(const char* name, const Vector3& vec3)
{
	GLint location = NULL;

	if (checkUniform(&location, name))
	{
		glUniform3f(location, vec3.x, vec3.y, vec3.z);
	}
}

void Shader::setVector4(const char* name, const Vector4& vec4)
{
	GLint location = NULL;

	if (checkUniform(&location, name))
	{
		glUniform4f(location, vec4.x, vec4.y, vec4.z, vec4.w);
	}
}

void Shader::setMatrix4(const char* name, const Matrix4& mat4)
{
	GLint location = NULL;

	if (checkUniform(&location, name))
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, GetMathPtr(mat4));
	}

}

bool Shader::checkUniform(GLint* location, const char* name)
{

	*location = glGetUniformLocation(mID, name);

	if (*location != -1)
	{
		return true;
	}
	else
	{
		std::cerr << "uniform�� \"" << name << "\"�̗l�ȕϐ��͂���܂���B" << std::endl;
	}

	return false;
}
