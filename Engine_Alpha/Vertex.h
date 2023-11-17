#pragma once
#include"OpenGL.h"
#include<vector>

#define VERTEX 0
#define TEXCOORDS 1


class Vertex
{
public:
	Vertex(const float* vert, const int Vertsize);
	Vertex(const float* vert, const int Vertsize, const float* texc, const int TexSize);
	~Vertex();

	void VertexActive(const int location = 0);
	void TexCoordActive(const int location = 0);

	void SetVertex(const float* vert, const int size);
	void SetTexCoord(const float* texcoord, const int size);
	GLuint GetVertexCount()const { return mVertCount; }
	GLuint GetTexCount()const { return mTexCount; }

private:

private:
	GLuint mVao;
	//VertInformation mVertex;
	//VertInformation mTexCoord;

	const GLuint mVertNum = 3;
	const GLuint mTexNum = 2;
	GLuint mID[2];
	GLuint mBufferNum;

	GLuint mVertCount;
	GLuint mTexCount;
};

