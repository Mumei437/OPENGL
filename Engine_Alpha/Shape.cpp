#include "Shape.h"
#include "Vertex.h"
#include "Transform.h"

Shape::Shape()
	:
	mVertex(nullptr)
{
	mTransform = new Transform();
}

Shape::~Shape()
{
	delete mVertex;
	delete mTransform;
}

void Shape::Active(const int& vert_location, const int& tex_location, const int& norm_location)
{
	if (mVertex != nullptr)
	{
		if (mVertex->GetState() == Vertex::enSuccess)
		{
			mVertex->Active(vert_location, tex_location, norm_location);
		}
	}
}

void Shape::Init()
{

}


