#ifndef SPECTATOR_H
#define SPECTATOR_H

#include "Camera.h"
#include "Entity.h"
#include "InputState.h"

class Spectator : public Entity
{
public:
    float       acceleration;
    float       speedMax;
    float       speed;
    frmr::Vec3f	viewVector;

private:
	void 		UpdateViewVector();

public:
	Camera		GetCamera() const;
    frmr::Vec3f GetViewVector() const;
    void        Update( const InputState &inputs, const float mouseSensitivity, const float deltaTime );


public:
    Spectator( const string &name, const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int16_t zoneNum );
};

#endif // CAMERA_H
