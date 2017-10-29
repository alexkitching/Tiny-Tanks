//////////////////////////////////////////////////////////////////////////
// File: <Menu.h>
// Author: <Alex Kitching>
// Date Created: <12/03/17>
// Brief: <Header file for all Menu classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _Menu_H_
#define _Menu_H_

#include "Vector2.h";
#include "Vector3.h";
#include "Vector4.h";

extern int g_iScreenHeight;
extern int g_iScreenWidth;

class Menu
{
public:
	Menu(); // Constructor
	~Menu() {}; // Destructor

	// Functions
	void Update(float a_fDeltaTime);
	void Initialise();

private:
	// Functions
	void SetNavigationKeys(short a_upKey, short a_downKey, short a_enterKey, short a_spaceKey);
	void Destroy();

	// Sprite Image Definition
	// File Names
	char const c_acBackgroundFileName[29];
	char const c_acMenuItemsFileName[28];
	char const c_acTankFileName[32];

	// Sprite IDs
	int iSpriteID[7];

	// Sprite Origin Points
	const Vector2 c_v2TopLeftOrigin;
	const Vector2 c_v2CenterOrigin;

	// Menu Item Variables
	// Background
	const Vector2 c_v2BackgroundDimensions;
	const Vector3 c_v3BackgroundPos;

	// Menu Button
	const float c_fButtonSize[3][2];
	const Vector4 c_v4ButtonUVCoords[3];
	const Vector3 c_v3ButtonPos[3];

	// Tank Arrow Variables		
	const Vector2 c_v2TankDimensions;
	const Vector2 c_v2TankPos[4];

	// General Variables
	bool bActive;
	bool bMenuDrawn;

	// Navigation Variables
	int iSelectedMenuItem;
	float fNavDelayTime;

	// Nav Keys
	short upKey, downKey, enterKey, spaceKey;

};


#endif // !_Menu_H_
