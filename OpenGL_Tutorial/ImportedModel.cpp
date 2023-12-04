#include "ImportedModel.h"
#include <string>
#include <fstream>
#include <sstream>
#include<glm/glm.hpp>

int my_strlen(const char* str, const char target)
{
	int len = 0;    // •¶š”‚ğ”‚¦‚é‚½‚ß‚ÌƒJƒEƒ“ƒ^
	while (*str != '\0')
	{
		if (*str == target)
		{
			++len;
		}
		str++;
	}
	return len;     // •¶š”‚ğ•Ô‚·
}


ImportedModel::ImportedModel(const char* filePath)
{

	ModelImporter modelImporter = ModelImporter();

	modelImporter.parseOBJ(filePath);
	numVertices = modelImporter.getNumVertices();
	std::vector<float> verts = modelImporter.getVertices();
	std::vector<float> tcs = modelImporter.getTextureCoordinates();
	std::vector<float> normals = modelImporter.getNormals();

	for (int i = 0; i < numVertices; i++)
	{
		vertices.push_back(glm::vec3(verts[i * 3], verts[i * 3 + 1], normals[i * 3 + 2]));
		texCoords.push_back(glm::vec2(tcs[i * 2], tcs[i * 2 + 1]));
		normalVec.push_back(glm::vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]));

	}

}

int ImportedModel::getNumVertices() const
{
	return numVertices;
}

std::vector<glm::vec3> ImportedModel::getVertices() const
{
	return vertices;
}

std::vector<glm::vec2> ImportedModel::getTextureCoords() const
{
	return texCoords;
}

std::vector<glm::vec3> ImportedModel::getNormals() const
{
	return normalVec;
}

ModelImporter::ModelImporter()
{
}

void ModelImporter::parseOBJ(const char* filePath)
{
	float x, y, z;
	//std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	std::string line = "";

	while (!fileStream.eof())
	{
		std::getline(fileStream, line);

		if (line.compare(0, 2, "v ") == 0)
		{
			std::stringstream ss(line.erase(0, 1));
			ss >> x; ss >> y; ss >> z;

			vertVals.push_back(x);
			vertVals.push_back(y);
			vertVals.push_back(z);

		}
		if (line.compare(0, 2, "vt") == 0)
		{
			std::stringstream ss(line.erase(0, 2));
			ss >> x; ss >> y; 

			stVals.push_back(x);
			stVals.push_back(y);
		}
		if (line.compare(0, 2, "vn") == 0)
		{
			std::stringstream ss(line.erase(0, 2));
			ss >> x; ss >> y; ss >> z;

			normVals.push_back(x);
			normVals.push_back(y);
			normVals.push_back(z);

		}
		if (line.compare(0, 2, "f ") == 0)
		{
			const int indexCount = my_strlen(line.c_str(), ' ');

			std::string oneCorner, v, t, n;
			std::stringstream ss(line.erase(0, 2));

			int vertRef[4];
			int tcRef[4];
			int normRef[4];



			for (int i = 0; i < indexCount; i++)
			{
				std::getline(ss, oneCorner, ' ');
				std::stringstream oneCornerSS(oneCorner);

				std::getline(oneCornerSS, v, '/');
				std::getline(oneCornerSS, t, '/');
				std::getline(oneCornerSS, n, '/');

				vertRef[i] = (stoi(v) - 1) * 3;
				tcRef[i] = (stoi(t) - 1) * 2;
				normRef[i] = (stoi(n) - 1) * 3;

				


				printf("%d/%d/%d\n", stoi(v), stoi(t), stoi(n));
			}

			const int polygonCount = indexCount - 2;

			for (int i = 1; i <= polygonCount; i++)
			{
				triangleVerts.push_back(vertVals[vertRef[0]]);
				triangleVerts.push_back(vertVals[vertRef[0] + 1]);
				triangleVerts.push_back(vertVals[vertRef[0] + 2]);

				textureCoords.push_back(stVals[tcRef[0]]);
				textureCoords.push_back(stVals[tcRef[0] + 1]);

				normals.push_back(normVals[normRef[0]]);
				normals.push_back(normVals[normRef[0] + 1]);
				normals.push_back(normVals[normRef[0] + 2]);

				triangleVerts.push_back(vertVals[vertRef[i]]);
				triangleVerts.push_back(vertVals[vertRef[i] + 1]);
				triangleVerts.push_back(vertVals[vertRef[i] + 2]);

				textureCoords.push_back(stVals[tcRef[i]]);
				textureCoords.push_back(stVals[tcRef[i] + 1]);

				normals.push_back(normVals[normRef[i]]);
				normals.push_back(normVals[normRef[i] + 1]);
				normals.push_back(normVals[normRef[i] + 2]);

				triangleVerts.push_back(vertVals[vertRef[i + 1]]);
				triangleVerts.push_back(vertVals[vertRef[i + 1] + 1]);
				triangleVerts.push_back(vertVals[vertRef[i + 1] + 2]);

				textureCoords.push_back(stVals[tcRef[i + 1]]);
				textureCoords.push_back(stVals[tcRef[i + 1] + 1]);

				normals.push_back(normVals[normRef[i + 1]]);
				normals.push_back(normVals[normRef[i + 1] + 1]);
				normals.push_back(normVals[normRef[i + 1] + 2]);
			}

		}
	}

}

int ModelImporter::getNumVertices() const
{
	return (triangleVerts.size() / 3);
}

std::vector<float> ModelImporter::getVertices() const
{
	return triangleVerts;
}

std::vector<float> ModelImporter::getTextureCoordinates() const
{
	return textureCoords;
}

std::vector<float> ModelImporter::getNormals() const
{
	return normals;
}
