#include "Window.h"
#include<cstdlib>

int Window::WinWidth = 0;
int Window::WinHeight = 0;

Window::Window(const int width, const int height, const char* title, GLFWmonitor* monitor, GLFWwindow* window)
	:
	mWindow(nullptr)
{
	mWindow = glfwCreateWindow(width, height, title, monitor, window);//ウィンドウの作成
	if (!mWindow)//もし、ウィンドウの作成に失敗すれば
	{
		exit(EXIT_FAILURE);//終了
	}
	glfwMakeContextCurrent(mWindow);//作成したウィンドウをOpenGLの処理の対象に指定

	if (glewInit() != GLEW_OK)//GLEWの初期化
	{
		exit(EXIT_FAILURE);//失敗したら、強制終了
	}
	glfwSwapInterval(1);//垂直同期のバッファの入れ替えの間隔の指定

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
	// フレームバッファ全体をビューポートに設定する
	glViewport(0, 0, WinWidth, WinHeight);
}
