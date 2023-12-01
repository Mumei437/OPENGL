#pragma once
#include<cmath>
#include<vector>
#include<glm/glm.hpp>


class Sphere
{
private:
	int numVertices;
	int numInidices;
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	void init(int prec);
	float toRadians(float degrees);

public:
	Sphere();
	Sphere(int prec);
	~Sphere();
	int getNumVerices()const;
	int getNumIndices()const;
	std::vector<int> getIndices()const;
	std::vector<glm::vec3> getVertices()const;
	std::vector<glm::vec2> getTexCoords()const;
	std::vector<glm::vec3> getNormals()const;


};

