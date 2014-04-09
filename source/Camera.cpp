#include "Camera.h"

#include <iostream>
#include "frmr/frmrMath.h"

using std::cout;
using std::endl;

void Camera::UpdateViewVector()
{
	viewVector = frmr::CalculateVectorFromRotation( rotation.GetX(), rotation.GetY() );
}

frmr::Vec3f Camera::GetViewVector() const
{
    return viewVector;
}

void Camera::Update( const InputState &inputs, const float mouseSensitivity, const float deltaTime )
{
    rotation += frmr::Vec3f( inputs.GetMouseChange().GetY() * mouseSensitivity, inputs.GetMouseChange().GetX() * mouseSensitivity, 0.0f );

    //limit rotation on x-axis
    if ( rotation.GetX() < -89.9f )
    {
        rotation.Set( -89.9f, rotation.GetY(), 0.0f );
    }
    else if ( rotation.GetX() > 89.9 )
    {
        rotation.Set( 89.9f, rotation.GetY(), 0.0f );
    }

    //let rotation on y-axis loop around, always staying within 0-360 degrees
    if ( rotation.GetY() < 0.0f )
    {
        rotation.Set( rotation.GetX(), 360.0f - rotation.GetY(), 0.0f );
    }
    else if ( rotation.GetY() >= 360.0f )
    {
        rotation.Set( rotation.GetX(), rotation.GetY() - 360.0f, 0.0f );
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

Camera::Camera( const string &name, const frmr::Vec3f &position, const frmr::Vec3f &rotation, const int16_t zoneNum )
    : Actor( name, position, rotation, frmr::Vec3f(), zoneNum ),
      acceleration( 0.008f ),
      speedMax( 0.15f ),
      speed( 0.0f ),
      viewVector()
{
}
