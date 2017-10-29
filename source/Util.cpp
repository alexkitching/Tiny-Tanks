//////////////////////////////////////////////////////////////////////////
// File: <Util.cpp>
// Author: <Alex Kitching>
// Date Created: <12/03/17>
// Brief: <Source file for Utility functions.>
/////////////////////////////////////////////////////////////////////////

#include "Util.h"
#include "UGFW.h"
#define _USE_MATH_DEFINES
#include <math.h>

// Converts Pixel Coordinates to UVW Coordinates
Vector4 SetSpriteUVCoords(const int a_iOriginX, const int a_iOriginY, const int a_iEndX, const int a_iEndY, const int a_iSheetWidth, const int a_iSheetHeight)
{
	return Vector4((float) a_iOriginX / a_iSheetWidth,(float) a_iOriginY / a_iSheetHeight,(float) a_iEndX / a_iSheetWidth,(float) a_iEndY / a_iSheetHeight);
}

// Centers Sprite Horizontally
float CenterSpriteHorizontal(const float a_fSpriteWidth, const float a_fScreenWidth)
{
	return ((a_fScreenWidth - a_fSpriteWidth ) / 2);
}

// Centers Sprite Vertically
float CenterSpriteVertical(const float a_fSpriteHeight, const float a_fScreenHeight)
{
	return ((a_fScreenHeight - a_fSpriteHeight ) / 2);
}

// Converts Degrees to Radians
float DegreestoRadians(const float a_fDegrees)
{
	return a_fDegrees * (float) M_PI / 180.f;
}
