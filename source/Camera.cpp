#include "Camera.h"

#include <iostream>
#include "frmr_math.h"

using std::cout;
using std::endl;

void Camera::UpdateViewVector()
{
	//viewVector = frmr::Vec3f( sin( ( rotation.GetY() + 180.0f ) * 0.01745f ), tan( rotation.GetX() * 0.01745f ), cos( ( rotation.GetY() + 180.0f ) * 0.01745f ) ).Unit();
	viewVector = frmr::CalculateVectorFromRotation( rotation.GetX(), rotation.GetY() );
}

frmr::Vec3f Camera::GetViewVector() const
{
    return viewVector;
}

void Camera::Update( const InputState &inputs, const float mouseSensitivity, const float deltaTime )
{
    rotation += inputs.GetMouseChange() * mouseSensitivity;

    //limit rotation on x-axis
    if ( rotation.GetX() < -89.9f )
    {
        rotation = frmr::Vec2f( -89.9f, rotation.GetY() );
    }
    else if ( rotation.GetX() > 89.9 )
    {
        rotation = frmr::Vec2f( 89.9f, rotation.GetY() );
    }

    //let rotation on y-axis loop around, always staying within 0-360 degrees
    if ( rotation.GetY() < 0.0f )
    {
        rotation = frmr::Vec2f( rotation.GetX(), 360.0f - rotation.GetY() );
    }
    else if ( rotation.GetY() >= 360.0f )
    {
        rotation = frmr::Vec2f( rotation.GetX(), rotation.GetY() - 360.0f );
    }

	UpdateViewVector();

    frmr::Vec3f velocityChange;
    bool buttonPressed = false;

    if ( inputs.GetDirectionHeld() )
    {
        if ( inputs.GetForwardHeld() && !inputs.GetBackwardHeld() )
        {
            buttonPressed = true;
            velocityChange += viewVector;
        }
        if ( inputs.GetLeftHeld() && !inputs.GetRightHeld() )
        {
            buttonPressed = true;
            velocityChange += frmr::CalculateVectorFromRotation( 0.0f, rotation.GetY() + 90.0f );
        }
        if ( inputs.GetBackwardHeld() && !inputs.GetForwardHeld() )
        {
            buttonPressed = true;
            velocityChange -= viewVector;
        }
        if ( inputs.GetRightHeld() && !inputs.GetLeftHeld() )
        {
            buttonPressed = true;
            velocityChange += frmr::CalculateVectorFromRotation( 0.0f, rotation.GetY() - 90.0f );
        }
    }
    //else
    if ( !buttonPressed )
    {
        velocityChange = velocity * -1.0f;
    }

    velocityChange.Unit();
    velocityChange *= acceleration;

    if ( velocity.Length() <= velocityChange.Length() && !buttonPressed )
    {
        velocity.Reset();
    }
    else
    {
        velocity += velocityChange;
        if ( velocity.Length() > speedMax )
        {
            velocity.Unit();
            velocity *= speedMax;
        }
    }

    ApplyVelocity( deltaTime );
}

Camera::Camera( const string &name, const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int16_t zoneNum )
    : Actor( name, position, rotation, frmr::Vec3f(), zoneNum ),
      acceleration( 0.008f ),
      speedMax( 0.15f ),
      speed( 0.0f ),
      viewVector()
{
}
