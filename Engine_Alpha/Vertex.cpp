#include "Vertex.h"

Vertex::Vertex(const float* vert, const int Vertsize)
	:
	mBufferNum(0)
{



	glGenVertexArrays(1, &mVao);
	glGenBuffers(2, mID);

	SetVertex(vert, Vertsize);

	/*
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);
	glGenBuffers(1, &mVbo);


	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, size, vert, GL_STATIC_DRAW);
	*/

}

Vertex::Vertex(const float* vert, const int Vertsize, const float* texc, const int TexSize)
	:
	mBufferNum(0)
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(2, mID);
	
	SetTexCoord(texc, TexSize);
	SetVertex(vert, Vertsize);
}

Vertex::~Vertex()
{
}

void Vertex::VertexActive(const int location)
{
	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mID[VERTEX]);
	glVertexAttribPointer(location, mVertNum, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);
}

void Vertex::TexCoordActive(const int location)
{

	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mID[TEXCOORDS]);
	glVertexAttribPointer(location, mTexNum, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);

}

void Vertex::SetVertex(const float* vert, const int size)
{

	mVertCount = (size / sizeof(float)) / mVertNum;

	
	glBindVertexArray(mVao);


	glBindBuffer(GL_ARRAY_BUFFER, mID[VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, size, vert, GL_STATIC_DRAW);

	
}

void Vertex::SetTexCoord(const float* texcoord, const int size)
{

	mTexCount = (size / sizeof(float)) / mTexNum;

	glBindVertexArray(mVao);

	glBindBuffer(GL_ARRAY_BUFFER, mID[TEXCOORDS]);
	glBufferData(GL_ARRAY_BUFFER, size, texcoord, GL_STATIC_DRAW);

}
