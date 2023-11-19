#pragma once

#include"OpenGL.h"
#include"math.h"
#include"Transform.h"

//レンダリングのクラス
class Renderer
{

public:
	//コンストラクタ(初期化処理)
	Renderer(const int width = 600, const int height = 600, const char* title = "Window1");
	//デストラクタ(終了処理)
	~Renderer();
	//継続するか否かの判定関数
	bool IsContinue()const;
	//レンダリングの実行
	void Run();
	//描画手順を指定
	void draw();
	//インターバルの間隔の設定
	void SetInterval(const int& interval) { mInterVal = interval; glfwSwapInterval(interval); }
	//背景色の設定
	void SetClearColor(float r, float g, float b, float a = 1.0) { glClearColor(r, g, b, a); }
	void SetClearColor(Color color) { SetClearColor(color.r, color.g, color.b, color.a); }
	void SetClearColor(Vector3 color) { SetClearColor(color.r, color.g, color.b); }


private:
	//ウィンドウのインスタンス

	class Window* mWindow;

	//ダブルバッファの入れ替えの間隔時間
	int mInterVal;

	class Shader* mShader;
	class Vertex* cube;
	class Vertex* pyramid;
	class Texture* mTexture;

	Vector3 CameraPos;
	Vector3 CubePos;
	Vector3 Pyra_Pos;

	Transform mTransform;
	Vector3 euler;

	float x;
	float x_speed;

	float y;
	float y_speed;

};

