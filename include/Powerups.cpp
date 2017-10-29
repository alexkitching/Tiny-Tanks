#include "Powerups.h"
#include "LevelController.h"
#include "Util.h"
#include "UGFW.h"

Powerup::Powerup::Powerup()
{
	bMapCollideable = false;
	v2Dimensions = Vector2(24.f, 24.f);
}

Powerup::Powerup::Powerup(const Vector2 a_v2SpawnPos, const int a_iSpawnIndex) :
	iSpawnIndex(a_iSpawnIndex)
{
	bMapCollideable = false;
	v2Dimensions = Vector2(24.f, 24.f);
}

void Powerup::Powerup::CollideWith(Sprite * a_Sprite)
{
	if (a_Sprite->GetType() == PLAYER)
	{
		Destroy();
	}
}

void Powerup::Powerup::Destroy()
{
	// Get Level Controller Singleton
	LevelController* levelController = &LevelController::GetLevelController();
	levelController->ResetPowerupSpawn(iSpawnIndex);
	DestroySprite();
}

Powerup::Life::Life() : 
	c_acPowerupFileName("./images/powerups/life.png")
{
	bMapCollideable = false;
	Type = LIFEPOWERUP;
	v2Dimensions = Vector2(24.f, 24.f);
}

Powerup::Life::Life(const Vector2 a_v2SpawnPos, const int a_iSpawnIndex) :
	c_acPowerupFileName("./images/powerups/life.png")
{
	iSpawnIndex = a_iSpawnIndex;
	bMapCollideable = false;
	Type = LIFEPOWERUP;
	v2Dimensions = Vector2(24.f, 24.f);
	Initialise(a_v2SpawnPos);
}

void Powerup::Life::Initialise(const Vector2 a_v2SpawnPos)
{
	InitialiseSprite(c_acPowerupFileName ,v2Dimensions, v2Origin);
	SetPosition(a_v2SpawnPos);
	DrawSprite();
	MoveSprite();
	UpdateSprite(UG::GetDeltaTime());
	SetLayer(1);
	bActive = true;
}

void Powerup::Life::CollideWith(Sprite * a_Sprite)
{
	if (a_Sprite->GetType() == PLAYER)
	{
		Destroy(); // Destroy Powerup
	}
}

Powerup::Ammo::Ammo()  :
	c_acPowerupFileName("./images/powerups/ammo.png")
{
	bMapCollideable = false;
	Type = AMMOPOWERUP;
	v2Dimensions = Vector2(24.f, 24.f);
}

Powerup::Ammo::Ammo(const Vector2 a_v2SpawnPos, const int a_iSpawnIndex) :
	c_acPowerupFileName("./images/powerups/ammo.png")
{
	iSpawnIndex = a_iSpawnIndex;
	bMapCollideable = false;
	Type = AMMOPOWERUP;
	v2Dimensions = Vector2(24.f, 24.f);
	Initialise(a_v2SpawnPos);
}

void Powerup::Ammo::Initialise(const Vector2 a_v2SpawnPos)
{
	InitialiseSprite(c_acPowerupFileName, v2Dimensions, v2Origin);
	SetPosition(a_v2SpawnPos);
	DrawSprite();
	MoveSprite();
	UpdateSprite(UG::GetDeltaTime());
	SetLayer(1);
	bActive = true;
}

void Powerup::Ammo::CollideWith(Sprite * a_Sprite)
{
	if (a_Sprite->GetType() == PLAYER)
	{
		Destroy(); // Destroy Powerup
	}
}

Powerup::Homing::Homing() :
	c_acPowerupFileName("./images/powerups/homing.png")
{
	bMapCollideable = false;
	Type = HOMINGPOWERUP;
	v2Dimensions = Vector2(24.f, 24.f);
}

Powerup::Homing::Homing(const Vector2 a_v2SpawnPos, const int a_iSpawnIndex) :
	c_acPowerupFileName("./images/powerups/homing.png")
{
	iSpawnIndex = a_iSpawnIndex;
	bMapCollideable = false;
	Type = HOMINGPOWERUP;
	v2Dimensions = Vector2(24.f, 24.f);
	Initialise(a_v2SpawnPos);
}

void Powerup::Homing::Initialise(const Vector2 a_v2SpawnPos)
{
	InitialiseSprite(c_acPowerupFileName, v2Dimensions, v2Origin);
	SetPosition(a_v2SpawnPos);
	DrawSprite();
	MoveSprite();
	UpdateSprite(UG::GetDeltaTime());
	SetLayer(1);
	bActive = true;
}

void Powerup::Homing::CollideWith(Sprite * a_Sprite)
{
	if (a_Sprite->GetType() == PLAYER)
	{
		Destroy(); // Destroy Powerup
	}
}

Powerup::Mystery::Mystery() :
	c_acPowerupFileName("./images/powerups/mystery.png")
{
	bMapCollideable = false;
	Type = MYSTERYPOWERUP;
	v2Dimensions = Vector2(24.f, 24.f);
}

Powerup::Mystery::Mystery(const Vector2 a_v2SpawnPos, const int a_iSpawnIndex) :
	c_acPowerupFileName("./images/powerups/mystery.png")
{
	iSpawnIndex = a_iSpawnIndex;
	bMapCollideable = false;
	Type = MYSTERYPOWERUP;
	v2Dimensions = Vector2(24.f, 24.f);
	Initialise(a_v2SpawnPos);
}

void Powerup::Mystery::Initialise(const Vector2 a_v2SpawnPos)
{
	InitialiseSprite(c_acPowerupFileName, v2Dimensions, v2Origin);
	SetPosition(a_v2SpawnPos);
	DrawSprite();
	MoveSprite();
	UpdateSprite(UG::GetDeltaTime());
	SetLayer(1);
	bActive = true;
}

void Powerup::Mystery::CollideWith(Sprite * a_Sprite)
{
	if (a_Sprite->GetType() == PLAYER)
	{
		Destroy(); // Destroy Powerup
	}
}
