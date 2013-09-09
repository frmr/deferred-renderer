#include "InputState.h"

void InputState::ResetOneFrameKeys()
{
	jumpHeld = false;
	useHeld = false;
	healthHeld = false;
	resistHeld = false;
	talkHeld = false;
	exitHeld = false;
}

void InputState::ResetAll()
{
	forwardHeld = false;
	backwardHeld = false;
	leftHeld = false;
	rightHeld = false;
	sprintHeld = false;
	primaryFireHeld = false;
	secondaryFireHeld = false;
	tertiaryFireHeld = false;
	ResetOneFrameKeys();
	mouseChange.Reset();

}

void InputState::Update( sf::RenderWindow &window, const EngineConfig &engineCfg )
{
    ResetOneFrameKeys();
    mouseChange.Reset();

	sf::Event event;

	while ( window.pollEvent( event ) )
    {
        if ( event.type == sf::Event::KeyReleased )
        {
            if ( event.key.code == sf::Keyboard::W )            { forwardHeld = false; }
            else if ( event.key.code == sf::Keyboard::A )       { leftHeld = false; }
            else if ( event.key.code == sf::Keyboard::S )       { backwardHeld = false; }
            else if ( event.key.code == sf::Keyboard::D )       { rightHeld = false; }
            else if ( event.key.code == sf::Keyboard::Space )   { jumpHeld = false; }
            else if ( event.key.code == sf::Keyboard::LShift )  { sprintHeld = false; }

            //questionable mouse controls
            else if ( event.key.code == sf::Mouse::isButtonPressed( sf::Mouse::Left ) )     { primaryFireHeld = false; }
            else if ( event.key.code == sf::Mouse::isButtonPressed( sf::Mouse::Right ) )    { secondaryFireHeld = false; }
            else if ( event.key.code == sf::Mouse::isButtonPressed( sf::Mouse::Middle ) )   { tertiaryFireHeld = false; }
        }
        else if ( event.type == sf::Event::KeyPressed )
        {
            if ( event.key.code == sf::Keyboard::W )            { forwardHeld = true; }
            else if ( event.key.code == sf::Keyboard::A )       { leftHeld = true; }
            else if ( event.key.code == sf::Keyboard::S )       { backwardHeld = true; }
            else if ( event.key.code == sf::Keyboard::D )       { rightHeld = true; }
            else if ( event.key.code == sf::Keyboard::Space )   { jumpHeld = true; }
            else if ( event.key.code == sf::Keyboard::LShift )  { sprintHeld = true; }
            else if ( event.key.code == sf::Keyboard::E )       { useHeld = true; }
            else if ( event.key.code == sf::Keyboard::Num2 )    { healthHeld = true; }
            else if ( event.key.code == sf::Keyboard::Num3 )    { resistHeld = true; }
            else if ( event.key.code == sf::Keyboard::T )       { talkHeld = true; }
            else if ( event.key.code == sf::Keyboard::Escape )  { exitHeld = true; }

            else if ( event.key.code == sf::Mouse::isButtonPressed( sf::Mouse::Left ) )     { primaryFireHeld = true; }
            else if ( event.key.code == sf::Mouse::isButtonPressed( sf::Mouse::Right ) )    { secondaryFireHeld = true; }
            else if ( event.key.code == sf::Mouse::isButtonPressed( sf::Mouse::Middle ) )   { tertiaryFireHeld = true; }
        }
        else if ( event.type == sf::Event::MouseMoved )
        {
            mouseChange = frmr::Vec2f( engineCfg.GetActiveHeight() / 2 - event.mouseMove.y, engineCfg.GetActiveWidth() / 2 - event.mouseMove.x );
        }
        else if ( event.type == sf::Event::Closed )
        {
            exitHeld = true;
        }
    }

    sf::Mouse::setPosition( sf::Vector2i( engineCfg.GetActiveWidth() / 2, engineCfg.GetActiveHeight() / 2 ), window );
}

bool        InputState::GetForwardHeld() const 		    { return forwardHeld; }
bool        InputState::GetBackwardHeld() const 		{ return backwardHeld; }
bool        InputState::GetLeftHeld() const 			{ return leftHeld; }
bool        InputState::GetRightHeld() const 			{ return rightHeld; }
bool        InputState::GetDirectionHeld() const        { if ( forwardHeld || backwardHeld || leftHeld || rightHeld){ return true; } else { return false; } }
bool        InputState::GetJumpHeld() const 			{ return jumpHeld; }
bool        InputState::GetSprintHeld() const 			{ return sprintHeld; }
bool        InputState::GetUseHeld() const 			    { return useHeld; }
bool        InputState::GetHealthHeld() const 			{ return healthHeld; }
bool        InputState::GetResistHeld() const 			{ return resistHeld; }
bool        InputState::GetTalkHeld() const 			{ return talkHeld; }
bool        InputState::GetExitHeld() const 			{ return exitHeld; }
bool        InputState::GetPrimaryFireHeld() const 	    { return primaryFireHeld; }
bool        InputState::GetSecondaryFireHeld() const 	{ return secondaryFireHeld; }
bool        InputState::GetTertiaryFireHeld() const 	{ return tertiaryFireHeld; }
frmr::Vec2f InputState::GetMouseChange() const 		    { return mouseChange; }

InputState::InputState()
{
	ResetAll();
}

InputState::~InputState()
{
}
