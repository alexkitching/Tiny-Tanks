//////////////////////////////////////////////////////////////////////////
// File: <AnimationController.h>
// Author: <Alex Kitching>
// Date Created: <21/5/17>
// Brief: <Header file for the Animation Controller class, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _ANIMATIONCONTROLLER_H_
#define _ANIMATIONCONTROLLER_H_

#include "Vector4.h"

class AnimationController
{
public:
	AnimationController();
	~AnimationController() {};
	void Initialise(const int a_iSpriteID, Vector4* a_v4SpriteFrames, const int a_iMaxFrames);
	void UpdateAnimation(const float a_fDeltaTime);
	bool UpdateAnimationTrigger(const float a_fDeltaTime);
private:
	// Sprite Variables
	int iSpriteID;
	int iMaxFrames;
	Vector4* v4SpriteFrames;

	// Animation Variables
	int iIndex;
	float fFrameTime;

};

#endif // !_ANIMATIONCONTROLLER_H_
