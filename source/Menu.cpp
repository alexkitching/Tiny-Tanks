//////////////////////////////////////////////////////////////////////////
// File: <Menu.cpp>
// Author: <Alex Kitching>
// Date Created: <12/03/17>
// Brief: <Source file for the Menu class.>
/////////////////////////////////////////////////////////////////////////

#pragma region Includes

#include "Menu.h";
#include "UGFW.h";
#include "GameController.h"
#include "Util.h";

#pragma endregion

Menu::Menu() :
	// Initialise Variable List
	// Sprite Image Definition
	// File Names
	c_acBackgroundFileName("./images/menu/background.png"),
	c_acMenuItemsFileName("./images/menu/menuitems.png"),
	c_acTankFileName("./images/menu/TankArrow.png"),

	// Sprite IDs
	iSpriteID{ -1,  // Background 0 
	           -1,  // Title 1
		       -1,  // Play 2
			   -1,  // Quit 3
			   -1}, // Tank 4

	// Sprite Origin Points
	c_v2TopLeftOrigin(Vector2(0.f, 0.f)),
	c_v2CenterOrigin(Vector2(0.5f, 0.5f)),

	// Menu Item Variables
	// Background
	c_v2BackgroundDimensions(Vector2(1024.f, 768.f)),
	c_v3BackgroundPos(Vector3(g_iScreenWidth * 0.5f, g_iScreenHeight * 0.5f, 0.f)),

	// Menu Button
	c_fButtonSize{{ 624.f, 139.f }, // Title 1
				  { 154.f, 88.f },  // Play 2
				  { 149.f, 89.f } },// Quit 3
	c_v4ButtonUVCoords{ SetSpriteUVCoords(149, 0, 773, 140, 803, 228),   // Title 1
					    SetSpriteUVCoords(649, 139, 803, 228, 803, 228), // Play 2
					    SetSpriteUVCoords(0, 58, 149, 147, 803, 228) },  // Quit 3
	c_v3ButtonPos{ Vector3(CenterSpriteHorizontal(c_fButtonSize[0][0], g_iScreenWidth), g_iScreenHeight * 0.75, 0.f),   // Title 1
				   Vector3(CenterSpriteHorizontal(c_fButtonSize[1][0], g_iScreenWidth), g_iScreenHeight * 0.5, 0.f),   // Play 2
				   Vector3(CenterSpriteHorizontal(c_fButtonSize[2][0], g_iScreenWidth), g_iScreenHeight * 0.3, 0.f) }, // Quit 5

	// Tank Arrow Position Variables
	c_v2TankDimensions(Vector2(62.f,69.f)),
	c_v2TankPos{ Vector2(380.f, (float)g_iScreenHeight * 0.575f),
				 Vector2(390.f, (float)g_iScreenHeight * 0.370f) },

	// General Variables
	bMenuDrawn(false),

	// Navigation Variables
	iSelectedMenuItem(1),
	fNavDelayTime(0.0f),

	// Nav Keys
	upKey(-1), downKey(-1), enterKey(-1), spaceKey(-1)
{
}

void Menu::Initialise()
{
	// Create and Draw Background
	iSpriteID[0] = UG::CreateSprite(c_acBackgroundFileName, c_v2BackgroundDimensions, c_v2CenterOrigin);
	UG::DrawSprite(iSpriteID[0]);
	UG::MoveSprite(iSpriteID[0], c_v3BackgroundPos);

	// Create and Draw Menu Items
	for (int i = 1; i < 4; i++)
	{
		iSpriteID[i] = UG::CreateSprite(c_acMenuItemsFileName, c_fButtonSize[i-1], c_v2TopLeftOrigin, c_v4ButtonUVCoords[i-1]);
		UG::DrawSprite(iSpriteID[i]);
		UG::MoveSprite(iSpriteID[i], c_v3ButtonPos[i-1]);
	}

	// Create and Draw Tank
	iSpriteID[4] = UG::CreateSprite(c_acTankFileName, c_v2TankDimensions, c_v2CenterOrigin);
	UG::DrawSprite(iSpriteID[4]);
	UG::MoveSprite(iSpriteID[4], c_v2TankPos[0]);

	// Set Navigation Keys
	SetNavigationKeys(UG::KEY_UP, UG::KEY_DOWN, UG::KEY_ENTER, UG::KEY_SPACE);

	bMenuDrawn = true;
}

void Menu::Update(float a_fDeltaTime)
{
	if (!bMenuDrawn) // If Menu is not Drawn
	{
		Initialise(); // Draw Menu
	}

	if (UG::IsKeyDown(enterKey) || UG::IsKeyDown(spaceKey))
	{
		// Get Instance of Game Controller
		GameController *gameController = &gameController->GetGameController();

		switch (iSelectedMenuItem) 
		{
		case 1: // Play Button Selected
			gameController->ChangeState(GAMEPLAY);
			Destroy(); // Destroy Menu Sprites
			iSelectedMenuItem == 1; // Reset Menu Item
			break;
		case 2: // Quit Button Selected
			gameController->ChangeState(GAMEOVER);
			Destroy(); // Destroy Menu Sprites
			iSelectedMenuItem == 1; // Reset Menu Item
			break;
		}
	}
	else if (UG::IsKeyDown(upKey) && fNavDelayTime <= 0.f) // Up key Pressed
	{
		if (iSelectedMenuItem == 1)  // Selected item is Play
		{
			iSelectedMenuItem = 2; // Selected Item now Quit
		}
		else
		{
			--iSelectedMenuItem; // Selected Item now Play
		}
		// Move Tank Arrow
		UG::MoveSprite(iSpriteID[4], c_v2TankPos[iSelectedMenuItem-1]);
		// Set Nav Delay Time
		fNavDelayTime = 0.2f;
	}
	else if (UG::IsKeyDown(downKey) && fNavDelayTime <= 0.f) // Down Key Pressed
	{
		if (iSelectedMenuItem == 2) // Selected Item is Quit
		{
			iSelectedMenuItem = 1; // Selected Item Now play
		}
		else
		{
		++iSelectedMenuItem; // Selected Item now Quit
		}
		// Move Tank Arrow
		UG::MoveSprite(iSpriteID[4], c_v2TankPos[iSelectedMenuItem-1]);
		// Set Nav Delay Time
		fNavDelayTime = 0.2f;
	}
	if (fNavDelayTime > 0.f) // if Nav Timer not elapsed
	{
		fNavDelayTime -= a_fDeltaTime; // Reduce Timer
	}
}


void Menu::SetNavigationKeys(short a_upKey, short a_downKey, short a_enterKey, short a_spaceKey)
{
	// Sets up Navigation Keys
	upKey = a_upKey;
	downKey = a_downKey;
	enterKey = a_enterKey;
	spaceKey = a_spaceKey;
}

void Menu::Destroy()
{
	// Stop Drawing Destroy and Reset Sprites
	for (int i = 0; i < 5; i++)
	{
		UG::StopDrawingSprite(iSpriteID[i]);
		UG::DestroySprite(iSpriteID[i]);
		iSpriteID[i] = -1;
	}
	bMenuDrawn = false; // Menu is no longer drawn
}
