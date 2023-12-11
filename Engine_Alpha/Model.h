#pragma once
#include "Shape.h"
class Model :
    public Shape
{
public:
    Model(class Renderer* renderer, const char* filePath);
    ~Model();

private:
};

