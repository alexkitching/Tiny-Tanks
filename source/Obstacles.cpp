#include "Obstacles.h"
#include "UGFW.h"
#include "Util.h"

Obstacle::Pencil::Pencil(const Vector2 a_v2SpawnPos, const float a_fStartRot) :
	// Initialise Variable List
	// Sprite Image Definition
	// File Names
	c_acPencilFileName("./images/obstacles/pencil.png")
{
	bMapCollideable = false;
	Type = STATIC;
	v2Dimensions = Vector2(26, 471);
	Initialise(a_v2SpawnPos, a_fStartRot);
}

void Obstacle::Pencil::Initialise(const Vector2 a_v2SpawnPos, const float a_fStartRot)
{
	// Initialises Sprite
	InitialiseSprite(c_acPencilFileName, v2Dimensions, v2Origin);
	// Sets Position
	SetPosition(a_v2SpawnPos);
	// Sets Rotation
	RotateZ(DegreestoRadians(a_fStartRot));
	// Draws and Moves Sprite
	DrawSprite();
	SetLayer(1);
	MoveSprite();
	UpdateSprite(UG::GetDeltaTime());
	bActive = true;
}

void Obstacle::Pencil::Destroy()
{
	DestroySprite(); // Destroys Sprite
}

Obstacle::Eraser::Eraser(const Vector2 a_v2SpawnPos, const float a_fStartRot) :
	// Initialise Variable List
	// Sprite Image Definition
	// File Names
	c_acEraserFileName("./images/obstacles/eraser.png")
{
	bMapCollideable = false;
	Type = STATIC;
	v2Dimensions = Vector2(38.f, 70.f);
	Initialise(a_v2SpawnPos, a_fStartRot);
}

void Obstacle::Eraser::Initialise(const Vector2 a_v2SpawnPos, const float a_fStartRot)
{
	// Creates Sprite
	InitialiseSprite(c_acEraserFileName, v2Dimensions, v2Origin);
	// Sets Position
	SetPosition(a_v2SpawnPos);
	// Sets Rotation
	RotateZ(DegreestoRadians(a_fStartRot));
	// Draws and Moves Sprite
	DrawSprite();
	SetLayer(1);
	MoveSprite();
	UpdateSprite(UG::GetDeltaTime());
	bActive = true;
}

void Obstacle::Eraser::Destroy()
{
	DestroySprite(); // Destroys Sprite
}
