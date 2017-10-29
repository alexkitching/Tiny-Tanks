//////////////////////////////////////////////////////////////////////////
// File: <TankBullet.cpp>
// Author: <Alex Kitching>
// Date Created: <19/05/17>
// Brief: <Source file for Tank Bullet classes.>
/////////////////////////////////////////////////////////////////////////

#include "TankBullet.h"
#include "Matrix3.h"
#include "LevelController.h"
#include "Explosion.h"
#include "Util.h"
#define _USE_MATH_DEFINES
#include <math.h>

//  Default Constructor
TankBullet::TankBullet() :
	// Initialise Variable List
	fSpeed(0.f)
{
	Type = BULLET;
}

// Custom Constructor
TankBullet::TankBullet(const Matrix3 a_m3StartPosRot, const unsigned int a_iOwnerID) :
	// Initialise Variable List
	iOwnerID(a_iOwnerID),
	fSpeed(0.f)
{
	Type = BULLET;
}

void TankBullet::CollideWith(Sprite * a_sprite)
{
	if (a_sprite->GetPlayerID() != iOwnerID) // If not Colliding with The Shooter
	{
		switch (a_sprite->GetType())
		{
		case PLAYER:
			// Explode Bullet
			CreateExplosion();
			// Destroy Player
			a_sprite->Destroy();
			// Destroy Bullet
			Destroy();
			break;
		case BULLET:
			// Explode Bullet
			CreateExplosion();
			// Destroy Bullet
			Destroy();
			break;

		case STATIC:
			// Explode Bullet
			CreateExplosion();
			// Destroy Bullet
			Destroy();
			break;
		}
	}
}

void TankBullet::CollideWithMap()
{
	// Explode Bullet
	CreateExplosion();
	// Destroy Bullet
	Destroy();
}

void TankBullet::Destroy()
{
	DestroySprite();
}

void TankBullet::CreateExplosion()
{
	// Get Level Controller Singleton
	LevelController* levelcontroller = &LevelController::GetLevelController();
	// Create Explosion
	levelcontroller->RegisterDynamicObject(new Explosion(m3PosRot));
}

// Basic Bullet Constructor
BasicBullet::BasicBullet() :
	// Initialise Variable List
	c_acBulletSheetFileName("./images/tanks/bullets/bulletbasicsheet.png"),
	v4BulletUVCoords {Vector4(SetSpriteUVCoords(0.f, 0.f, 12.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(12.f, 0.f, 24.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(24.f, 0.f, 36.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(36.f, 0.f, 48.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(48.f, 0.f, 60.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(60.f, 0.f, 72.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(72.f, 0.f, 84.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(84.f, 0.f, 96.f, 18.f, 96.f, 18.f))}
{
	Type = BULLET;
	fSpeed = 400.f;
	v2Dimensions = Vector2(12.f, 18.f);
	Initialise(); // Initialise Bullet
}

// Custom Constructor
BasicBullet::BasicBullet(const Matrix3 a_m3StartPosRot, const unsigned int a_iOwnerID) :
	c_acBulletSheetFileName("./images/tanks/bullets/basicbulletsheet.png"),
	v4BulletUVCoords{ Vector4(SetSpriteUVCoords(0.f, 0.f, 12.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(12.f, 0.f, 24.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(24.f, 0.f, 36.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(36.f, 0.f, 48.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(48.f, 0.f, 60.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(60.f, 0.f, 72.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(72.f, 0.f, 84.f, 18.f, 96.f, 18.f)),
					  Vector4(SetSpriteUVCoords(84.f, 0.f, 96.f, 18.f, 96.f, 18.f)) }
{
	Type = BULLET;
	iOwnerID = a_iOwnerID;
	fSpeed = 400.f;
	v2Dimensions = Vector2(12.f, 18.f);
	Initialise(a_m3StartPosRot);  // Initialise Bullet
}

void BasicBullet::Initialise()
{
	// Initialise Sprite
	InitialiseSprite(c_acBulletSheetFileName, v2Dimensions, v2Origin, v4BulletUVCoords[0]);
	// Initialise Animation Controller
	animationController.Initialise(iSpriteID, v4BulletUVCoords, 8);
	// Draw Sprite
	DrawSprite();
	// Set Layer
	SetLayer(2);
	// Set Sprite to Active
	bActive = true;
}

void BasicBullet::Initialise(const Matrix3 a_m3StartPosRot)
{
	// Initialise Sprite
	InitialiseSprite(c_acBulletSheetFileName, v2Dimensions, v2Origin, v4BulletUVCoords[0], a_m3StartPosRot);
	// Initialise Animation Controller
	animationController.Initialise(iSpriteID, v4BulletUVCoords, 8);
	// Draw Sprite
	DrawSprite();
	// Set Layer
	SetLayer(2);
	// Set Sprite to Active
	bActive = true;
}

void BasicBullet::Update(const float a_fDeltaTime)
{
	// Update Sprite
	UpdateSprite(a_fDeltaTime);

	// Set Velocity to Upwards/Forwards Vector
	v3Velocity = Vector3::Up;
	// Multiply Velocity Vector by Bullet Speed
	v3Velocity *= fSpeed * a_fDeltaTime;
	// Move Bullet
	MoveSprite();
	// Update Animation
	animationController.UpdateAnimation(a_fDeltaTime);
}

HomingBullet::HomingBullet() : 
	// Initialise Variable List
	c_acBulletSheetFileName("./images/tanks/bullets/homingbulletsheet.png"),
	v4BulletUVCoords { Vector4(SetSpriteUVCoords(0.f, 0.f, 12.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(12.f, 0.f, 24.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(24.f, 0.f, 36.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(36.f, 0.f, 48.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(48.f, 0.f, 60.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(60.f, 0.f, 72.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(72.f, 0.f, 84.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(84.f, 0.f, 96.f, 18.f, 96.f, 18.f)) }
{
	Type = BULLET;
	fSpeed = 300.f;
	v2Dimensions = Vector2(12.f, 18.f);
	Initialise();
}

HomingBullet::HomingBullet(const Matrix3 a_m3StartPosRot, const unsigned int a_iOwnerID) :
	// Initialise Variable List
	c_acBulletSheetFileName("./images/tanks/bullets/homingbulletsheet.png"),
	v4BulletUVCoords { Vector4(SetSpriteUVCoords(0.f, 0.f, 12.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(12.f, 0.f, 24.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(24.f, 0.f, 36.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(36.f, 0.f, 48.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(48.f, 0.f, 60.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(60.f, 0.f, 72.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(72.f, 0.f, 84.f, 18.f, 96.f, 18.f)),
					   Vector4(SetSpriteUVCoords(84.f, 0.f, 96.f, 18.f, 96.f, 18.f)) }
{
	Type = BULLET;
	iOwnerID = a_iOwnerID;
	fSpeed = 300.f;
	v2Dimensions = Vector2(12.f, 18.f);
	Initialise(a_m3StartPosRot);
}

void HomingBullet::Initialise()
{
	// Create and Draw Sprite and Initialise Animation
	InitialiseSprite(c_acBulletSheetFileName, v2Dimensions, v2Origin, v4BulletUVCoords[0]);
	animationController.Initialise(iSpriteID, v4BulletUVCoords, 8);
	DrawSprite();
	SetLayer(2);
	bActive = true;
	// Setup Enemy ID
	if (iOwnerID == 0)
	{
		iEnemyID = 1;
	}
	else if (iOwnerID == 1)
	{
		iEnemyID = 0;
	}
}

void HomingBullet::Initialise(const Matrix3 a_m3StartPosRot)
{
	InitialiseSprite(c_acBulletSheetFileName, v2Dimensions, v2Origin, v4BulletUVCoords[0], a_m3StartPosRot);
	animationController.Initialise(iSpriteID, v4BulletUVCoords, 8);
	DrawSprite();
	SetLayer(2);
	bActive = true;
	// Setup Enemy ID
	if (iOwnerID == 0)
	{
		iEnemyID = 1;
	}
	else if (iOwnerID == 1)
	{
		iEnemyID = 0;
	}
}

void HomingBullet::Update(const float a_fDeltaTime)
{
	// Get Level Controller Singleton
	LevelController* levelcontroller = &LevelController::GetLevelController();

	// Setup Movement Vector
	v3Velocity = Vector3::Up;

	// Get Current Position
	Vector3 v3CurrentPos = m3PosRot.GetRow(2);

	// Check Enemy Exists (Is Alive)
	if (levelcontroller->GetPlayerPos(iEnemyID) != Vector3::Zero) // Enemy Position Found
	{
		// Get Enemy Position
		Vector3 v3EnemyPos = levelcontroller->GetPlayerPos(iEnemyID);
		// Get Bullet To Enemy Vector
		Vector3 v3BullettoEnemy = (v3EnemyPos - v3CurrentPos).GetUnitVector();
		// Get Local Velocity
		Vector3 v3VelocityLocal = (v3Velocity * m3PosRot).GetUnitVector();

		if (v3VelocityLocal.DotProduct(v3BullettoEnemy) > 0) // Enemy Tank is in Line of Sight of Homing Bullet
		{
			HomingMove(a_fDeltaTime, v3BullettoEnemy); // Perform Homing Movement to Enemy
		}
		else
		{
			DefaultMove(a_fDeltaTime); // Move Normally
		}
	}
	else // Enemy Does not Exist (Just Move Bullet Forward)
	{
		DefaultMove(a_fDeltaTime);
	}
	
	// Update Animation
	animationController.UpdateAnimation(a_fDeltaTime);
	// Updates Sprite
	UpdateSprite(a_fDeltaTime);
}

void HomingBullet::DefaultMove(const float a_fDeltaTime)
{
	// Multiply Velocity Vector by Bullet Speed
	v3Velocity *= fSpeed * a_fDeltaTime;
	// Move Bullet
	MoveSprite();
}

void HomingBullet::HomingMove(const float a_fDeltaTime, Vector3 a_v3BullettoEnemy)
{
	float fRotateSpeed = 0.02f;
	float fCrossValue = -a_v3BullettoEnemy.CrossProduct(m3PosRot.GetRow(1)).GetZ();

	RotateZ(fRotateSpeed * fCrossValue);

	DefaultMove(a_fDeltaTime);
}