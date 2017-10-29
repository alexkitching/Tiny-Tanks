//////////////////////////////////////////////////////////////////////////
// File: <LevelController.h>
// Author: <Alex Kitching>
// Date Created: <30/03/17>
// Brief: <Header file for all LevelController classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#include "Vector2.h"
#include "Sprite.h"
#include "SpawnController.h"
#include "UIController.h"
#include <list>

#ifndef _LevelController_H_
#define _LevelController_H_

// Retrieve Global Screen Dimensions
extern int g_iScreenWidth;
extern int g_iScreenHeight;

class Vector3;
class LevelController
{
public:
	// Singleton Functions
	static LevelController& GetLevelController();
	static void DestroyLevelController();


	// Functions
	void InitialiseLevel();
	void InitialiseLevelAssets();
	void UpdateObjects(const float a_fDeltaTime);
	void RegisterDynamicObject(Sprite* a_SpriteObject);
	void RegisterStaticObject(Sprite* a_SpriteObject);
	void ResetPowerupSpawn(const int a_iSpawnID);
	bool LevelInitialised() const;
	Vector3 GetPlayerPos(const int a_iPlayerID);
	int GetCurrentPlayerLifes(const int a_iPlayerID) const;
	void AddPlayerLife(const int a_iPlayerID);
	void UpdatePlayerAmmo(const int a_iPlayerID, const unsigned int a_iCurrentAmmo);
	void UpdatePlayerSpecial(const int a_iPlayerID, const bool a_bEquipped);
	void RequestPause() const;
	void ResetLevel();

private:
	// Constructors
	LevelController();  // Constructor
	~LevelController(); // Destructor

	// Functions
	void CheckMapCollisions(Sprite* a_CurrentSprite);
	void CheckCollisions(Sprite* a_CurrentSprite, Sprite* a_OtherSprite);
	void DecreasePlayerLife(const int a_iPlayerID);

	// Level Initialised Boolean - Game Manager Checks to prevent looping of Initialise Level
	bool bLevelInitialised;

	// Player Lives Tracking
	const unsigned int c_iMaxPlayerLives;
	unsigned int iPlayerLives[2];

	// Player Ammo Tracking
	unsigned int iPlayerAmmo[2];

	// Sprite Image Definition
	// Sprite ID's
	int iSpriteID;
	// Sprite Origin Points
	const Vector2 c_fv2TopLeftOrigin;
	// Level Background Images
	const char c_cLevelBackgroundFileNames[32];
	// Level Background Dimension
	const Vector2 c_fv2BackgroundDimensions;
	// Background Layer
	const unsigned int c_iBackgroundLayer;

	// Object Arrays
	std::list<Sprite*> vDynamicObjects;
	std::list<Sprite*> vObjects;

	// Spawn Controller
	SpawnController spawnController;

	// UI Controller
	UIController uiController;
};

#endif // !_Level_H_