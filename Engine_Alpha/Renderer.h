#pragma once

#include"OpenGL.h"
#include"math.h"
#include"Transform.h"

//�����_�����O�̃N���X
class Renderer
{

public:
	//�R���X�g���N�^(����������)
	Renderer(const int width = 600, const int height = 600, const char* title = "Window1");
	//�f�X�g���N�^(�I������)
	~Renderer();
	//�p�����邩�ۂ��̔���֐�
	bool IsContinue()const;
	//�����_�����O�̎��s
	void Run();
	//�`��菇���w��
	void draw();
	//�C���^�[�o���̊Ԋu�̐ݒ�
	void SetInterval(const int& interval) { mInterVal = interval; glfwSwapInterval(interval); }
	//�w�i�F�̐ݒ�
	void SetClearColor(float r, float g, float b, float a = 1.0) { glClearColor(r, g, b, a); }
	void SetClearColor(Color color) { SetClearColor(color.r, color.g, color.b, color.a); }
	void SetClearColor(Vector3 color) { SetClearColor(color.r, color.g, color.b); }


private:
	//�E�B���h�E�̃C���X�^���X

	class Window* mWindow;

	//�_�u���o�b�t�@�̓���ւ��̊Ԋu����
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

