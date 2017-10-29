//////////////////////////////////////////////////////////////////////////
// File: <AnimationController.cpp>
// Author: <Alex Kitching>
// Date Created: <21/05/17>
// Brief: <Source file for the Animation Controller class.>
/////////////////////////////////////////////////////////////////////////

#include "AnimationController.h"
#include "UGFW.h"

AnimationController::AnimationController() :
	// Initialise Variable List
	iIndex(0),
	fFrameTime(0.2f)
{
}

void AnimationController::Initialise(const int a_iSpriteID, Vector4 * a_v4SpriteFrames, const int a_iMaxFrames)
{
	// Assign Sprite Variables
	iSpriteID = a_iSpriteID;
	v4SpriteFrames = a_v4SpriteFrames;
	iMaxFrames = a_iMaxFrames - 1;
}

void AnimationController::UpdateAnimation(const float a_fDeltaTime)
{
	fFrameTime -= a_fDeltaTime; // Decrease Frame Time
	if (fFrameTime < 0.f) // Frame Time elapsed
	{
		if (iIndex < iMaxFrames) // Current Index is Less than max index
		{
			iIndex++; // Increment Index
		}
		else // Index is now Max Frame
		{
			iIndex = 0; // Reset Index
		}
		fFrameTime = 0.2f; // Reset Frame Time
		UG::SetSpriteUVCoordinates(iSpriteID, v4SpriteFrames[iIndex]); // Change Current UV Coordinates
	}
}

bool AnimationController::UpdateAnimationTrigger(const float a_fDeltaTime)
{
	fFrameTime -= a_fDeltaTime; // Decrease Frame Time
	if (fFrameTime < 0.f) // Frame Time Elapsed
	{
		if (iIndex < iMaxFrames) // Current Index is Less than max index
		{
			iIndex++; // Increment Index
		}
		else // Index is now Max Frame
		{
			return true; // Trigger - Animation Finished
		}
		fFrameTime = 0.2f; // Reset Frame Time
		UG::SetSpriteUVCoordinates(iSpriteID, v4SpriteFrames[iIndex]); // Change Current UV Coordinates
	}
	return false; // Don't Trigger - Animation not finished
}
