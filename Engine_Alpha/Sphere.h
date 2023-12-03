#pragma once
#include "Shape.h"
class Sphere :
    public Shape
{
public:
    Sphere(class Renderer* renderer);
    ~Sphere();
    Sphere(class Renderer* renderer, const int& prec);
    void Init()override;

private:
    int mPrec;
};

