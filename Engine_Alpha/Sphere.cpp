#include "Sphere.h"
#include"Renderer.h"
#include"math.h"
#include"Vertex.h"
#include<vector>

Sphere::Sphere(Renderer* renderer)
	:
	Shape(renderer)
{
	mPrec = 48;
}

Sphere::~Sphere()
{

}

Sphere::Sphere(Renderer* renderer, const int& prec)
	:
	Shape(renderer)
{
	mPrec = prec;
}

void Sphere::Init()
{

	unsigned int numVertices = (mPrec + 1) * (mPrec + 1);
	unsigned int numInidices = mPrec * mPrec * 6;

	std::vector<Vector3> vertices;
	std::vector<Vector2> texCoords;
	std::vector<Vector3> normals;
	std::vector<int> indices;


	for (int i = 0; i < numVertices; i++) { vertices.push_back(glm::vec3()); }
	for (int i = 0; i < numVertices; i++) { texCoords.push_back(glm::vec2()); }
	for (int i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); }
	for (int i = 0; i < numInidices; i++) { indices.push_back(0); }

	//球体の頂点の情報の計算と作成
	for (int i = 0; i <= mPrec; i++)
	{
		for (int j = 0; j <= mPrec; j++)
		{
			float y = (float)cos(glm::radians(180.0f - i * 180.0f / mPrec));
			float x = -(float)cos(glm::radians(j * 360.0f / mPrec)) * (float)abs(cos(asin(y)));
			float z = (float)sin(glm::radians(j * 360.0f / mPrec)) * (float)abs(cos(asin(y)));

			vertices[i * (mPrec + 1) + j] = glm::vec3(x, y, z);
			texCoords[i * (mPrec + 1) + j] = glm::vec2(((float)j / mPrec), ((float)i / mPrec));
			normals[i * (mPrec + 1) + j] = glm::vec3(x, y, z);

		}
	}

	//球体の頂点のインデックスの作成
	for (int i = 0; i < mPrec; i++)
	{
		for (int j = 0; j < mPrec; j++)
		{

			indices[6 * (i * mPrec + j) + 0] = i * (mPrec + 1) + j;
			indices[6 * (i * mPrec + j) + 1] = i * (mPrec + 1) + j + 1;
			indices[6 * (i * mPrec + j) + 2] = (i + 1) * (mPrec + 1) + j;
			indices[6 * (i * mPrec + j) + 3] = i * (mPrec + 1) + j + 1;
			indices[6 * (i * mPrec + j) + 4] = (i + 1) * (mPrec + 1) + j + 1;
			indices[6 * (i * mPrec + j) + 5] = (i + 1) * (mPrec + 1) + j;

		}
	}

	std::vector<float> pvalues;//頂点座標
	std::vector<float> tvalues;//テクスチャ座標
	std::vector<float> nvalues;//法線ベクトル

	for (int i = 0; i < numInidices; i++)
	{
		pvalues.push_back((vertices[indices[i]]).x);
		pvalues.push_back((vertices[indices[i]]).y);
		pvalues.push_back((vertices[indices[i]]).z);

		tvalues.push_back((texCoords[indices[i]]).s);
		tvalues.push_back((texCoords[indices[i]]).t);

		nvalues.push_back((normals[indices[i]]).x);
		nvalues.push_back((normals[indices[i]]).y);
		nvalues.push_back((normals[indices[i]]).z);

	}

	mVertex = new Vertex(&pvalues[0], pvalues.size() * 4, &tvalues[0], tvalues.size() * 4, &nvalues[0], nvalues.size() * 4);

}
