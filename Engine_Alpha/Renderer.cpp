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

	Pyramid* pyramid = new Pyramid();
	pyramid->Init();

	pyramid->GetTransform()->SetPosition(Vector3(1, 1, 0));
	pyramid->GetTransform()->SetScale(Vector3(2));
	pyramid->GetTransform()->SetRotation(0, 20, 0);

	AddShape(pyramid);

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

	glClear(GL_DEPTH_BUFFER_BIT);//深度バッファの初期化
	glClear(GL_COLOR_BUFFER_BIT);//背景色で初期化

	draw();//ここに描画方法を書く

	glfwSwapBuffers(mWindow->GetWindow());//ダブバッファの入れ替え
	glfwPollEvents();//イベントの取り出し
}

void Renderer::draw()
{

	//float currentTime = (float)glfwGetTime();

	//glEnable(GL_CULL_FACE);
	mShader->Use();

	int width = Window::GetWidth(), height = Window::GetHeight();

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

		shape->Active(0, 1, 2);
		mTexture->setActive();
		mShader->setMatrix4("view_matrix", vMat);
		mShader->setMatrix4("model_matrix", shape->GetTransform()->GetMatrix());
		mShader->setMatrix4("proj_matrix", pMat);

	}
	
	/*
	for (auto vertex : mVertexs)
	{
		mTransform.SetRotation(euler);
		vertex->Active(0, 1, 0);

		mTexture->setActive();

		mShader->setMatrix4("view_matrix", vMat);
		mShader->setMatrix4("model_matrix", mTransform.GetMatrix());
		mShader->setMatrix4("proj_matrix", pMat);

	}
	*/
	


	
	
	/*
	pyramid->VertexActive();
	pyramid->TexCoordActive(1);

	mTexture->setActive();
	*/

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glFrontFace(GL_CCW);
	glDrawArrays(GL_TRIANGLES, 0, pyramid->GetVertexCount());//ピラミッドを描画
	mvStack.pop();

	/*
	//子オブジェクトの正方形(惑星)の描画
	mvStack.push(mvStack.top());
	mvStack.top() *= GetTranslate(Mat4::Identity, Vector3(sin((float)currentTime) * 4.0f, 0.0f, cos((float)currentTime) * 4.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= GetRotateMatrix(Mat4::Identity, (float)currentTime, Vec3::Axis_Y);

	mShader->setMatrix4("mv_matrix", mvStack.top());

	cube->VertexActive();

	glFrontFace(GL_CW);
	glDrawArrays(GL_TRIANGLES, 0, cube->GetVertexCount());
	mvStack.pop();//惑星の軸回転をスタックから取り除く

	//
	mvStack.push(mvStack.top());
	mvStack.top() *= GetTranslate(Mat4::Identity, Vector3(0.0f, sin((float)currentTime) * 2.0f, cos((float)currentTime) * 2.0f));
	mvStack.top() *= GetRotateMatrix(Mat4::Identity, (float)currentTime, Vec3::Axis_Z);
	mvStack.top() *= GetScaleMatrix(Mat4::Identity, Vector3(0.25f));

	mShader->setMatrix4("mv_matrix", mvStack.top());
	cube->VertexActive();

	glFrontFace(GL_CW);
	glDrawArrays(GL_TRIANGLES, 0, cube->GetVertexCount());
	*/
	//すべての要素を取り除く

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
