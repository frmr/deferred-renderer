#ifndef CAMERA_H
#define CAMERA_H

#include "Actor.h"
#include "InputState.h"

class Camera : public Actor
{
public:
    float       acceleration;
    float       speedMax;
    float       speed;

public:
    void Update( const InputState &inputs, const float mouseSensitivity, const float deltaTime );

public:
    Camera( const string &name, const frmr::Vec3f &position, const frmr::Vec2f &rotation );
};

#endif // CAMERA_H
