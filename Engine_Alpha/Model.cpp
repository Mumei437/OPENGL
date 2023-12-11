#include "Model.h"
#include "Renderer.h"
#include "ModelImporter.h"
#include "Vertex.h"
#include<cstdio>

Model::Model(Renderer* renderer, const char* filePath)
	:
	Shape(renderer)
{
	
	ModelImporter mi(filePath);

	if (mi.GetEnable(ModelImporter::enable_Vertex))
	{
		if (mi.GetEnable(ModelImporter::enable_Normals | ModelImporter::enable_TexCoords))
		{
			mVertex = new Vertex(&mi.GetVertices()[0], mi.GetVertSize(), &mi.GetTexCoords()[0], mi.GetTexCoordsSize(), &mi.GetNormals()[0], mi.GetNoramalsSize());
		}
		else if (mi.GetEnable(ModelImporter::enable_TexCoords))
		{
			mVertex = new Vertex(&mi.GetVertices()[0], mi.GetVertSize(), &mi.GetTexCoords()[0], mi.GetTexCoordsSize());
		}
		else if (mi.GetEnable(ModelImporter::enable_Normals))
		{
			mVertex = new Vertex();
			mVertex->SetVertex(&mi.GetVertices()[0], mi.GetVertSize());
			mVertex->SetNormals(&mi.GetNormals()[0], mi.GetNoramalsSize());
		}
		else
		{
			mVertex = new Vertex(&mi.GetVertices()[0], mi.GetVertSize());
		}
	}
	else
	{
		printf("エラー：モデルの作成に失敗しました。\n");
	}

}

Model::~Model()
{
}
