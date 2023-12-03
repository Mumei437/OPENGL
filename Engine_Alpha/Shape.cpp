#include "Shape.h"
#include "Vertex.h"
#include "Transform.h"
#include "Renderer.h"
#include"Texture.h"

Shape::Shape(Renderer* renderer)
	:
	mVertex(nullptr),
	mIsDestroy(true)
{
	mTransform = new Transform();

	renderer->AddShape(this);

	mTexture = new Texture("Textures/default.png");

}

Shape::~Shape()
{
	if (mVertex)
	{
		delete mVertex;
	}
	if (mTransform)
	{
		delete mTransform;
	}

	if (mTexture)
	{
		delete mTexture;
	}
}

void Shape::Active(const int& vert_location, const int& tex_location, const int& norm_location)
{
	if (mVertex != nullptr)
	{
		if (mVertex->GetState() != Vertex::enError)
		{
			mVertex->Active(vert_location, tex_location, norm_location);
		}
	}
	glFrontFace(mSurface);
}

void Shape::Init()
{

}

void Shape::Update(const float& deltaTime)
{
}

void Shape::SetTexture(const char* filePath)
{
	if (mTexture)
	{
		mTexture->SetTexture(filePath);
	}
}

Vertex::VertexState Shape::GetVertexState() const
{
	return mVertex->GetState();
}

unsigned int Shape::GetIndexCount() const
{
	return mVertex->GetIndexCount();
}

unsigned int Shape::GetVertCount() const
{

	if (mVertex)
	{
		return mVertex->GetVertexCount();
	}

	return 0;
}

unsigned int Shape::GetTexCount() const
{

	if (mVertex)
	{
		return mVertex->GetTexCount();
	}

	return 0;
}


