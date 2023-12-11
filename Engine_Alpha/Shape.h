#pragma once
#include"Vertex.h"
class Shape
{
public:
	Shape(class Renderer* renderer);
	virtual ~Shape();
	void Active(const int& vert_location, const int& tex_location, const int& norm_location);
	virtual void Init();

	class Transform* GetTransform()const { return mTransform; }

	virtual void Update(const float& deltaTime);

	bool GetIsDestroy()const { return mIsDestroy; }

	void SetTexture(const char* filePath);

	class Texture* GetTexture()const { return mTexture; }

	GLuint GetVertexState(const GLuint type)const;
	
	unsigned int GetIndexCount()const;
	unsigned int GetVertCount()const;
	unsigned int GetTexCount()const;

protected:
	enum Surface
	{
		enFace_front = GL_CCW,
		enFace_back = GL_CW,
	};
	class Vertex* mVertex;
	class Transform* mTransform;

	bool mIsDestroy;

	class Renderer* mRenderer;


	class Texture* mTexture;

	Surface mSurface = enFace_front;

};

