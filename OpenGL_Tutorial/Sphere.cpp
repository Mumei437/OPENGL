#include "Sphere.h"

void Sphere::init(int prec)
{
	
	numVertices = (prec + 1) * (prec + 1);
	numInidices = prec * prec * 6;
	for (int i = 0; i < numVertices; i++) { vertices.push_back(glm::vec3()); }
	for (int i = 0; i < numVertices; i++) { texCoords.push_back(glm::vec2()); }
	for (int i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); }
	for (int i = 0; i < numInidices; i++) { indices.push_back(0); }



	//球体の頂点の情報の計算と作成
	for (int i = 0; i <= prec; i++)
	{
		for (int j = 0; j <= prec; j++)
		{
			float y = (float)cos(toRadians(180.0f - i * 180.0f / prec));
			float x = -(float)cos(toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
			float z = (float)sin(toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));

			vertices[i * (prec + 1) + j] = glm::vec3(x, y, z);
			texCoords[i * (prec + 1) + j] = glm::vec2(((float)j / prec), ((float)i / prec));
			normals[i * (prec + 1) + j] = glm::vec3(x, y, z);

		}
	}

	//球体の頂点のインデックスの作成
	for (int i = 0; i < prec; i++)
	{
		for (int j = 0; j < prec; j++)
		{

			indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
			indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
			indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;

		}
	}

}

float Sphere::toRadians(float degrees)
{
	return (degrees * 2.0f * 3.14159f) / 360.0f;
}

Sphere::Sphere()
{
	init(48);
}

Sphere::Sphere(int prec)
{
	init(prec);
}

Sphere::~Sphere()
{
}

int Sphere::getNumVerices() const
{
	return numVertices;
}

int Sphere::getNumIndices() const
{
	return numInidices;
}

std::vector<int> Sphere::getIndices() const
{
	return indices;
}

std::vector<glm::vec3> Sphere::getVertices() const
{
	return vertices;
}

std::vector<glm::vec2> Sphere::getTexCoords() const
{
	return texCoords;
}

std::vector<glm::vec3> Sphere::getNormals() const
{
	return normals;
}
