#pragma once
#include"math.h"
class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(const Vector3& pos) { mPosition = pos; }
	Vector3 GetPosition()const { return mPosition; }
	void SetScale(const Vector3& scale) { mScale = scale; }
	Vector3 GetScale()const { return mScale; }

	void SetRotation(const Quaternion& roat) { mRotation = roat; }
	void SetRotation(const float& yaw = 0, const float& pitch = 0, const float& roll = 0);
	Quaternion GetRotation()const { return mRotation; }

	Matrix4 GetMatrix();

private:
	Vector3 mPosition;
	Vector3 mScale;
	Quaternion mRotation;
};

