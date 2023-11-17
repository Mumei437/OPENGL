#include "Transform.h"
#include<glm/gtx/quaternion.hpp>

Transform::Transform()
    :
    mPosition(Vec3::Zero),
    mScale(Vec3::One),
    mRotation(Quat::Identify)
{
}

Transform::~Transform()
{
}

void Transform::SetRotation(const float& x, const float& y, const float& z)
{

    //Šp“x‚©‚çƒ‰ƒWƒAƒ“‚É•ÏŠ·
    
    //x
    float yaw = x * (PI / 180.0f);
    //y
    float pitch = y * (PI / 180.0f);
    //z
    float roll = z * (PI / 180.0f);


    Quaternion rotation = Quat::Identify;

    rotation.x = sin(roll / 2) * cos(pitch / 2) * cos(yaw / 2) - cos(roll / 2) * sin(pitch / 2) * sin(yaw / 2);
    rotation.y = cos(roll / 2) * sin(pitch / 2) * cos(yaw / 2) + sin(roll / 2) * cos(pitch / 2) * sin(yaw / 2);
    rotation.z = cos(roll / 2) * cos(pitch / 2) * sin(yaw / 2) - sin(roll / 2) * sin(pitch / 2) * cos(yaw / 2);
    rotation.w = cos(roll / 2) * cos(pitch / 2) * cos(yaw / 2) + sin(roll / 2) * sin(pitch / 2) * sin(yaw / 2);

    SetRotation(rotation);
}

Matrix4 Transform::GetMatrix()
{

    Matrix4 trans = glm::translate(Mat4::Identity, mPosition);

    trans *= glm::toMat4(mRotation);

    trans *= glm::scale(Mat4::Identity, mScale);

    return trans;
}
