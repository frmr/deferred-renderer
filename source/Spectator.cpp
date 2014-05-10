#include "Spectator.h"

#include <iostream>
#include "frmr/frmrMath.h"

using std::cout;
using std::endl;

void Spectator::UpdateViewVector()
{
	viewVector = frmr::CalculateVectorFromRotation( rotation.GetX(), rotation.GetY() );
}

PerspectiveCamera Spectator::GetCamera() const
{
	return PerspectiveCamera( position, rotation, currentZoneNum, 75.0f, 120.0f / 75.0f );
}

frmr::Vec3f Spectator::GetViewVector() const
{
    return viewVector;
}

void Spectator::Update( const InputState &inputs, const float mouseSensitivity, const float deltaTime )
{
    rotation += frmr::Vec2f( inputs.GetMouseChange().GetY() * mouseSensitivity, inputs.GetMouseChange().GetX() * mouseSensitivity );

    //limit rotation on x-axis
    if ( rotation.GetX() < -89.9f )
    {
        rotation.Set( -89.9f, rotation.GetY() );
    }
    else if ( rotation.GetX() > 89.9 )
    {
        rotation.Set( 89.9f, rotation.GetY() );
    }

    //let rotation on y-axis loop around, always staying within 0-360 degrees
    if ( rotation.GetY() < 0.0f )
    {
        rotation.Set( rotation.GetX(), 360.0f - rotation.GetY() );
    }
    else if ( rotation.GetY() >= 360.0f )
    {
        rotation.Set( rotation.GetX(), rotation.GetY() - 360.0f );
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
    //cout << position.GetX() << " " << position.GetY() << " " << position.GetZ() << endl;
    //cout << viewVector.GetX() << " " << viewVector.GetY() << " " << viewVector.GetZ() << endl;
    //cout << rotation.GetX() << " " << rotation.GetY() << endl;
}

Spectator::Spectator( const string &name, const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int16_t zoneNum )
    : Entity( name, position, rotation, frmr::Vec3f(), zoneNum ),
      acceleration( 0.008f ),
      speedMax( 0.15f ),
      speed( 0.0f ),
      viewVector()
{
}
