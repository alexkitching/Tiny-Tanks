//////////////////////////////////////////////////////////////////////////
// File: <Tank.cpp>
// Author: <Alex Kitching>
// Date Created: <21/03/17>
// Brief: <Source file for the Tank class.>
/////////////////////////////////////////////////////////////////////////

#include "Tank.h";
#include "LevelController.h"
#include "UGFW.h";
#include "Util.h";
#include "Enumerations.h";
#define _USE_MATH_DEFINES
#include <math.h>

Tank::Tank(const unsigned int a_iPlayerID, const Vector2 a_v2SpawnPos, const float a_fSpawnRot) :
	// Initialise Variable List

	// Speed Variables
	fCurrentSpeed(0.f),
	c_fMaxSpeed(2.f),
	fAcceleration(0.f),
	c_fForwardSpeed(4.f),
	c_fReverseSpeed(1.6f),
	fCurrentDrag(0.f),
	c_fDrag(2.0f),

	// Shooting Variables
	c_iMaxNumBullets(6),
	iCurrentNumBullets(6),
	c_fReloadDelay(2.f),
	c_fFireDelay(0.25f),
	fLastReloaded(2.f),
	fLastFired(0.f),
	bNextHoming(false),

	// Rotation Variables
	c_fTurnRate(0.04f),
	c_fTurretTurnRate(0.04f),

	CurrentState(IDLE),

	// Control Keys
	moveUpKey(-1), moveDownKey(-1), leftTurnKey(-1), rightTurnKey(-1), leftTurnTurretKey(-1), rightTurnTurretKey(-1), fireKey(-1), quitKey(-1),

	// Sprite Image Definition
	// File Names
	c_acTankSheetFileName("./images/tanks/basesheet.png"),

	// UV Coordinates  // Player 1
	v4TankUVCoords{ { { SetSpriteUVCoords(0.f, 0.f, 62.f, 52.f, 126.f, 105.f) }, 
					  { SetSpriteUVCoords(63.f, 0.f, 125.f, 52.f, 126.f, 105.f) } },
					   // Player 2
					{ { SetSpriteUVCoords(0.f, 54.f, 62.f, 106.f, 126.f, 105.f) },
					  { SetSpriteUVCoords(63.f, 54.f, 125.f, 106.f, 126.f, 105.f) } } }
{
	// Setup Sprite Variables
	iPlayerID = a_iPlayerID;
	Type = PLAYER;
	v2Dimensions = Vector2(64.f, 53.f);
	Initialise(a_v2SpawnPos, a_fSpawnRot);
}

Tank::~Tank()
{
}

void Tank::Initialise(const Vector2 a_v2SpawnPos, const float a_fSpawnRot)
{
	// Initialise Sprite
	InitialiseSprite(c_acTankSheetFileName, v2Dimensions, v2Origin, v4TankUVCoords[iPlayerID][0]);

	// Initialise Animation Controller
	animationController.Initialise(iSpriteID, v4TankUVCoords[iPlayerID], 2);

	// Set Starting Position
	SetPosition(a_v2SpawnPos);

	// Assign Movement Keys and Rotation
	if (iPlayerID == 0) // We are Player 1
	{
		RotateZ(DegreestoRadians(a_fSpawnRot)); // Rotate to Start Rotation
		SetMovementKeys(UG::KEY_W, UG::KEY_S, UG::KEY_A, UG::KEY_D, UG::KEY_Q, UG::KEY_E, UG::KEY_SPACE, UG::KEY_ESCAPE);
	}
	else if (iPlayerID == 1) // We are Player 2
	{
		RotateZ(DegreestoRadians(a_fSpawnRot)); // Rotate to Start Rotation
		SetMovementKeys(UG::KEY_KP_8, UG::KEY_KP_5, UG::KEY_KP_4, UG::KEY_KP_6, UG::KEY_KP_7, UG::KEY_KP_9, UG::KEY_KP_0, UG::KEY_ESCAPE);
	}
	// Draw Sprites
	DrawSprite();
	SetLayer(1);

	// Set Tank to Active 
	bActive = true;

	// Initialise Turret
	turret.Initialise(iPlayerID, this);

	// Update Ammo Tracker
	UpdateAmmoTracker();
}

void Tank::Update(const float a_fDeltaTime)
{
	CleanupDestroyedBullets(); // Removes Destroyed Bullets

	fAcceleration = 0.f; //Reset Acceleration to 0

	switch (CurrentState)
	{
	case IDLE:
		// Movement
		if (UG::IsKeyDown(moveUpKey))
		{
			CurrentState = MOVING; // We are Moving
		}
		if (UG::IsKeyDown(moveDownKey))
		{
			CurrentState = MOVING; // We are Moving
		}

		break;

	case MOVING:
		// Start Moving Animation
		animationController.UpdateAnimation(a_fDeltaTime);

		if (UG::IsKeyDown(moveUpKey))
		{
			// Accelerate
			fAcceleration += c_fForwardSpeed;
			fCurrentDrag = 0.f;
		}
		else if (UG::IsKeyDown(moveDownKey))
		{
			// Reverse
			fAcceleration -= c_fReverseSpeed;
			fCurrentDrag = 0.f;
		}
		else  // When Tank not accelerating or reversing
		{
			fCurrentDrag = c_fDrag; // Apply Drag
		}

		fCurrentSpeed += fAcceleration * a_fDeltaTime; // Apply Acceleration
		fCurrentSpeed -= (fCurrentSpeed * fCurrentDrag) * a_fDeltaTime; // Apply Drag

		if (fabsf(fCurrentSpeed) > c_fMaxSpeed) // If Current Speed is Greater than Max Speed
		{
			if (fCurrentSpeed < 0.f) // Current Speed is Negative
			{
				fCurrentSpeed = -c_fMaxSpeed; 
			}
			else // Current Speed is Positive
			{
				fCurrentSpeed = c_fMaxSpeed;
			}
		}

		if (fabsf(fCurrentSpeed) > FLT_EPSILON) // If we are moving
		{
			v3Velocity = Vector3::Up; // Set Velocity to Upwards/Forwards Vector
			v3Velocity *= fCurrentSpeed; // Multiply Velocity Vector by Current Speed
			MoveSprite(); // Move Tank
		}
		else // Not Moving
		{
			CurrentState = IDLE;
		}
		break;
	}

	// Check Rotation Input and Update
	UpdateRotation();

	ReduceFireDelay(a_fDeltaTime); // Reduce Fire Delay
	ReduceReloadDelay(a_fDeltaTime); // Reduce Reload Delay

	if (CanReload()) // If we can Reload
	{
		Reload(); // Reload
	}

	if (UG::IsKeyDown(fireKey) && CanShoot()) // Fire Key Pressed and Can Shoot
	{
		Shoot(); // Shoot
	}

	if (UG::IsKeyDown(quitKey))
	{
		// Get Level Controller Singleton
		LevelController* levelController = &LevelController::GetLevelController();
		levelController->RequestPause(); // Pause Game
	}

	// Update Tank and Turret
	UpdateSprite(a_fDeltaTime);
	turret.Update(a_fDeltaTime);
}

void Tank::CollideWith(Sprite * a_Sprite)
{
	// Get Level Controller Singleton
	LevelController* levelController = &LevelController::GetLevelController();
	switch (a_Sprite->GetType())
	{
	case PLAYER:
		fCurrentSpeed = -fCurrentSpeed * 0.5; // Invert Current Speed and half it (Tank will now be moving opposite direction
		v3Velocity = -v3Velocity; // Invert Current Velocity
		MoveSprite(); // Move Tank
		break;
	case LIFEPOWERUP:
		levelController->AddPlayerLife(iPlayerID);
		break;
	case AMMOPOWERUP:
		if (iCurrentNumBullets < c_iMaxNumBullets) // If we have less bullets than the maximum
		{
			Reload(); // Reload
		}
		break;
	case HOMINGPOWERUP:
		bNextHoming = true; // Next Bullet is Homing Bullet
		levelController->UpdatePlayerSpecial(iPlayerID, bNextHoming); // Update Level Controller's UI Controller to Draw UI
		break;
	case MYSTERYPOWERUP:
		RollMysteryPowerup(levelController); // Rolls Mystery Powerup
		break;
	case STATIC:
		fCurrentSpeed = -fCurrentSpeed * 0.5; // Invert Current Speed and half it (Tank will now be moving opposite direction
		v3Velocity = -v3Velocity; // Invert Current Velocity
		MoveSprite(); // Move Tank
		break;
	}
}

void Tank::CollideWithMap()
{
	fCurrentSpeed = -fCurrentSpeed * 0.5; // Invert Current Speed and half it (Tank will now be moving opposite direction
	v3Velocity = -v3Velocity; // Invert Current Velocity
	MoveSprite(); // Move Tank
}

void Tank::SetState(const State a_state)
{
	CurrentState = a_state;
}

void Tank::UpdateRotation()
{
	// Tank Rotation
	if (UG::IsKeyDown(leftTurnKey))
	{
		// Turn Tank Left
		RotateZ(c_fTurnRate);
	}
	if (UG::IsKeyDown(rightTurnKey))
	{
		// Turn Tank Right
		RotateZ(-c_fTurnRate);
	}
	if (UG::IsKeyDown(leftTurnTurretKey))
	{
		// Turn Turret Left
		turret.RotateZ(c_fTurretTurnRate);
	}
	if (UG::IsKeyDown(rightTurnTurretKey))
	{
		// Turn Turret Right
		turret.RotateZ(-c_fTurretTurnRate);
	}
}

bool Tank::CanShoot()
{
	if (fLastFired <= 0.f) // Has Delay Time Passed
	{	// Delay has passed
		if (iCurrentNumBullets > 0) // If we have not used up all bullets
		{
			// Reset Last Fired to DelayTime
			fLastFired = c_fFireDelay;
			return true; // We Can shoot
		}
	}
	// We can't shoot
	return false;
}

void Tank::Shoot()
{
	// Get Level Controller Singleton
	LevelController* levelController = &LevelController::GetLevelController();
	if (bNextHoming) // if Next Bullet is Homing Bullet
	{
		// Create Bullet 
		BulletArray.emplace_back(new HomingBullet(turret.GetBulletPosRot(), iPlayerID));
		bNextHoming = false; // No longer have Homing Bullet
		levelController->UpdatePlayerSpecial(iPlayerID, bNextHoming); // Update Level Controller's UI Controller to Draw UI
	}
	else // Fire Normal Bullet
	{
		// Create Bullet
		BulletArray.emplace_back(new BasicBullet(turret.GetBulletPosRot(), iPlayerID));
	}

	// Register Bullet on LevelController
	levelController->RegisterDynamicObject(BulletArray.back());

	// Decrease Current Number of Bullets
	--iCurrentNumBullets;

	// Update Ammo Tracker
	UpdateAmmoTracker();
}

bool Tank::CanReload()
{
	if (fLastReloaded <= 0.f)
	{
		if (iCurrentNumBullets < c_iMaxNumBullets) // We have less than maximum bullets
		{
			// Reset Last Reloaded Time to Reload Delay
			fLastReloaded = c_fReloadDelay;
			return true; // Can Reload
		}
	}
	return false;
}

void Tank::Reload()
{
	// Increase Current Number of Bullets
	++iCurrentNumBullets;
	// Update Ammo Tracker
	UpdateAmmoTracker();
}

void Tank::ReduceFireDelay(const float a_fDeltaTime)
{
	if (fLastFired > 0.f) // If delay has not yet passed
	{
		fLastFired -= a_fDeltaTime; // Reduce Last Fired time by DeltaTime;
	}
}

void Tank::ReduceReloadDelay(const float a_fDeltaTime)
{
	if (fLastReloaded > 0.f) // IF delay has not passed
	{
		fLastReloaded -= a_fDeltaTime; // Reduce Last Reloaded time by DeltaTime;
	}
}

void Tank::CleanupActiveBullets()
{
	if (!BulletArray.empty()) // Bullets still in array
	{
		// Iterate Through bullets
		for (std::list<TankBullet*>::iterator bullet = BulletArray.begin(); bullet != BulletArray.end(); ++ bullet)
		{
			// Get Current Bullet
			TankBullet* pBullet = *bullet;

			// Destroy Bullet
			pBullet->Destroy();
		}
	}
}

void Tank::CleanupDestroyedBullets()
{
	if (!BulletArray.empty()) // Bullets still in array
	{
		// Iterate through bullets
		for (std::list<TankBullet*>::iterator bullet = BulletArray.begin(); bullet != BulletArray.end();)
		{
			// Get Current Bullet
			TankBullet* pBullet = *bullet;
			if (!pBullet->IsActive())
			{
				pBullet = nullptr;
				bullet = BulletArray.erase(bullet);
			}
			else
			{
				++bullet;
			}
		}
	}
}

void Tank::UpdateAmmoTracker() const
{
	// Get Level Controller Singleton
	LevelController* levelController = &LevelController::GetLevelController();
	levelController->UpdatePlayerAmmo(iPlayerID, iCurrentNumBullets);
}

void Tank::RollMysteryPowerup(LevelController* a_levelController)
{
	int iRandomPowerup = rand() % 2;
	switch (iRandomPowerup)
	{
	case 0: // Life Powerup
		a_levelController->AddPlayerLife(iPlayerID);
		break;
	case 1: // Ammo Powerup
		if (iCurrentNumBullets < c_iMaxNumBullets) // If we have less bullets than the maximum
		{
			Reload(); // Reload
		}
		break;
	case 2: // Homing Powerup
		bNextHoming = true; // Next Bullet is Homing Bullet
		break;
	}
}

void Tank::Destroy()
{
	turret.Destroy();
	CleanupActiveBullets();
	DestroySprite();
}

void Tank::SetMovementKeys(short a_moveUpKey, short a_moveDownKey, short a_leftTurnKey, short a_rightTurnKey, short a_leftTurnTurretKey, short a_rightTurnTurretKey, short a_fireKey, short a_quitKey)
{
	moveUpKey = a_moveUpKey;
	moveDownKey = a_moveDownKey;
	leftTurnKey = a_leftTurnKey;
	rightTurnKey = a_rightTurnKey;
	leftTurnTurretKey = a_leftTurnTurretKey;
	rightTurnTurretKey = a_rightTurnTurretKey;
	fireKey = a_fireKey;
	quitKey = a_quitKey;
}