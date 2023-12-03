#include "Torus.h"
#include "math.h"
#include"Transform.h"
#include<algorithm>

Torus::Torus(Renderer* renderer)
	:
	Shape(renderer)
{
	prec = 48;
	inner = 0.5f;
	outer = 0.2f;
	rot = Vec3::Zero;
}

Torus::Torus(Renderer* renderer, float innerRadius, float outerRadius, int precin)
	:
	Shape(renderer)
{
	prec = precin;
	inner = innerRadius;
	outer = outerRadius;
	rot = Vec3::Zero;
}

Torus::~Torus()
{
}

void Torus::Update(const float& deltaTime)
{
	rot.z += 20 * deltaTime;
	mTransform->SetRotation(rot);
}

void Torus::Init()
{
	std::vector<int> indices;
	std::vector<Vector3> vertices;
	std::vector<Vector2> texCoords;
	std::vector<Vector3> normals;
	std::vector<Vector3> sTangents;
	std::vector<Vector3> tTangents;

	int numVertices = (prec + 1) * (prec + 1);
	int numIndices = prec * prec * 6;

	vertices.resize(numVertices);
	std::fill(vertices.begin(), vertices.end(), Vector3());
	texCoords.resize(numVertices);
	std::fill(texCoords.begin(), texCoords.end(), Vector2());
	normals.resize(numVertices);
	std::fill(normals.begin(), normals.end(), Vector3());
	sTangents.resize(numVertices);
	std::fill(sTangents.begin(), sTangents.end(), Vector3());
	tTangents.resize(numVertices);
	std::fill(tTangents.begin(), tTangents.end(), Vector3());
	indices.resize(numIndices);
	std::fill(indices.begin(), indices.end(), 0);

	for (int i = 0; i < prec + 1; i++) {
		float amt = toRadians(i * 360.0f / prec);

		// build the ring by rotating points around the origin, then moving them outward
		glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::vec3 initPos(rMat * glm::vec4(0.0f, outer, 0.0f, 1.0f));
		vertices[i] = glm::vec3(initPos + glm::vec3(inner, 0.0f, 0.0f));

		// compute texture coordinates for each vertex on the ring
		texCoords[i] = glm::vec2(0.0f, ((float)i / (float)prec));

		// compute tangents and normals -- first tangent is Y-axis rotated around Z
		rMat = glm::rotate(glm::mat4(1.0f), amt + (3.14159f / 2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		tTangents[i] = glm::vec3(rMat * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
		sTangents[i] = glm::vec3(glm::vec3(0.0f, 0.0f, -1.0f)); // second tangent is -Z.
		normals[i] = glm::cross(tTangents[i], sTangents[i]); // their X-product is the normal.

	}

	for (int i = 0; i < prec + 1; i++) {
		for (int ring = 1; ring < prec + 1; ring++) {
			for (int vert = 0; vert < prec + 1; vert++) {
				// rotate the vertex positions of the original ring around the Y axis
				float amt = (float)(toRadians(ring * 360.0f / prec));
				glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
				vertices[ring * (prec + 1) + i] = glm::vec3(rMat * glm::vec4(vertices[i], 1.0f));
				// compute the texture coordinates for the vertices in the new rings
				texCoords[ring * (prec + 1) + vert] = (glm::vec2((float)ring * 2.0f / (float)prec, texCoords[vert].t));
				texCoords[ring * (prec + 1) + vert].s -= (float)(texCoords[ring * (prec + 1) + vert].s > 1 ? (int)texCoords[ring * (prec + 1) + vert].s : 0);
				texCoords[ring * (prec + 1) + vert].t -= (float)(texCoords[ring * (prec + 1) + vert].t > 1 ? (int)texCoords[ring * (prec + 1) + vert].t : 0);
				// rotate the tangent and bitangent vectors around the Y axis
				rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
				sTangents[ring * (prec + 1) + i] = glm::vec3(rMat * glm::vec4(sTangents[i], 1.0f));
				rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
				tTangents[ring * (prec + 1) + i] = glm::vec3(rMat * glm::vec4(tTangents[i], 1.0f));
				// rotate the normal vector around the Y axis
				rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
				normals[ring * (prec + 1) + i] = glm::vec3(rMat * glm::vec4(normals[i], 1.0f));
			}
		}
	}

	// calculate triangle indices corresponding to the two triangles built per vertex
	for (int ring = 0; ring < prec; ring++) {
		for (int vert = 0; vert < prec; vert++) {
			indices[((ring * prec + vert) * 2) * 3 + 0] = ring * (prec + 1) + vert;
			indices[((ring * prec + vert) * 2) * 3 + 1] = (ring + 1) * (prec + 1) + vert;
			indices[((ring * prec + vert) * 2) * 3 + 2] = ring * (prec + 1) + vert + 1;
			indices[((ring * prec + vert) * 2 + 1) * 3 + 0] = ring * (prec + 1) + vert + 1;
			indices[((ring * prec + vert) * 2 + 1) * 3 + 1] = (ring + 1) * (prec + 1) + vert;
			indices[((ring * prec + vert) * 2 + 1) * 3 + 2] = (ring + 1) * (prec + 1) + vert + 1;
		}
	}

	std::vector<float> pvalues;//頂点座標
	std::vector<float> tvalues;//テクスチャ座標
	std::vector<float> nvalues;//法線ベクトル

	for (int i = 0; i < numVertices; i++)
	{

		pvalues.push_back(vertices[i].x);
		pvalues.push_back(vertices[i].y);
		pvalues.push_back(vertices[i].z);

		tvalues.push_back(texCoords[i].s);
		tvalues.push_back(texCoords[i].t);

		nvalues.push_back(normals[i].x);
		nvalues.push_back(normals[i].y);
		nvalues.push_back(normals[i].z);

	}


	mVertex = new Vertex(&pvalues[0], pvalues.size() * 4, &tvalues[0], tvalues.size() * 4, &nvalues[0], nvalues.size() * 4, &indices[0], indices.size() * 4);
}
