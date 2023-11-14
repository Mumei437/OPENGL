#pragma once
#include"OpenGL.h"
class Window
{
public:
	Window(const int width, const int height, const char* title, GLFWmonitor* monitor, GLFWwindow* window);
	~Window();

	GLFWwindow* GetWindow()const { return mWindow; }

	void SetInterval(unsigned int interval);

	

	static int GetWidth() { return WinWidth; }
	static int GetHeight() { return WinHeight; }

private:
	static void ReshapeWindow(GLFWwindow* window, int w, int h);

private:
	GLFWwindow* mWindow;

private:

	static int WinWidth;
	static int WinHeight;

};

