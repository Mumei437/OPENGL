#pragma once
#include"math.h"
class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(const Vector3& pos) { mPosition = pos; }
	void SetPosition(const float x, const float y, const float z) { mPosition = Vector3(x, y, z); }
	Vector3 GetPosition()const { return mPosition; }
	void SetScale(const Vector3& scale) { mScale = scale; }
	Vector3 GetScale()const { return mScale; }

	void SetRotation(const Quaternion& roat) { mRotation = roat; }
	void SetRotation(const Vector3 roatVec) { SetRotation(roatVec.x, roatVec.y, roatVec.z); }
	void SetRotation(const float& yaw = 0, const float& pitch = 0, const float& roll = 0);
	Quaternion GetRotation()const { return mRotation; }
	void Rotate(const float& yaw, const float& pitch, const float& roll);

	Matrix4 GetMatrix();

private:
	Vector3 mPosition;
	Vector3 mScale;
	Quaternion mRotation;
};

