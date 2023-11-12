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
	//ファイルのシェーダーコードを読み込み、保存する文字列型
	std::string vertexCode;
	std::string fragmentCode;
	
	//頂点シェーダーとフラグメントシェーダーのそれぞれのシェーダーファイルの読み込み用
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//ifstream オブジェクトが例外をスローできるようにする
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//ファイルの読み込み
		vShaderFile.open(vertexShaderfilename);
		fShaderFile.open(fragmentShaderfilename);
		
		std::stringstream vShaderStream{}, fShaderStream;
		//ファイルの内容をストリームに読み込む
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//ファイルを閉じる
		vShaderFile.close();
		fShaderFile.close();

		//ストリームを文字列に変換
		vertexCode = vShaderStream.str().c_str();
		fragmentCode = fShaderStream.str().c_str();

	}
	catch (std::ifstream::failure message)
	{
		std::cerr << "エラー：シェーダーファイルの読み込みに失敗しました。シェーダー名：" << vertexShaderfilename << "," << fragmentShaderfilename << "\n";
		exit(EXIT_FAILURE);

	}

	//文字列型からchar型の配列に変換
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//頂点,フラグメントのシェーダーオブジェクト
	GLuint vertex, fragment;
	//コンパイル、リンクの成功判定
	GLint success;
	//エラーログ
	GLchar infoLog[512];

	//頂点シェーダーの読み込み
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	//コンパイルエラーの確認
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)//コンパイラに失敗していた場合
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "エラー：頂点シェーダーのコンパイルに失敗しました。\nShader Info Log:" << infoLog << "\n";
		//exit(EXIT_FAILURE);
	}

	//フラグメントシェーダの読み込み
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	//コンパイルエラーの確認
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)//コンパイラに失敗していた場合
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cerr << "エラー：フラグメントシェーダーのコンパイルに失敗しました。\nShader Info Log:" << infoLog << "\n";
		//exit(EXIT_FAILURE);
	}

	//シェーダーの統合作業
	mID = glCreateProgram();
	glAttachShader(mID, vertex);
	glAttachShader(mID, fragment);
	glLinkProgram(mID);
	
	//リンクエラーの確認
	glGetProgramiv(mID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mID, 512, NULL, infoLog);
		std::cerr << "エラー：リンクに失敗しました。\nShader Info Log:" << infoLog << "\n";

	}


	//不要になったシェーダーの削除
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
		std::cerr << "uniformに \"" << name << "\"の様な変数はありません。\n";
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
		std::cerr << "uniformに \"" << name << "\"の様な変数はありません。" << std::endl;
	}

	return false;
}
