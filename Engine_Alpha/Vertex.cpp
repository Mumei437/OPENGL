#include "Vertex.h"

Vertex::Vertex(const float* vert, const GLuint Vertsize)
	:
	mBufferNum(0),
	mVertCount(0),
	mTexCount(0),
	mNormCount(0),
	mIndexCount(0)
{

	glGenVertexArrays(1, &mVao);
	glGenBuffers(BUFFER_SIZE, mBuffers.buffers);

	mVertCount = (Vertsize / sizeof(float)) / mBuffers.buffers_num[VERTEX];

	if (Vertsize >= 0)
	{
		SetVertex(vert, Vertsize);
	}
	else
	{
		printf("頂点のサイズが負の値で不正の値です。\n");
		mState = enError;
	}

}

Vertex::Vertex()
{
}

Vertex::Vertex(const float* vert, const GLuint Vertsize, const int* index, const GLuint index_size)
	:
	mBufferNum(0),
	mVertCount(0),
	mTexCount(0),
	mNormCount(0),
	mIndexCount(0)
{

	glGenVertexArrays(1, &mVao);
	glGenBuffers(BUFFER_SIZE, mBuffers.buffers);

	mVertCount = (Vertsize / sizeof(float)) / mBuffers.buffers_num[VERTEX];
	mIndexCount = (index_size / sizeof(int)) / mBuffers.buffers_num[INDEX];


	if (Vertsize >= 0 && index_size >= 0)
	{
		SetVertex(vert, Vertsize);
		SetIndex(index, index_size);
	}
	else
	{
		printf("頂点のサイズが負の値で不正の値です。\n");
		mState = enError;
	}

}

Vertex::Vertex(const float* vert, const GLuint Vertsize, const float* texc, const GLuint TexSize)
	:
	mBufferNum(0),
	mVertCount(0),
	mTexCount(0),
	mNormCount(0),
	mIndexCount(0)
{

	glGenVertexArrays(1, &mVao);
	glGenBuffers(BUFFER_SIZE, mBuffers.buffers);

	
	mVertCount = (Vertsize / sizeof(float)) / mBuffers.buffers_num[VERTEX];
	mTexCount = (TexSize / sizeof(float)) / mBuffers.buffers_num[TEXCOORDS];


	if (mVertCount == mTexCount && Vertsize >= 0 && TexSize >= 0)
	{
		SetTexCoord(texc, TexSize);
		SetVertex(vert, Vertsize);
	}
	else
	{
		printf("エラー：値が不正です。\n");
		mState = enError;
	}


}

Vertex::Vertex(const float* vert, const GLuint Vertsize, const float* texc, const GLuint TexSize, const int* index, const GLuint index_size)
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(BUFFER_SIZE, mBuffers.buffers);


	mVertCount = (Vertsize / sizeof(float)) / mBuffers.buffers_num[VERTEX];
	mTexCount = (TexSize / sizeof(float)) / mBuffers.buffers_num[TEXCOORDS];

	mIndexCount = (index_size / sizeof(int)) / mBuffers.buffers_num[INDEX];

	

	if (mVertCount == mTexCount && Vertsize >= 0 && TexSize >= 0 && index_size >= 0)
	{
		SetTexCoord(texc, TexSize);
		SetVertex(vert, Vertsize);
		SetIndex(index, index_size);
	}
	else
	{
		printf("エラー：値が不正です。\n");
		mState = enError;
	}
}

Vertex::Vertex(const float* vert, const GLuint Vertsize, const float* texc, const GLuint TexSize, const float* norm, const GLuint NormSize)
	:
	mBufferNum(0),
	mVertCount(0),
	mTexCount(0),
	mNormCount(0),
	mIndexCount(0)
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(BUFFER_SIZE, mBuffers.buffers);


	mVertCount = (Vertsize / sizeof(float)) / mBuffers.buffers_num[VERTEX];
	mTexCount = (TexSize / sizeof(float)) / mBuffers.buffers_num[TEXCOORDS];
	mNormCount = (NormSize / sizeof(float)) / mBuffers.buffers_num[NORMALS];


	if (mVertCount == mTexCount && mVertCount == mTexCount && Vertsize >= 0 && TexSize >= 0)
	{
		SetTexCoord(texc, TexSize);
		SetVertex(vert, Vertsize);
		SetNormals(norm, NormSize);
	}
	else
	{
		printf("エラー：値が不正です。\n");
		mState = enError;
	}
}

Vertex::Vertex(const float* vert, const GLuint Vertsize, const float* texc, const GLuint TexSize, const float* norm, const GLuint NormSize, const int* index, const GLuint index_size)
	:
	mBufferNum(0),
	mVertCount(0),
	mTexCount(0),
	mNormCount(0),
	mIndexCount(0)
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(BUFFER_SIZE, mBuffers.buffers);


	mVertCount = (Vertsize / sizeof(float)) / mBuffers.buffers_num[VERTEX];
	mTexCount = (TexSize / sizeof(float)) / mBuffers.buffers_num[TEXCOORDS];
	mNormCount = (NormSize / sizeof(float)) / mBuffers.buffers_num[NORMALS];
	mIndexCount = (index_size / sizeof(int)) / mBuffers.buffers_num[INDEX];


	if (mVertCount == mTexCount && mVertCount == mTexCount && Vertsize >= 0 && TexSize >= 0 && index_size >= 0)
	{
		SetTexCoord(texc, TexSize);
		SetVertex(vert, Vertsize);
		SetNormals(norm, NormSize);
		SetIndex(index, index_size);
	}
	else
	{
		printf("エラー：値が不正です。\n");
		mState = enError;
	}
}

Vertex::~Vertex()
{
}

void Vertex::VertexActive(const int location)
{
	if (mBuffers.isdefine[VERTEX])
	{
		glBindVertexArray(mVao);
		glBindBuffer(GL_ARRAY_BUFFER, mBuffers.buffers[VERTEX]);
		glVertexAttribPointer(location, mBuffers.buffers_num[VERTEX], GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(location);
	}
}

void Vertex::TexCoordActive(const int location)
{

	if (mBuffers.isdefine[TEXCOORDS])
	{
		glBindVertexArray(mVao);
		glBindBuffer(GL_ARRAY_BUFFER, mBuffers.buffers[TEXCOORDS]);
		glVertexAttribPointer(location, mBuffers.buffers_num[TEXCOORDS], GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(location);
	}

}

void Vertex::NormalActive(const int location)
{
	if (mBuffers.isdefine[NORMALS])
	{
		glBindVertexArray(mVao);
		glBindBuffer(GL_ARRAY_BUFFER, mBuffers.buffers[NORMALS]);
		glVertexAttribPointer(location, mBuffers.buffers_num[NORMALS], GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(location);
	}
}

void Vertex::IndexActive(const int location)
{
	if (mBuffers.isdefine[INDEX])
	{
		glBindVertexArray(mVao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers.buffers[INDEX]);
	}
}

void Vertex::Active(const int& vert_location, const int& tex_location, const int& norm_location)
{
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case VERTEX:
			VertexActive(vert_location);
			break;
		case TEXCOORDS:
			TexCoordActive(tex_location);
			break;
		case NORMALS:
			NormalActive(norm_location);
			break;
		case INDEX:
			IndexActive();
			break;
		}
	}
}

void Vertex::SetVertex(const float* vert, const int size)
{
	try
	{
		mVertCount = (size / sizeof(float)) / mBuffers.buffers_num[VERTEX];

		if (mBuffers.isdefine[TEXCOORDS])
		{
			if (mVertCount != mTexCount)
			{
				throw"頂点とテックスコードの数が異なります。";
			}
		}
		if (mBuffers.isdefine[NORMALS])
		{
			if (mVertCount != mNormCount)
			{
				throw"頂点と法線ベクトルの数が異なります。";
			}
		}

		glBindVertexArray(mVao);

		glBindBuffer(GL_ARRAY_BUFFER, mBuffers.buffers[VERTEX]);
		glBufferData(GL_ARRAY_BUFFER, size, vert, GL_STATIC_DRAW);

		mBuffers.isdefine[VERTEX] = true;
		mState |= enVertex;
	}
	catch (const char* errorCode)
	{
		mState = enError;
		printf("エラー：%s\n", errorCode);
	}
	
}

void Vertex::SetTexCoord(const float* texcoord, const int size)
{
	try
	{
		mTexCount = (size / sizeof(float)) / mBuffers.buffers_num[TEXCOORDS];

		if (mBuffers.isdefine[VERTEX])
		{
			if (mVertCount != mTexCount)
			{
				throw"頂点とテックスコードの数が異なります。";
			}
		}
		if (mBuffers.isdefine[NORMALS])
		{
			if (mTexCount != mNormCount)
			{
				throw"テックスコードと法線ベクトルの数が異なります。";
			}
		}

		glBindVertexArray(mVao);

		glBindBuffer(GL_ARRAY_BUFFER, mBuffers.buffers[TEXCOORDS]);
		glBufferData(GL_ARRAY_BUFFER, size, texcoord, GL_STATIC_DRAW);

		mBuffers.isdefine[TEXCOORDS] = true;
		mState |= enTexCoord;
	}
	catch (const char* errorCode)
	{
		mState = enError;
		printf("エラー：%s\n", errorCode);
	}

}

void Vertex::SetNormals(const float* normals, const int size)
{
	try
	{

		mNormCount = (size / sizeof(float)) / mBuffers.buffers_num[NORMALS];

		if (mBuffers.isdefine[VERTEX])
		{
			if (mVertCount != mNormCount)
			{
				throw"頂点と法線ベクトルの数が異なります。";
			}
		}
		if (mBuffers.isdefine[TEXCOORDS])
		{
			if (mTexCount != mNormCount)
			{
				throw"テックスコードと法線ベクトルの数が異なります。";
			}
		}

		glBindVertexArray(mVao);

		glBindBuffer(GL_ARRAY_BUFFER, mBuffers.buffers[NORMALS]);
		glBufferData(GL_ARRAY_BUFFER, size, normals, GL_STATIC_DRAW);

		mBuffers.isdefine[NORMALS] = true;
		mState |= enNormal;
	}
	catch (const char* errorCode)
	{
		mState = enError;
		printf("エラー：%s\n", errorCode);
	}
}

void Vertex::SetIndex(const int* indexs, const int size)
{

	mIndexCount = (size / sizeof(int)) / mBuffers.buffers_num[INDEX];

	glBindVertexArray(mVao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers.buffers[INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexs, GL_STATIC_DRAW);

	mState |= enIndex;
}
