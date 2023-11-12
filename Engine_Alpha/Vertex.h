#pragma once
#include"OpenGL.h"
class Vertex
{
public:
	Vertex(const float* vert, const int size);
	~Vertex();

	void active();

	void SetVertex(const float* vert, const int size);

	int GetVertexCount()const;

private:
	GLuint mVao;
	GLuint mVbo;
	int mCount;
};

