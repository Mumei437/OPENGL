#pragma once
#include"OpenGL.h"
#include<vector>

class ModelImporter
{
public:
	enum ModelState
	{
		error = 0,
		enable_Vertex = 1,
		enable_TexCoords = 2,
		enable_Normals = 4,
	};
	ModelImporter(const char* filePath);
	~ModelImporter();

	const std::vector<float>& GetVertices()const { return mVertices; }
	const std::vector<float>& GetTexCoords()const { return mTexCoords; }
	const std::vector<float>& GetNormals()const { return mNormals; }

	GLuint GetVertSize()const { return mVertices.size() * sizeof(float); }
	GLuint GetTexCoordsSize()const { return mTexCoords.size() * sizeof(float); }
	GLuint GetNoramalsSize()const { return mNormals.size() * sizeof(float); }
	bool GetEnable(GLuint type) { return ((mState) & (type)) == type; }

private:
	void LoadFile(const char* filePath);

private:
	std::vector<float> mVertices;
	std::vector<float> mTexCoords;
	std::vector<float> mNormals;
	GLuint mState;
};

