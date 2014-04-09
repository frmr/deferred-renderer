#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"
#include "InputState.h"

class Camera : public Entity
{
public:
    float       acceleration;
    float       speedMax;
    float       speed;
    frmr::Vec3f	viewVector;

private:
	void 		UpdateViewVector();

public:
    frmr::Vec3f GetViewVector() const;
    void        Update( const InputState &inputs, const float mouseSensitivity, const float deltaTime );


public:
    Camera( const string &name, const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int16_t zoneNum );
};

#endif // CAMERA_H
