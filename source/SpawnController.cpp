//////////////////////////////////////////////////////////////////////////
// File: <SpawnController.cpp>
// Author: <Alex Kitching>
// Date Created: <24/05/17>
// Brief: <Source file for the Spawn Controller class.>
/////////////////////////////////////////////////////////////////////////

#include "SpawnController.h"
#include "LevelController.h"
#include "Obstacles.h"
#include "Powerups.h"
#include "Tank.h"
#include "UGFW.h"
#include "Util.h"

SpawnController::SpawnController() :
	// Level 1 Object Parameters
	// Tank Respawn Points
	c_v3TankRespawnPoints{ { Vector3(g_iScreenWidth * 0.5, g_iScreenHeight * 0.8, 180.f) },
						   { Vector3(g_iScreenWidth * 0.8, g_iScreenHeight * 0.5, 90.f) },
						   { Vector3(g_iScreenWidth * 0.5, g_iScreenHeight * 0.2, 0.f)   },
						   { Vector3(g_iScreenWidth * 0.2, g_iScreenHeight * 0.5, 270.f)  } },
	// Tank Starting Points
	c_iPlayer1Start(0),
	c_iPlayer2Start(2),

	// Powerup Spawn Points
	c_iMaxSpawnpoints(5),
	v3PowerUpSpawnPoints{ { Vector3(g_iScreenWidth * 0.1, g_iScreenHeight * 0.3, 0.f) },
						  { Vector3(g_iScreenWidth * 0.9, g_iScreenHeight * 0.3, 0.f) },
						  { Vector3(g_iScreenWidth * 0.3, g_iScreenHeight * 0.9, 0.f) },
						  { Vector3(g_iScreenWidth * 0.75, g_iScreenHeight * 0.8, 0.f) },
						  { Vector3(g_iScreenWidth * 0.5, g_iScreenHeight * 0.5, 0.f) } },
	// Spawn Delay
	c_fMaxSpawnDelay(10.f),
	fCurrentSpawnDelay(10.f),
	c_iMaxPowerupsSpawned(3),
	iCurrentPowerupsSpawned(0),

	// Spawn Roll Thresholds
	c_iPowerupThreshhold{ 0, 40, 70, 90 }, // 0 - Ammo, 40 - Homing , 70 - Mystery, 90 - Life

	// Obstacle Positions and Rotations
	c_v3PencilPosRot { { Vector3(g_iScreenWidth * 0.3, g_iScreenHeight * 0.55, 330.f) },
				     { Vector3(g_iScreenWidth * 0.7, g_iScreenHeight * 0.55, 30.f) } },

	c_v3EraserPosRot { { Vector3(g_iScreenWidth * 0.5, g_iScreenHeight * 0.3, 90.f) },
					 { Vector3(g_iScreenWidth * 0.15, g_iScreenHeight * 0.15, 70.f) }, 
					 { Vector3(g_iScreenWidth * 0.85, g_iScreenHeight * 0.85, 330.f) } }
{
}

void SpawnController::SpawnLevelObjects()
{
	// Get Level Controller Singleton
	LevelController* levelController = &LevelController::GetLevelController();

	// Create and Register Players to LevelController
	levelController->RegisterDynamicObject(new Tank(0, Vector2(c_v3TankRespawnPoints[c_iPlayer1Start]), c_v3TankRespawnPoints[c_iPlayer1Start].GetZ()));
	levelController->RegisterDynamicObject(new Tank(1, Vector2(c_v3TankRespawnPoints[c_iPlayer2Start]), c_v3TankRespawnPoints[c_iPlayer2Start].GetZ()));

	// Create and Register Obstacles to LevelController
	for (int i = 0; i < 2; i++)
	{
		levelController->RegisterStaticObject(new Obstacle::Pencil(Vector2(c_v3PencilPosRot[i]), c_v3PencilPosRot[i].GetZ())); 
	}
	for (int i = 0; i < 3; i++)
	{
		levelController->RegisterStaticObject(new Obstacle::Eraser(Vector2(c_v3EraserPosRot[i]), c_v3EraserPosRot[i].GetZ()));
	}
}



void SpawnController::RespawnTank(const int a_iPlayerID)
{
	// Get Level Controller Singleton
	LevelController* levelController = &LevelController::GetLevelController();
	Vector2 v2EnemyPos = Vector2::Zero;
	int iFurthestSpawnPoint = -1;

	if (a_iPlayerID == 0) // Player 1
	{
		// Get Player 2's Position
		v2EnemyPos = Vector2(levelController->GetPlayerPos(1));
	}
	else if(a_iPlayerID == 1) // Player 2
	{
		// Get Player 1's Position
		v2EnemyPos = Vector2(levelController->GetPlayerPos(0)); 
	}
	// Find Furthest Spawn Point away from Enemy
	iFurthestSpawnPoint = FindFurthestSpawn(v2EnemyPos);

	// Respawn Tank
	levelController->RegisterDynamicObject(new Tank(a_iPlayerID, Vector2(c_v3TankRespawnPoints[iFurthestSpawnPoint]), c_v3TankRespawnPoints[iFurthestSpawnPoint].GetZ()));
}

bool SpawnController::CanSpawnPowerup(const float a_fDeltaTime)
{
	if (iCurrentPowerupsSpawned < c_iMaxPowerupsSpawned) // If the number of currently spawned powerups is less than the max
	{
		fCurrentSpawnDelay -= a_fDeltaTime; // Decrease Current Spawn Delay
		if (fCurrentSpawnDelay <= 0.f) // Spawn Time Elapsed
		{
			fCurrentSpawnDelay = c_fMaxSpawnDelay; // Reset Delay
			return true; // Can Spawn Powerup
		}
	}
	return false; // Can't Spawn Powerup
}

int SpawnController::FindFurthestSpawn(Vector2 a_v2EnemyPos) const
{
	// Find Furthest Spawn Point from Enemy
	Vector2 v2FurthestSpawn = Vector2::Zero;
	int iFurthestSpawnIndex = -1;
	float fFurthestDistance = 0.f;
	for (int i = 0; i < 4; i++) // Iterate through Spawn Points
	{
		Vector2 v2SpawnPos = Vector2(c_v3TankRespawnPoints[i]); // Get Spawn Position
		float fDistance = a_v2EnemyPos.Distance(v2SpawnPos); // Get Distance
		if (fDistance > fFurthestDistance) // New Distance is greater than current furthest distance
		{
			fFurthestDistance = fDistance; // New Distance is now furthest distance
			iFurthestSpawnIndex = i; // Furthest Spawn is now the current spawn point
		}
	}
	return iFurthestSpawnIndex;
}

void SpawnController::SpawnPowerup()
{
	// Generate Spawn Point
	int iNumPossibleSpawnPoints = c_iMaxSpawnpoints - iCurrentPowerupsSpawned; // Get Number of Possible Spawn Points
	int iSpawnIndex = -1; // Index for Selected Spawn Point

	if (iNumPossibleSpawnPoints != c_iMaxSpawnpoints) // If all spawns are not available
	{
		bool bSpawnPicked = false;
		while (!bSpawnPicked) // While We haven't found a spawn, loop
		{
			int iSpawnRoll = rand() % (c_iMaxSpawnpoints); // Pick a random number between 0 and Number of Spawns (5)
			if (v3PowerUpSpawnPoints[iSpawnRoll].GetZ() == 0)
			{
				iSpawnIndex = iSpawnRoll; // Set Spawn Index to Spawn Roll
				v3PowerUpSpawnPoints[iSpawnIndex].SetZ(1.f); // Set Spawn to Occupied
				bSpawnPicked = true; // Spawn Found, exit loop
			}
		}
	}
	else // All Spawns are Available (Pick from Any)
	{
		int iSpawnRoll = rand() % (c_iMaxSpawnpoints - 1); // Pick a random number between 0 and Number of Spawns (5)
		iSpawnIndex = iSpawnRoll; // Set Spawn Index to Spawn Roll
		v3PowerUpSpawnPoints[iSpawnIndex].SetZ(1.f); // Set Spawn to Occupied
	}

	// Get Level Controller Singleton
	LevelController* levelController = &LevelController::GetLevelController();

	// Randomly Pick Powerup
	int iCurrentRoll = (rand() % 100) + 1; // Peform Dice Roll from 1-100

	if (iCurrentRoll > c_iPowerupThreshhold[3]) // If Current Roll is Greater Than Life's Threshhold (90)
	{
		// Spawn Life Powerup
		levelController->RegisterDynamicObject(new Powerup::Life(v3PowerUpSpawnPoints[iSpawnIndex], iSpawnIndex));
		iCurrentPowerupsSpawned++; // Increment Number of Powerups Spawned
	}
	else if (iCurrentRoll > c_iPowerupThreshhold[2]) // If Current Roll is Greater than Mystery's Threshold (70)
	{
		// Spawn Mystery Powerup
		levelController->RegisterDynamicObject(new Powerup::Mystery(v3PowerUpSpawnPoints[iSpawnIndex], iSpawnIndex));
		iCurrentPowerupsSpawned++; // Increment Number of Powerups Spawned
	}
	else if (iCurrentRoll > c_iPowerupThreshhold[1])  // If Current Roll is Greater than Homing's Threshold (40)
	{
		// Spawn Homing Powerup
		levelController->RegisterDynamicObject(new Powerup::Homing(v3PowerUpSpawnPoints[iSpawnIndex], iSpawnIndex));
		iCurrentPowerupsSpawned++; // Increment Number of Powerups Spawned
	}
	else if (iCurrentRoll > c_iPowerupThreshhold[0]) // If Current Roll is Greater than Ammo's Threshold (0)
	{
		// Spawn Ammo Powerup
		levelController->RegisterDynamicObject(new Powerup::Ammo(v3PowerUpSpawnPoints[iSpawnIndex], iSpawnIndex));
		iCurrentPowerupsSpawned++; // Increment Number of Powerups Spawned
	}
}

void SpawnController::ResetPowerupSpawn(const int a_iSpawnID)
{
	v3PowerUpSpawnPoints[a_iSpawnID].SetZ(0.f); // Free up Spawn Value
	--iCurrentPowerupsSpawned; // Decrease Current Number of Powerups Spawned
}
