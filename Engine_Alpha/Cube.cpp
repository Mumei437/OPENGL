#include "Cube.h"
#include"Renderer.h"
#include"Vertex.h"


Cube::Cube(Renderer* renderer)
	:
	Shape(renderer)
{
    rot = Vec3::Zero;
}

Cube::~Cube()
{
}

void Cube::Init()
{
    mSurface = enFace_back;

    const GLfloat cube_vertex[] = 
    {
        -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
    };

    float texCoords[] = 
    { 
        1.0, 1.0,  //bottom left of texture
        1.0, 0.0,  
        0.0, 0.0,
        0.0, 0.0,  //bottom left of texture
        0.0, 1.0,
        1.0, 1.0, 
        
        1.0, 0.0,
        0.0, 0.0,  //bottom left of texture
        1.0, 1.0,
        0.0, 0.0,  //bottom left of texture
        0.0, 1.0,
        1.0, 1.0,

        1.0, 0.0,  //bottom left of texture
        0.0, 0.0,
        1.0, 1.0,
        0.0, 0.0,  //bottom left of texture
        0.0, 1.0,
        1.0, 1.0,

        1.0, 0.0,  //bottom left of texture
        0.0, 0.0,
        1.0, 1.0,
        0.0, 0.0,  //bottom left of texture
        0.0, 1.0,
        1.0, 1.0,

        0.0, 1.0,
        1.0, 1.0,
        1.0, 0.0,  //bottom left of textur
        1.0, 0.0,
        0.0, 0.0,
        0.0, 1.0,  //bottom left of texture 
        
        0.0, 1.0,
        1.0, 1.0,  //bottom left of texture
        1.0, 0.0,
        1.0, 0.0,
        0.0, 0.0,
        0.0, 1.0,
        
    };

    mVertex = new Vertex(cube_vertex, sizeof(cube_vertex), texCoords, sizeof(texCoords));

}

void Cube::Update(const float& deltaTime)
{
    rot.y += 50 * deltaTime;

    mTransform->SetRotation(rot);
}
