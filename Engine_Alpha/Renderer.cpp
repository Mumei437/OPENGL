#include "Renderer.h"
#include<iostream>
#include<cstdlib>
#include<stack>
#include"Shader.h"
#include"Vertex.h"
#include"Window.h"
#include"Texture.h"
#include"Transform.h"
#include"Time.h"
#include"Shape.h"
#include"Pyramid.h"
#include"Cube.h"
#include"Sphere.h"
#include"Torus.h"
#include"Model.h"
#include"math.h"
//白い照明

//マテリアルプロパティ
Vector4 matAmb = Light::goldAmbient();
Vector4 matDif = Light::goldDiffuse();
Vector4 matSpe = Light::goldSpecular();
float matShi = Light::goldShininess();

Renderer::Renderer(const int width, const int height, const char* title)
	:
	mInterVal(1),//インターバルは1
	mWindow(nullptr),//からなのでヌルポインタ
	x(0.0f),
	x_speed(0.01f),
	y(0.0f),
	y_speed(0.02f)
{

	if (!glfwInit())//glfwライブラリの初期化
	{
		exit(EXIT_FAILURE);//失敗時の終了処理
	}

	//終了処理をする際の関数の設定
	atexit(glfwTerminate);

	//OpenGLのバージョン設定(4.3に指定)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	mWindow = new Window(width, height, title, NULL, NULL);

	SetClearColor(Vec3::Zero);//背景色の設定(最初は真っ黒)

	mShader = new Shader("shaders/Texture.vert", "shaders/Texture.frag");

	mPhongShader = new Shader("shaders/phong.vert", "shaders/phong.frag");

	//キューブの頂点
	float vertexPositions[108] = {
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

	float pyramidPositions[] = {
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // front face
		1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // right face
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // back face
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // left face
		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, // base – left front
		1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, // base – right back
	};

	float pyramidTexCoords[] = {
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, // top and right faces
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, // back and left face
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0, //  base triangles
	};

	


	CameraPos = Vector3(0.f, 0.f, 10.f);
	CubePos = Vector3(-2.0f, 0.0f, 0.0f);
	Pyra_Pos = Vector3(2.0f, 0.0f, 0.0f);

	mTransform.SetPosition(Vector3(1, 0, 0));
	mTransform.SetScale(Vector3(2));


	cube = new Vertex(vertexPositions, sizeof(vertexPositions));
	pyramid = new Vertex(pyramidPositions, sizeof(pyramidPositions), pyramidTexCoords, sizeof(pyramidTexCoords));

	mVertexs.push_back(new Vertex(pyramidPositions, sizeof(pyramidPositions), pyramidTexCoords, sizeof(pyramidTexCoords)));

	mTexture = new Texture("Textures/itimatsu.png");

	euler = Vec3::Zero;

	Load();

}

void Renderer::Load()
{

	Sphere* sphere = new Sphere(this);
	sphere->Init();
	sphere->GetTransform()->SetPosition(0, 0, 0);
	sphere->GetTexture()->SetTexture("Textures/el_global.png");

	Torus* torus = new Torus(this);
	torus->Init();
	torus->GetTransform()->SetPosition(0, -2, 0);
	torus->GetTexture()->SetTexture("Textures/itimatsu.png");

	Model* akyo = new Model(this, "models/Akyo.obj");
	akyo->Init();
	akyo->GetTransform()->SetPosition(0, 2, 0);
	akyo->GetTexture()->SetTexture("Textures/tex_akyo.png");


}

Renderer::~Renderer()
{

	delete mShader;
	delete cube;
	delete pyramid;
	delete mWindow;
	delete mTexture;


	while (!mVertexs.empty())
	{
		delete mVertexs.back();
		mVertexs.pop_back();
	}

	while (!mShapes.empty())
	{
		delete mShapes.back();
		mShapes.pop_back();
	}

}

bool Renderer::IsContinue() const
{
	return !glfwWindowShouldClose(mWindow->GetWindow());//ウィンドウが閉じているかどうか判定(閉じていなければ継続)
}

void Renderer::Run()
{
	Time::Update();

	const float deltaTime = Time::GetDeltaTime();

	for (auto shape : mShapes)
	{
		shape->Update(deltaTime);
	}

	glClear(GL_DEPTH_BUFFER_BIT);//深度バッファの初期化
	glClear(GL_COLOR_BUFFER_BIT);//背景色で初期化

	draw();//ここに描画方法を書く

	glfwSwapBuffers(mWindow->GetWindow());//ダブバッファの入れ替え
	glfwPollEvents();//イベントの取り出し
}

void Renderer::draw()
{

	//float currentTime = (float)glfwGetTime();

	glEnable(GL_CULL_FACE);
	

	int width = Window::GetWidth(), height = Window::GetHeight();

	GLFWwindow* window = mWindow->GetWindow();

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		CameraPos.z -= 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		CameraPos.z += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		CameraPos.x -= 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		CameraPos.x += 0.1f;
	}

	//視点行列の構築
	float aspect = (float)width / (float)height;
	Matrix4 pMat = GetPerspective(1.0472f, aspect, 0.1f, 1000.0f);
	Matrix4 vMat = glm::translate(Mat4::Identity, CameraPos * -1.f);

	// 現在時刻を使用して、x、y、zのさまざまな平行移動を計算する。
	
	std::stack<Matrix4> mvStack;
	mvStack.push(vMat);

	//ピラミッドオブジェクト(太陽)
	mvStack.push(mvStack.top());
	mvStack.top() *= GetTranslate(Mat4::Identity, Pyra_Pos);
	mvStack.push(mvStack.top());
	//mvStack.top() *= GetRotateMatrix(Mat4::Identity, (float)currentTime, Vec3::Axis_Z);

	//mTransform.Rotate(4, 8, 12);

	euler.z += 70 * Time::GetDeltaTime() * -1.f;
	//euler.y += 50 * Time::GetDeltaTime();


	for (auto shape : mShapes)
	{

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		//glFrontFace(GL_CCW);

		if (shape->GetVertexState(Vertex::enVertex))
		{
			if (shape->GetVertexState(Vertex::enNormal))
			{
				mPhongShader->Use();

				Matrix4 mvMat = vMat * shape->GetTransform()->GetMatrix();
				Matrix4 invtrMat = glm::transpose(glm::inverse(mvMat));

				mPhongShader->setMatrix4("view_matrix", vMat);
				mPhongShader->setMatrix4("model_matrix", shape->GetTransform()->GetMatrix());
				mPhongShader->setMatrix4("proj_matrix", pMat);
				mPhongShader->setMatrix4("norm_matrix", invtrMat);

				const Vector4 globalAmbient(0.1f, 0.1f, 0.1f, 1.0f);
				const Vector4 lightAmbient(0.0f, 0.0f, 0.0f, 1.0f);
				const Vector4 lightDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
				const Vector4 lightSpecular(1.0f, 1.0f, 1.0f, 1.0f);

				Vector3 lightPos(0.0f, 5.0f, 10.0f);

				const Vector3 lightPosV = Vector3(vMat * Vector4(lightPos, 1.0));



				mPhongShader->setVector4("globalAmbient", globalAmbient);
				mPhongShader->setVector4("light.ambient", lightAmbient);
				mPhongShader->setVector4("light.diffuse", lightDiffuse);
				mPhongShader->setVector4("light.specular", lightSpecular);
				mPhongShader->setVector3("light.position", lightPosV);
				mPhongShader->setVector4("material.ambient", lightAmbient);
				mPhongShader->setVector4("material.diffuse", lightDiffuse);
				mPhongShader->setVector4("material.specular", lightSpecular);
				mPhongShader->setVector3("material.shininess", lightPosV);

				shape->Active(0, 1, 2);
				shape->GetTexture()->setActive();

				if (shape->GetVertexState(Vertex::enIndex))
				{
					glDrawElements(GL_TRIANGLES, shape->GetIndexCount(), GL_UNSIGNED_INT, 0);
				}
				else
				{
					glDrawArrays(GL_TRIANGLES, 0, shape->GetVertCount());//ピラミッドを描画
				}
			}
			else
			{
				mShader->Use();
				shape->Active(0, 1, 2);
				shape->GetTexture()->setActive();
				mShader->setMatrix4("view_matrix", vMat);
				mShader->setMatrix4("model_matrix", shape->GetTransform()->GetMatrix());
				mShader->setMatrix4("proj_matrix", pMat);
				if (shape->GetVertexState(Vertex::enIndex))
				{
					glDrawElements(GL_TRIANGLES, shape->GetIndexCount(), GL_UNSIGNED_INT, 0);
				}
				else
				{
					glDrawArrays(GL_TRIANGLES, 0, shape->GetVertCount());//ピラミッドを描画
				}
			}
		}
		else
		{
			printf("エラー：頂点情報がありません。\n");
		}
		
	}
	mvStack.pop();
	

	while (mvStack.size() > 0)
	{
		mvStack.pop();
	}

	// mvStack.pop(); mvStack.pop(); mvStack.pop();


}

void Renderer::AddShape(Shape* shape)
{
	mShapes.emplace_back(shape);

}

void Renderer::RemoveShape(const Shape* shape)
{
	
	auto iter = std::find(mShapes.begin(), mShapes.end(), shape);

	if (iter != mShapes.end())
	{
		mShapes.erase(iter);
	}

}
