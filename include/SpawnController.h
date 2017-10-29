//////////////////////////////////////////////////////////////////////////
// File: <SpawnController.h>
// Author: <Alex Kitching>
// Date Created: <24/05/17>
// Brief: <Header file for all SpawnController classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _SpawnController_H_
#define _SpawnController_H_
#include "Vector3.h"
#include "Vector2.h"

extern int g_iScreenWidth;
extern int g_iScreenHeight;

class SpawnController
{
public:
	// Constructors
	SpawnController();
	~SpawnController() {};

	// Functions
	void SpawnLevelObjects();
	void RespawnTank(const int a_iPlayerID);
	bool CanSpawnPowerup(const float a_fDeltaTime);
	void SpawnPowerup();
	void ResetPowerupSpawn(const int a_iSpawnID);

private:
	// Functions
	int FindFurthestSpawn(Vector2 a_v3EnemyPos) const;
	
	// Level 1 Object Parameters
	// Tank Respawn Points
	const Vector3 c_v3TankRespawnPoints[4]; // XY - Position, Z = Rotation
	// Tank Starting Points
	const int c_iPlayer1Start;
	const int c_iPlayer2Start;

	// Powerup Spawn Parameters
	// Powerup Spawn Points
	int c_iMaxSpawnpoints;
	Vector3 v3PowerUpSpawnPoints[5]; // XY - Position, Z = Spawnpoint Free
	// Powerup Spawn Delay
	const float c_fMaxSpawnDelay;
	float fCurrentSpawnDelay;
	const int c_iMaxPowerupsSpawned;
	int iCurrentPowerupsSpawned;
	// Spawn Roll Thresholds
	const int c_iPowerupThreshhold[4];

	// Obstacle Positions and Rotations
	const Vector3 c_v3PencilPosRot[2]; // XY - Position, Z = Rotation
	const Vector3 c_v3EraserPosRot[3]; // XY - Position, Z = Rotation
};

#endif // !_SpawnController_H_
