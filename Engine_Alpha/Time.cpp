#include "Time.h"
#include"OpenGL.h"

float Time::mPreTime = 0.0f;

float Time::mdeltaTime = 0.0f;

void Time::Update()
{

	mdeltaTime = static_cast<float>(glfwGetTime()) - mPreTime;

	mPreTime = glfwGetTime();

	if (mdeltaTime > 0.05f)
	{
		mdeltaTime = 0.05f;
	}

}

void Time::ShutDown()
{
}

float Time::GetDeltaTime()
{
	return mdeltaTime;
}
