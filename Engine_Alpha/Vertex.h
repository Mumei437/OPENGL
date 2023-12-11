#pragma once
#include"OpenGL.h"
#include<vector>

#define VERTEX 0
#define TEXCOORDS 1
#define NORMALS 2
#define INDEX 3

#define BUFFER_SIZE 4

class Vertex
{
public:
	enum VertexState
	{
		enError = 0,
		enNormal = 1,
		enIndex  = 2,
		enTexCoord = 4,
		enVertex = 8,
	};
public:
	Vertex(const float* vert, const GLuint Vertsize);

	Vertex();

	Vertex(const float* vert, const GLuint Vertsize, const int* index, const GLuint index_size);

	Vertex(const float* vert, const GLuint Vertsize, const float* texc, const GLuint TexSize);

	Vertex(const float* vert, const GLuint Vertsize, const float* texc, const GLuint TexSize, const int* index, const GLuint index_size);


	Vertex(const float* vert, const GLuint Vertsize, const float* texc, const GLuint TexSize,
		const float* norm, const GLuint NormSize);

	Vertex(const float* vert, const GLuint Vertsize, const float* texc, const GLuint TexSize,
		const float* norm, const GLuint NormSize, const int* index, const GLuint index_size);

	~Vertex();

	void VertexActive(const int location = 0);
	void TexCoordActive(const int location = 0);
	void NormalActive(const int location = 0);
	void IndexActive(const int location = 0);

	void Active(const int& vert_location = 0, const int& tex_location = 0, const int& norm_location = 0);

	void SetVertex(const float* vert, const int size);
	void SetTexCoord(const float* texcoord, const int size);
	void SetNormals(const float* normals, const int size);
	void SetIndex(const int* indexs, const int size);

	GLuint GetVertexCount()const { return mVertCount; }
	GLuint GetTexCount()const { return mTexCount; }
	GLuint GetIndexCount()const { return mIndexCount; }

	bool GetState(GLuint type)const { return ((mState) & (type)) == type; }

private:
	struct VertexBuffer
	{
		GLuint buffers[BUFFER_SIZE];
		bool isdefine[BUFFER_SIZE] = { false,false,false,false };
		const GLuint buffers_num[BUFFER_SIZE] = { 3,2,3,1 };
	};
private:
	GLuint mVao;

	GLuint mnumVertices;
	GLuint mnumInidices;

	//VertInformation mVertex;
	//VertInformation mTexCoord;

	const GLuint mVertNum = 3;
	const GLuint mTexNum = 2;
	const GLuint mNormnum = 3;
	VertexBuffer mBuffers;
	GLuint mBufferNum;

	GLuint mVertCount;
	GLuint mTexCount;
	GLuint mNormCount;
	GLuint mIndexCount;

	GLuint mState = enError;

};

