//////////////////////////////////////////////////////////////////////////
// File: <Tank.h>
// Author: <Alex Kitching>
// Date Created: <21/03/17>
// Brief: <Header file for all Tank classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _Tank_H_
#define _Tank_H_

#include "Sprite.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "TankTurret.h"
#include "TankStates.h"
#include "TankBullet.h"
#include "AnimationController.h"
#include <list>

class LevelController;
class GameController;
class Tank : public Sprite
{
public:
	Tank(const unsigned int a_iPlayerID, const Vector2 a_v2SpawnPos, const float a_fSpawnRot); // Constructor
	~Tank(); // Destructor

	// Functions
	void Update(const float a_fDeltaTime) override;
	void CollideWith(Sprite* a_Sprite) override;
	void CollideWithMap() override;
	void SetState(const State a_state);
	void Destroy() override;
private:

#pragma region Functions
	//Functions
	void Initialise(const Vector2 a_v2SpawnPos, const float a_fSpawnRot);
	void UpdateRotation();

	// Shoot Functions
	bool CanShoot();
	void Shoot();
	bool CanReload();
	void Reload();
	void ReduceFireDelay(const float a_fDeltaTime);
	void ReduceReloadDelay(const float a_fDeltaTime);
	void CleanupActiveBullets();
	void CleanupDestroyedBullets();
	void UpdateAmmoTracker() const;
	void RollMysteryPowerup(LevelController* a_levelController);

	void SetMovementKeys(short a_moveUpKey, short a_moveDownKey, short a_leftTurnKey, short a_rightTurnKey, short a_leftTurnTurretKey, short a_rightTurnTurretKey, short a_fireKey, short a_quitKey);

#pragma endregion

#pragma region Variables
	// Speed Variables
	float fCurrentSpeed;
	float const c_fMaxSpeed;
	float fAcceleration;
	float const c_fForwardSpeed;
	float const c_fReverseSpeed;
	float fCurrentDrag;
	float const c_fDrag;

	// Shooting Variables
	unsigned int const c_iMaxNumBullets;
	int iCurrentNumBullets;
	const float c_fReloadDelay;
	const float c_fFireDelay;
	float fLastReloaded;
	float fLastFired;
	bool bNextHoming;
	std::list<TankBullet*> BulletArray;

	// Rotation Variables
	float const c_fTurnRate;
	float const c_fTurretTurnRate;

	// Tank Turret Object
	TankTurret turret;

	// State Variable
	State CurrentState;

	// Control Keys
	short moveUpKey, moveDownKey, leftTurnKey, rightTurnKey, leftTurnTurretKey, rightTurnTurretKey, fireKey, quitKey;

	// Sprite Image Definition
	// File Names
	char const c_acTankSheetFileName[29];

	// UV Coordinates
	Vector4 v4TankUVCoords[2][2];

	// Sprite Animation Controller
	AnimationController animationController;

#pragma endregion
};
#endif // !_Tank_H_