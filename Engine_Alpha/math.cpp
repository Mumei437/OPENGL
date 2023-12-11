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


// GOLD material - ambient, diffuse, specular, and shininess
Vector4 Light::goldAmbient() { return Vector4(0.2473f, 0.1995f, 0.0745f, 1); }
Vector4 Light::goldDiffuse() { return Vector4(0.7516f, 0.6065f, 0.2265f, 1); }
Vector4 Light::goldSpecular() { return Vector4(0.6283f, 0.5559f, 0.3661f, 1); }
float Light::goldShininess() { return 51.2f; }

// SILVER material - ambient, diffuse, specular, and shininess
Vector4 Light::silverAmbient() { return Vector4(0.1923f, 0.1923f, 0.1923f, 1); }
Vector4 Light::silverDiffuse() { return Vector4(0.5075f, 0.5075f, 0.5075f, 1); }
Vector4 Light::silverSpecular() { return Vector4(0.5083f, 0.5083f, 0.5083f, 1); }
float Light::silverShininess() { return 51.2f; }

// BRONZE material - ambient, diffuse, specular, and shininess
Vector4 Light::bronzeAmbient() { return Vector4(0.2125f, 0.1275f, 0.0540f, 1 ); }
Vector4 Light::bronzeDiffuse() { return Vector4(0.7140f, 0.4284f, 0.1814f, 1); }
Vector4 Light::bronzeSpecular() { return Vector4(0.3936f, 0.2719f, 0.1667f, 1); }
float Light::bronzeShininess() { return 25.6f; }

