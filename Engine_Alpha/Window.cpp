#include "Window.h"
#include<cstdlib>

int Window::WinWidth = 0;
int Window::WinHeight = 0;

Window::Window(const int width, const int height, const char* title, GLFWmonitor* monitor, GLFWwindow* window)
	:
	mWindow(nullptr)
{
	mWindow = glfwCreateWindow(width, height, title, monitor, window);//�E�B���h�E�̍쐬
	if (!mWindow)//�����A�E�B���h�E�̍쐬�Ɏ��s�����
	{
		exit(EXIT_FAILURE);//�I��
	}
	glfwMakeContextCurrent(mWindow);//�쐬�����E�B���h�E��OpenGL�̏����̑ΏۂɎw��

	if (glewInit() != GLEW_OK)//GLEW�̏�����
	{
		exit(EXIT_FAILURE);//���s������A�����I��
	}
	glfwSwapInterval(1);//���������̃o�b�t�@�̓���ւ��̊Ԋu�̎w��

	WinWidth = width;
	WinHeight = height;

	glfwSetWindowSizeCallback(mWindow, ReshapeWindow);

}

Window::~Window()
{

}

void Window::SetInterval(unsigned int interval)
{
	glfwSwapInterval(interval);
}

void Window::ReshapeWindow(GLFWwindow* window, int w, int h)
{
	glfwGetFramebufferSize(window, &WinWidth, &WinHeight);
	// �t���[���o�b�t�@�S�̂��r���[�|�[�g�ɐݒ肷��
	glViewport(0, 0, WinWidth, WinHeight);
}
