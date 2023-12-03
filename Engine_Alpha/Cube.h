#pragma once
#include"Shape.h"
#include"math.h"
class Cube
	: public Shape
{
public:
	Cube(class Renderer* renderer);
	~Cube();
	void Init()override;

	void Update(const float& deltaTime)override;
private:
	Vector3 rot;
};

