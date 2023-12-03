#pragma once
#include "Shape.h"
#include"math.h"
class Pyramid :
    public Shape
{
public:
    Pyramid(class Renderer* renderer);
    ~Pyramid();
    void Init()override;
    void Update(const float& deltaTime)override;

private:
    Vector3 rot;
};

