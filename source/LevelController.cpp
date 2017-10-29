//////////////////////////////////////////////////////////////////////////
// File: <LevelController.cpp>
// Author: <Alex Kitching>
// Date Created: <30/03/17>
// Brief: <Source file for the LevelController class.>
/////////////////////////////////////////////////////////////////////////

#include "LevelController.h"
#include "GameController.h"
#include "UGFW.h";
#include "MapCollision.h"
#include "BoxBoxCollision.h"
#include "Gjk.h"
#include <iostream>
#include <algorithm>

LevelController::LevelController() :
	// Initialise Variable List

	// Level Initialised Boolean
	bLevelInitialised(false),

	// Player Lives
	c_iMaxPlayerLives(5),
	iPlayerLives{5,5},

	// Sprite Image Definition
	// Sprite IDs
	iSpriteID(-1),
	// Sprite Origin Points
	c_fv2TopLeftOrigin(Vector2(0.f, 0.f)),
	// Level Background Images
	c_cLevelBackgroundFileNames("./images/levels/level1.png"),
	// Level Background Dimension
	c_fv2BackgroundDimensions(Vector2(1024.f, 768.f)),
	// Level Background Layer
	c_iBackgroundLayer(0)
{
}

LevelController::~LevelController()
{
}

LevelController & LevelController::GetLevelController()
{
	// TODO: insert return statement here
	static LevelController *levelController = NULL; // Creates Blank Level Controller Singleton
	if (levelController == NULL) // If Singleton is Blank
	{
		levelController = new LevelController(); // Assign new LevelController Object
		std::cout << "LevelController created." << std::endl; // Print to Console
	}
	return *levelController; // Return LevelController Singleton
}

void LevelController::DestroyLevelController()
{
	// Get Instance of Level Controller
	LevelController *levelController = &GetLevelController();
	if (levelController != NULL) // If LevelController singleton is present
	{
		delete levelController;  // Deletes LevelController
		std::cout << "LevelController destroyed." << std::endl; // Prints to Console
	}
}

void LevelController::InitialiseLevel() // Initialises Level
{
	// Create and Draw Background
	iSpriteID = UG::CreateSprite(c_cLevelBackgroundFileNames, c_fv2BackgroundDimensions, c_fv2TopLeftOrigin);
	UG::DrawSprite(iSpriteID);
	// Assign Layer
	UG::SetSpriteLayer(iSpriteID, c_iBackgroundLayer);
	// Initialise Level Assets
	InitialiseLevelAssets();
	// Level Now Initialised
	bLevelInitialised = true;
	// Assign Player Lives to Max
	iPlayerLives[0] = c_iMaxPlayerLives;
	iPlayerLives[1] = c_iMaxPlayerLives;
}

void LevelController::InitialiseLevelAssets()
{
	spawnController.SpawnLevelObjects(); // Spawns Level Objects
}

void LevelController::UpdateObjects(const float a_fDeltaTime)
{
	// Iterate through Dynamic (Moving) Objects
	for (std::list<Sprite*>::iterator currentSprite = vDynamicObjects.begin(); currentSprite != vDynamicObjects.end();)
	{
		// Get Current Object
		Sprite* pCurrentSprite = *currentSprite;

		if (pCurrentSprite != nullptr) // If Valid Pointer
		{

			if (pCurrentSprite->IsMapCollideable()) // If Sprite is Map Collidable
			{
				// Check Collisions with Current Object against Map Boundaries
				CheckMapCollisions(pCurrentSprite);
			}

			if (pCurrentSprite->IsActive()) // If Sprite Collided With Map, we recheck to see whether it is still active.
			{
				if (pCurrentSprite->IsCollideable()) // If Current Sprite is Collideable
				{
					// Check Collisions with Current Object against other Dynamic Objects
					for (std::list<Sprite*>::iterator otherSprite = vDynamicObjects.begin(); otherSprite != vDynamicObjects.end(); ++otherSprite)
					{
						//If Other Dynamic Object is not Current Object
						if (otherSprite != currentSprite)
						{
							// Get Other Object
							Sprite* pOtherSprite = *otherSprite;
							if (pOtherSprite != nullptr) // If Valid Pointer
							{
								if (pOtherSprite->IsCollideable()) // If other sprite is collideable
								{
									// Check Collision with Current Object and Other Object
									CheckCollisions(pCurrentSprite, pOtherSprite);
								}
							}
						}
					}

					// Check Collisions with Current Object against other static Objects
					for (std::list<Sprite*>::iterator otherSprite = vObjects.begin(); otherSprite != vObjects.end(); ++otherSprite)
					{
						// Get Other object
						Sprite* pOtherSprite = *otherSprite;
						if (pOtherSprite != nullptr) // If Valid Pointer
						{
							// Check Collision with Current Object and Other Object
							CheckCollisions(pCurrentSprite, pOtherSprite);
						}
					}
				}

				if (pCurrentSprite->IsActive()) // Recheck whether sprite is still active.
				{
					// Move Current Object
					pCurrentSprite->Update(a_fDeltaTime);
				}
			}

			// Remove Dead Objects
			if (!pCurrentSprite->IsActive())
			{
				int iPlayerID = -1;
				if (pCurrentSprite->GetPlayerID() != -1) // Sprite is a Player
				{
					iPlayerID = pCurrentSprite->GetPlayerID(); // Get Player ID
				}
				// Clear Pointer
				pCurrentSprite = nullptr;
				// Erase Sprite from Array
				currentSprite = vDynamicObjects.erase(currentSprite);

				if (iPlayerID != -1) // Last Sprite Erased was Player
				{
					DecreasePlayerLife(iPlayerID); // Decrease Players Life
					if (iPlayerLives[iPlayerID] > 0) // If Player still has at least 1 life
					{
						spawnController.RespawnTank(iPlayerID); // Respawn Player
					}
					else
					{
						// Game Over
						// Get Instance of Game Controller
						GameController *gameController = &gameController->GetGameController();
						if (iPlayerID == 0) // Player 1 Died
						{
							gameController->PauseGame(2); // Player 2 Wins
						}
						else if (iPlayerID == 1) // Player 2 Died
						{
							gameController->PauseGame(1); // Player 1 Wins
						}

					}
				}
			}
			else
			{
				currentSprite++; // Next Sprite
			}
		}

		 //Perform Powerup Spawn Check
	    if (spawnController.CanSpawnPowerup(a_fDeltaTime))
		{
			spawnController.SpawnPowerup(); // Spawn Powerup
		}

		// Draw UI
		uiController.DrawUI(iPlayerLives[0], iPlayerLives[1], iPlayerAmmo[0], iPlayerAmmo[1]);
	}
}

void LevelController::RegisterDynamicObject(Sprite * a_SpriteObject)
{
	vDynamicObjects.push_back(a_SpriteObject); // Add Dynamic Object to Array
}

void LevelController::RegisterStaticObject(Sprite * a_SpriteObject)
{
	vObjects.push_back(a_SpriteObject); // Add Object to Array
}

void LevelController::ResetPowerupSpawn(const int a_iSpawnID)
{
	spawnController.ResetPowerupSpawn(a_iSpawnID); // Reset PowerUps Spawn
}

bool LevelController::LevelInitialised() const
{
	return bLevelInitialised; // Returns whether the level has been initialised or not
}

Vector3 LevelController::GetPlayerPos(const int a_iPlayerID)
{
	// Loop Through Dynamic Object Array
	for (std::list<Sprite*>::iterator currentSprite = vDynamicObjects.begin(); currentSprite != vDynamicObjects.end(); currentSprite++)
	{
		// Get Current Object
		Sprite* pCurrentSprite = *currentSprite;
		if (pCurrentSprite != nullptr) // If Valid Pointer
		{
			if (pCurrentSprite->GetPlayerID() == a_iPlayerID) // If Player is Current Sprite - Player Found
			{
				return pCurrentSprite->GetPosition(); // Return Position
			}
		}
	}
	// Player Not Found
	return Vector3::Zero;
}

int LevelController::GetCurrentPlayerLifes(const int a_iPlayerID) const
{
	return iPlayerLives[a_iPlayerID]; // Returns Players Lives
}

void LevelController::UpdatePlayerAmmo(const int a_iPlayerID, const unsigned int a_iCurrentAmmo)
{
	iPlayerAmmo[a_iPlayerID] = a_iCurrentAmmo; // Updates Ammo Tracker
}

void LevelController::UpdatePlayerSpecial(const int a_iPlayerID, const bool a_bEquipped)
{
	if (a_bEquipped) // If Special is equipped.
	{
		uiController.DrawPlayerSpecial(a_iPlayerID);
	}
	else // Special is no longer equipped.
	{
		uiController.StopDrawingPlayerSpecial(a_iPlayerID);
	}
}

void LevelController::RequestPause() const
{
	// Get Instance of Game Controller
	GameController *gameController = &gameController->GetGameController();
	gameController->PauseGame(0); // Pause Game
}

void LevelController::ResetLevel()
{
	// Destroy Background Sprite
	UG::StopDrawingSprite(iSpriteID);
	UG::DestroySprite(iSpriteID);
	iSpriteID = -1;

	// Destroy Dynamic Objects
	for (std::list<Sprite*>::iterator currentSprite = vDynamicObjects.begin(); currentSprite != vDynamicObjects.end();)
	{
		// Get Current Object
		Sprite* pCurrentSprite = *currentSprite;
		if (pCurrentSprite != nullptr) // If Valid Pointer
		{
			pCurrentSprite->Destroy(); // Destroy Sprite
			pCurrentSprite = nullptr;
			// Erase Sprite from Array
			currentSprite = vDynamicObjects.erase(currentSprite);
		}
	}

	// Destroy Static Objects
	for (std::list<Sprite*>::iterator currentSprite = vObjects.begin(); currentSprite != vObjects.end();) 
	{
		// Get Current Object
		Sprite* pCurrentSprite = *currentSprite;
		if (pCurrentSprite != nullptr) // If Valid Pointer
		{
			pCurrentSprite->Destroy(); // Destroy Sprite
			pCurrentSprite = nullptr;
			// Erase Sprite from Array
			currentSprite = vObjects.erase(currentSprite);
		}
	}
	bLevelInitialised = false; // Level no longer initialised;
}

void LevelController::CheckMapCollisions(Sprite * a_CurrentSprite)
{
	CollisionAlgorithms::MapCollision MapCollisionCheck(Vector2((float)g_iScreenWidth, (float)g_iScreenHeight), a_CurrentSprite->GetDimensions(), a_CurrentSprite->GetPosition());

	if (MapCollisionCheck.IsColliding()) // Collision Check
	{ // We are Colliding
		a_CurrentSprite->CollideWithMap();
	}
}

void LevelController::CheckCollisions(Sprite * a_CurrentSprite, Sprite * a_OtherSprite)
{
	if (a_OtherSprite->GetType() != STATIC)
	{
		// Create Instance of Box Collision Check
		CollisionAlgorithms::BoxBoxCollision BoxCollisionCheck(a_CurrentSprite->GetPosition(), a_CurrentSprite->GetDimensions(), a_OtherSprite->GetPosition(), a_OtherSprite->GetDimensions());

		if (BoxCollisionCheck.IsColliding()) // Collision Check
		{	// We are Colliding

			// Initialise Sprite Vert Arrays
			Vector3 v3CurrentSpriteVerts[4]{ Vector3::Zero, Vector3::Zero, Vector3::Zero, Vector3::Zero };
			Vector3 v3OtherSpriteVerts[4]{ Vector3::Zero, Vector3::Zero, Vector3::Zero, Vector3::Zero };

			// Retrieve Verts from each sprite
			for (int i = 0; i < 4; i++)
			{
				v3CurrentSpriteVerts[i] = a_CurrentSprite->GetCurrentVerts()[i];
				v3OtherSpriteVerts[i] = a_OtherSprite->GetCurrentVerts()[i];
			}

			// Create Instance of GJK Collision Check
			CollisionAlgorithms::Gjk GjkCollisionCheck(v3CurrentSpriteVerts, 4, v3OtherSpriteVerts, 4);

			if (GjkCollisionCheck.IsColliding()) // Check for GJK Collision
			{	// We are Colliding
				a_CurrentSprite->CollideWith(a_OtherSprite); // React to Collision

				if (a_OtherSprite->GetType() != STATIC) // If Other Object is Dynamic
				{
					a_OtherSprite->CollideWith(a_CurrentSprite); // React to Collision
				}
			}
		}
	}
	else // Object is Static - Use just GJK due to Static Objects Rotations and Uneven Width/Heights
	{
		// Initialise Sprite Vert Arrays
		Vector3 v3CurrentSpriteVerts[4]{ Vector3::Zero, Vector3::Zero, Vector3::Zero, Vector3::Zero };
		Vector3 v3OtherSpriteVerts[4]{ Vector3::Zero, Vector3::Zero, Vector3::Zero, Vector3::Zero };

		// Retrieve Verts from each sprite
		for (int i = 0; i < 4; i++)
		{
			v3CurrentSpriteVerts[i] = a_CurrentSprite->GetCurrentVerts()[i];
			v3OtherSpriteVerts[i] = a_OtherSprite->GetCurrentVerts()[i];
		}

		// Create Instance of GJK Collision Check
		CollisionAlgorithms::Gjk GjkCollisionCheck(v3CurrentSpriteVerts, 4, v3OtherSpriteVerts, 4);

		if (GjkCollisionCheck.IsColliding()) // Check for GJK Collision
		{	// We are Colliding
			a_CurrentSprite->CollideWith(a_OtherSprite); // React to Collision

			if (a_OtherSprite->GetType() != STATIC) // If Other Object is Dynamic
			{
				a_OtherSprite->CollideWith(a_CurrentSprite); // React to Collision
			}
		}
	}
}

void LevelController::AddPlayerLife(const int a_iPlayerID)
{
	if (iPlayerLives[a_iPlayerID] < c_iMaxPlayerLives) // If Player has less than Maximum lives
	{
		++iPlayerLives[a_iPlayerID]; // Increment Player's Life
	}
}

void LevelController::DecreasePlayerLife(const int a_iPlayerID)
{
	if (iPlayerLives[a_iPlayerID] > 0) // If Player has at least 1 life
	{
		--iPlayerLives[a_iPlayerID]; // Decrease Player's life
	}
}
