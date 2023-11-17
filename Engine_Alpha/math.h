#pragma once
#include<cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#define GetMathPtr glm::value_ptr
#define GetPerspective glm::perspective
#define GetTranslate glm::translate
#define GetRotateMatrix glm::rotate
#define GetScaleMatrix glm::scale
#define PI 3.14159265358979

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef glm::vec4 Color;
typedef glm::mat4 Matrix4;
typedef glm::quat Quaternion;

//Vector2のライブラリ
namespace Vec2
{
	//Vector2のゼロベクトル
	static const Vector2 Zero(0, 0);
}

//Vector3のライブラリ
namespace Vec3
{
	//Vector3のゼロベクトル
	static const Vector3 Zero(0, 0, 0);
	static const Vector3 One(1, 1, 1);
	static const Vector3 Axis_X(1, 0, 0);
	static const Vector3 Axis_Y(0, 1, 0);
	static const Vector3 Axis_Z(0, 0, 1);
}

//Vector4のライブラリ
namespace Vec4
{
	//Vector4のゼロベクトル
	static const Vector4 Zero(0, 0, 0, 0);
}

namespace Mat4
{
	//Matrix4の単位行列
	static const Matrix4 Identity(1.0f);
}

namespace Quat
{
	static const Quaternion Identify(0, 0, 0, 1);
}