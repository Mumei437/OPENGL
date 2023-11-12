#include "Vertex.h"

Vertex::Vertex(const float* vert, const int size)
	:
	mCount((size/sizeof(float))/3)
{

	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);
	glGenBuffers(1, &mVbo);


	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, size, vert, GL_STATIC_DRAW);


}

Vertex::~Vertex()
{
}

void Vertex::active()
{
	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

void Vertex::SetVertex(const float* vert, const int size)
{
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);
	glGenBuffers(1, &mVbo);


	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, size, vert, GL_STATIC_DRAW);

	mCount = (size / sizeof(float)) / 3;
}

int Vertex::GetVertexCount() const
{
	return mCount;
}
