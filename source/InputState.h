#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <SFML/Graphics.hpp>

#include "Config.h"
#include "frmr_vec2f.h"

class InputState
{
private:
	bool 	    forwardHeld;
	bool 	    backwardHeld;
	bool 	    leftHeld;
	bool 	    rightHeld;
	bool 	    jumpHeld;
	bool 	    sprintHeld;
	bool 	    useHeld;
	bool 	    healthHeld;
	bool 	    resistHeld;
	bool 	    talkHeld;
	bool 	    exitHeld;
    bool 	    primaryFireHeld;
	bool 	    secondaryFireHeld;
	bool 	    tertiaryFireHeld;
	frmr::Vec2f mouseChange;

public:
	void	    ResetOneFrameKeys(); //rename
	void	    ResetAll();
	void	    Update( sf::RenderWindow &window, const EngineConfig &engineCfg );

	bool 	    GetForwardHeld() const;
	bool 	    GetBackwardHeld() const;
	bool 	    GetLeftHeld() const;
	bool 	    GetRightHeld() const;
	bool        GetDirectionHeld() const;
	bool 	    GetJumpHeld() const;
	bool 	    GetSprintHeld() const;
	bool 	    GetUseHeld() const;
	bool 	    GetHealthHeld() const;
	bool 	    GetResistHeld() const;
	bool 	    GetTalkHeld() const;
	bool 	    GetExitHeld() const;
    bool 	    GetPrimaryFireHeld() const;
	bool 	    GetSecondaryFireHeld() const;
	bool 	    GetTertiaryFireHeld() const;
	frmr::Vec2f GetMouseChange() const;

public:
	InputState(); //binding config
	~InputState();
};

#endif
