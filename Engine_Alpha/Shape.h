#pragma once

class Shape
{
public:
	Shape();
	~Shape();
	void Active(const int& vert_location, const int& tex_location, const int& norm_location);
	virtual void Init();

	class Transform* GetTransform()const { return mTransform; }

protected:
	class Vertex* mVertex;
	class Transform* mTransform;

};

