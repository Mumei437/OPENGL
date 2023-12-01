#pragma once
#include"OpenGL.h"
#include<vector>

#define VERTEX 0
#define TEXCOORDS 1
#define NORMALS 2


class Vertex
{
public:
	enum VertexState
	{
		enSuccess,
		enError,
	};
public:
	Vertex(const float* vert, const GLuint Vertsize);
	Vertex(const float* vert, const GLuint Vertsize, const float* texc, const GLuint TexSize);
	Vertex(const float* vert, const GLuint Vertsize, const float* texc, const GLuint TexSize,
		const float* norm, const GLuint NormSize);
	~Vertex();

	void VertexActive(const int location = 0);
	void TexCoordActive(const int location = 0);
	void NormalActive(const int location = 0);

	void Active(const int& vert_location = 0, const int& tex_location = 0, const int& norm_location = 0);

	void SetVertex(const float* vert, const int size);
	void SetTexCoord(const float* texcoord, const int size);
	void SetNormals(const float* normals, const int size);
	GLuint GetVertexCount()const { return mVertCount; }
	GLuint GetTexCount()const { return mTexCount; }

	VertexState GetState()const { return mState; }

private:
	enum BufferState
	{
		enUndefine,
		enDefine,
	};
	struct VertexBuffer
	{
		GLuint buffers[3];
		bool isdefine[3] = { false,false,false };
		const GLuint buffers_num[3] = { 3,2,3 };
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

	VertexState mState = enSuccess;

};

