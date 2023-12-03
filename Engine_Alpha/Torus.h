#pragma once
#include "Shape.h"
#include"math.h"

class Torus :
    public Shape
{
public:
    Torus(class Renderer* renderer);
    Torus(class Renderer* renderer, float innerRadius, float outerRadius, int precin);

    ~Torus();

    void Update(const float& deltaTime)override;

    void Init()override;

private:
    int numVertices;
    int numIndices;
    int prec;
    float inner;
    float outer;
    Vector3 rot;
};

