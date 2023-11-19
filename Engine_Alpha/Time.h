#pragma once
class Time
{
public:
	static void Update();
	static void ShutDown();
	static float GetDeltaTime();
private:
private:
	static float mPreTime;
	static float mdeltaTime;
};

