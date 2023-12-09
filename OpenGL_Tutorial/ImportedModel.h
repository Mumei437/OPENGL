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

	std::vector<int> indices;

	bool IsSucess = true;

public:
	ImportedModel(const char* filePath);
	int getNumVertices()const;
	bool Is_Success()const { return IsSucess; }
	std::vector<glm::vec3> getVertices()const;
	std::vector<glm::vec2> getTextureCoords()const;
	std::vector<glm::vec3> getNormals()const;
	std::vector<int> getIndices()const;

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

	std::vector<int> indeices;

public:
	ModelImporter();
	bool parseOBJ(const char* filePath);
	int getNumVertices()const;

	std::vector<float> getVerVal()const;
	std::vector<float> getTextureCoordVal()const;
	std::vector<float> getNormVal()const;

	std::vector<float> getVertices()const;
	std::vector<float> getTextureCoordinates()const;
	std::vector<float> getNormals()const;
	std::vector<int> getIndices()const;

};
