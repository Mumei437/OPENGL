#pragma once
#include<vector>
#include<glm/glm.hpp>

class ImportedModel
{
private:
	int numVertices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normalVec;

public:
	ImportedModel(const char* filePath);
	int getNumVertices()const;
	std::vector<glm::vec3> getVertices()const;
	std::vector<glm::vec2> getTextureCoords()const;
	std::vector<glm::vec3> getNormals()const;

};



class ModelImporter
{
private:
	//
	std::vector<float> vertVals;
	std::vector<float> stVals;
	std::vector<float> normVals;

	//
	std::vector<float> triangleVerts;
	std::vector<float> textureCoords;
	std::vector<float> normals;

public:
	ModelImporter();
	void parseOBJ(const char* filePath);
	int getNumVertices()const;

	std::vector<float> getVertices()const;
	std::vector<float> getTextureCoordinates()const;
	std::vector<float> getNormals()const;

};
