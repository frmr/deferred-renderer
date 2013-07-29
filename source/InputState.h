#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include "frmr_vec2f.h"

class InputState
{
private:
	bool 	    forwardHeld;
	bool 	    backwardHeld;
	bool 	    leftHeld;
	bool 	    rightHeld;
	bool 	    jumpHeld;
	bool 	    speedHeld;
	bool 	    useHeld;
	bool 	    healthHeld;
	bool 	    resistHeld;
	bool 	    primaryFireHeld;
	bool 	    secondaryFireHeld;
	bool 	    tertiaryFireHeld;
	bool 	    talkHeld;
	bool 	    exitHeld;
	frmr::Vec2f mouseChange;

public:
	void	    ResetOneFrameKeys(); //rename
	void	    ResetAll();
	void	    Update();

	bool 	    GetForwardHeld() const;
	bool 	    GetBackwardHeld() const;
	bool 	    GetLeftHeld() const;
	bool 	    GetRightHeld() const;
	bool 	    GetJumpHeld() const;
	bool 	    GetSpeedHeld() const;
	bool 	    GetUseHeld() const;
	bool 	    GetHealthHeld() const;
	bool 	    GetResistHeld() const;
	bool 	    GetPrimaryFireHeld() const;
	bool 	    GetSecondaryFireHeld() const;
	bool 	    GetTertiaryFireHeld() const;
	bool 	    GetTalkHeld() const;
	bool 	    GetExitHeld() const;
	frmr::Vec2f GetMouseChange() const;

public:
	InputState(); //binding config
	~InputState();
};

#endif
