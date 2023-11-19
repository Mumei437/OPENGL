#include "Transform.h"
#include<glm/gtx/quaternion.hpp>

Transform::Transform()
    :
    mPosition(Vec3::Zero),
    mScale(Vec3::One),
    mRotation(Quat::Identity)
{
}

Transform::~Transform()
{
}

void Transform::SetRotation(const float& x, const float& y, const float& z)
{

    //Šp“x‚©‚çƒ‰ƒWƒAƒ“‚É•ÏŠ·

    SetRotation(Quat::Euler(x, y, z));
}

void Transform::Rotate(const float& yaw, const float& pitch, const float& roll)
{
    Quaternion eulerRot = Quat::Euler(yaw, pitch, roll);

    mRotation = mRotation * (Quat::Inverse(mRotation) * eulerRot * mRotation);

    //Quaternion value = 
}

Matrix4 Transform::GetMatrix()
{

    Matrix4 trans = glm::translate(Mat4::Identity, mPosition);

    trans *= glm::toMat4(mRotation);

    trans *= glm::scale(Mat4::Identity, mScale);

    return trans;
}
