#include "math.h"

Quaternion Quat::Euler(const float& x, const float& y, const float& z)
{
    //x
    float yaw = glm::radians(x);// x* (PI / 180.0f);
    //y
    float pitch = glm::radians(y); //y * (PI / 180.0f);
    //z
    float roll = glm::radians(z); //z * (PI / 180.0f);


    Quaternion eulerRot = Quat::Identity;

    eulerRot.x = sin(roll / 2) * cos(pitch / 2) * cos(yaw / 2) - cos(roll / 2) * sin(pitch / 2) * sin(yaw / 2);
    eulerRot.y = cos(roll / 2) * sin(pitch / 2) * cos(yaw / 2) + sin(roll / 2) * cos(pitch / 2) * sin(yaw / 2);
    eulerRot.z = cos(roll / 2) * cos(pitch / 2) * sin(yaw / 2) - sin(roll / 2) * sin(pitch / 2) * cos(yaw / 2);
    eulerRot.w = cos(roll / 2) * cos(pitch / 2) * cos(yaw / 2) + sin(roll / 2) * sin(pitch / 2) * sin(yaw / 2);

    return eulerRot;
}

Quaternion Quat::Inverse(Quaternion value)
{

    Quaternion ans;

    float ls = value.x * value.x + value.y * value.y + value.z * value.z + value.w * value.w;
    float invNorm = 1.0f / ls;

    ans.x = -value.x * invNorm;
    ans.y = -value.y * invNorm;
    ans.z = -value.z * invNorm;
    ans.w = value.w * invNorm;

    return ans;
}

Quaternion Quat::Inverse(Vector3 eulers)
{

    Quaternion eulerRot = Quat::Identity;


    return Inverse(eulerRot);
}
