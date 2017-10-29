//////////////////////////////////////////////////////////////////////////
// File: <Util.h>
// Author: <Alex Kitching>
// Date Created: <12/03/17>
// Brief: <Header file for Utility functions.>
/////////////////////////////////////////////////////////////////////////

#ifndef _UTIL_H_
#define _UTIL_H_

#include "Vector4.h"

Vector4 SetSpriteUVCoords(const int a_iOriginX, const int a_iOriginY, const int a_iEndX, const int a_iEndY, const int a_iSheetWidth, const int a_iSheetHeight);
float CenterSpriteHorizontal(const float a_fSpriteWidth, const float a_fScreenWidth);
float CenterSpriteVertical(const float a_fSpriteHeight, const float a_fScreenHeight);
float DegreestoRadians(const float a_fDegrees);

#endif // !_UTIL_H_

