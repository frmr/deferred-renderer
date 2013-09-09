#include "Camera.h"

#include <iostream>

using std::cout;
using std::endl;

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

    frmr::Vec3f velocityChange;

    if ( inputs.GetDirectionHeld() )
    {
        if ( inputs.GetForwardHeld() )
        {
            velocityChange += frmr::Vec3f( sin( ( rotation.GetY() + 180.0f ) * 0.01745 ), tan( rotation.GetX() * 0.01745 ), cos( ( rotation.GetY() + 180.0f ) * 0.01745 ) ).Unit();
        }
        if ( inputs.GetLeftHeld() )
        {
            velocityChange += frmr::Vec3f( sin( ( rotation.GetY() - 90.0f ) * 0.01745 ), 0.0f, cos( ( rotation.GetY() - 90.0f ) * 0.01745 ) ).Unit();
        }
        if ( inputs.GetBackwardHeld() )
        {
            velocityChange += frmr::Vec3f( sin( ( rotation.GetY() + 0.0f ) * 0.01745 ), tan( -rotation.GetX() * 0.01745 ), cos( ( rotation.GetY() + 0.0f ) * 0.01745 ) ).Unit();
        }
        if ( inputs.GetRightHeld() )
        {
            velocityChange += frmr::Vec3f( sin( ( rotation.GetY() + 90.0f ) * 0.01745 ), 0.0f, cos( ( rotation.GetY() + 90.0f ) * 0.01745 ) ).Unit();
        }
    }
    else
    {
        velocityChange = velocity * -1.0f;
    }

    velocityChange.Unit();
    velocityChange *= acceleration;

    if ( velocity.Length() <= velocityChange.Length() && !inputs.GetDirectionHeld() )
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

Camera::Camera( const string &name, const frmr::Vec3f &position, const frmr::Vec2f &rotation )
    : Actor( name, position, rotation, frmr::Vec3f() ),
      acceleration( 0.008f ),
      speedMax( 0.15f ),
      speed( 0.0f )
{
}
