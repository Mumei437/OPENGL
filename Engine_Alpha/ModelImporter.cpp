#include "ModelImporter.h"
#include<fstream>
#include<sstream>

int my_strlen(const char* str, const char target)
{
	int len = 0;    // 文字数を数えるためのカウンタ
	while (*str != '\0')
	{
		if (*str == target)
		{
			++len;
		}
		str++;
	}
	return len;     // 文字数を返す
}

ModelImporter::ModelImporter(const char* filePath)
	:
	mState(error)
{
	LoadFile(filePath);
}

ModelImporter::~ModelImporter()
{
}

void ModelImporter::LoadFile(const char* filePath)
{
	float x, y, z;

	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("ERROR：この名前のファイルはありません：ファイル名(%s)\n", filePath);
	}

	std::vector<float> vertVals;
	std::vector<float> stVals;
	std::vector<float> normVals;

	std::string line;

	while (!fileStream.eof())
	{
		std::getline(fileStream, line);

		while (line[0] == ' ')
		{
			line.erase(0, 1);
		}

		if (line.compare(0, 2, "v ") == 0)
		{
			std::stringstream ss(line.erase(0, 1));

			ss >> x; ss >> y; ss >> z;

			vertVals.push_back(x);
			vertVals.push_back(y);
			vertVals.push_back(z);

		}
		else if (line.compare(0, 2, "vt") == 0)
		{
			std::stringstream ss(line.erase(0, 2));
			ss >> x; ss >> y;

			stVals.push_back(x);
			stVals.push_back(y);
		}
		else if (line.compare(0, 2, "vn") == 0)
		{
			std::stringstream ss(line.erase(0, 2));
			ss >> x; ss >> y; ss >> z;

			normVals.push_back(x);
			normVals.push_back(y);
			normVals.push_back(z);

		}
		else if (line.compare(0, 2, "f ") == 0)
		{
			const int indexCount = my_strlen(line.c_str(), '/') / 2;

			if (indexCount == 0)
			{
				indexCount == 1;
			}

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

				printf("%d/%d/%d\n", vertRef[i], tcRef[i], normRef[i]);
			}

			const int polygonCount = indexCount - 2;

			for (int i = 1; i <= polygonCount; i++)
			{
				mVertices.push_back(vertVals[vertRef[0]]);
				mVertices.push_back(vertVals[vertRef[0] + 1]);
				mVertices.push_back(vertVals[vertRef[0] + 2]);

				
				mTexCoords.push_back(stVals[tcRef[0]]);
				mTexCoords.push_back(stVals[tcRef[0] + 1]);

				mNormals.push_back(normVals[normRef[0]]);
				mNormals.push_back(normVals[normRef[0] + 1]);
				mNormals.push_back(normVals[normRef[0] + 2]);

				mVertices.push_back(vertVals[vertRef[i]]);
				mVertices.push_back(vertVals[vertRef[i] + 1]);
				mVertices.push_back(vertVals[vertRef[i] + 2]);

				mTexCoords.push_back(stVals[tcRef[i]]);
				mTexCoords.push_back(stVals[tcRef[i] + 1]);

				mNormals.push_back(normVals[normRef[i]]);
				mNormals.push_back(normVals[normRef[i] + 1]);
				mNormals.push_back(normVals[normRef[i] + 2]);

				mVertices.push_back(vertVals[vertRef[i + 1]]);
				mVertices.push_back(vertVals[vertRef[i + 1] + 1]);
				mVertices.push_back(vertVals[vertRef[i + 1] + 2]);

				mTexCoords.push_back(stVals[tcRef[i + 1]]);
				mTexCoords.push_back(stVals[tcRef[i + 1] + 1]);

				mNormals.push_back(normVals[normRef[i + 1]]);
				mNormals.push_back(normVals[normRef[i + 1] + 1]);
				mNormals.push_back(normVals[normRef[i + 1] + 2]);

			}
		}

	}

	if (mVertices.size() != 0)
	{
		mState |= enable_Vertex;
	}
	if (mTexCoords.size() != 0)
	{
		mState |= enable_TexCoords;
	}
	if (mNormals.size() != 0)
	{
		mState |= enable_Normals;
	}

}
