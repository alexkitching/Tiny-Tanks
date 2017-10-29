#include "Explosion.h"
#include "Util.h"

Explosion::Explosion(const Matrix3 a_m3SpawnPosRot) :
	// Initialise Variable List
	c_acExplosionSheetFileName("./images/explosion/explosion.png"),
	v4ExplosionUVCoords { Vector4(SetSpriteUVCoords(0.f, 0.f, 48.f, 48.f, 576.f, 48.f)),
						  Vector4(SetSpriteUVCoords(48.f, 0.f, 96.f, 48.f, 576.f, 48.f)),
					      Vector4(SetSpriteUVCoords(96.f, 0.f, 144.f, 48.f, 576.f, 48.f)),
						  Vector4(SetSpriteUVCoords(144.f, 0.f, 192.f, 48.f, 576.f, 48.f)),
						  Vector4(SetSpriteUVCoords(192.f, 0.f, 240.f, 48.f, 576.f, 48.f)),
						  Vector4(SetSpriteUVCoords(240.f, 0.f, 288.f, 48.f, 576.f, 48.f)),
						  Vector4(SetSpriteUVCoords(288.f, 0.f, 336.f, 48.f, 576.f, 48.f)),
						  Vector4(SetSpriteUVCoords(336.f, 0.f, 384.f, 48.f, 576.f, 48.f)),
						  Vector4(SetSpriteUVCoords(384.f, 0.f, 432.f, 48.f, 576.f, 48.f)),
						  Vector4(SetSpriteUVCoords(432.f, 0.f, 480.f, 48.f, 576.f, 48.f)),
					      Vector4(SetSpriteUVCoords(480.f, 0.f, 528.f, 48.f, 576.f, 48.f)),
						  Vector4(SetSpriteUVCoords(528.f, 0.f, 576.f, 48.f, 576.f, 48.f)) }
{
	bCollideable = false;
	bMapCollideable = false;
	Type = EXPLOSION;
	v2Dimensions = Vector2(48.f, 48.f);
	Initialise(a_m3SpawnPosRot);
}

void Explosion::Update(const float a_fDeltaTime)
{
	// Update Sprite
	UpdateSprite(a_fDeltaTime);

	// Update Animation
	if (animationController.UpdateAnimationTrigger(a_fDeltaTime)) // When Animation has finished
	{
		Destroy(); // Destroy Explosion
	}
}

void Explosion::Destroy()
{
	DestroySprite(); // Destroy Sprite
}

void Explosion::Initialise(const Matrix3 a_m3SpawnPosRot)
{
	// Initialise Sprite
	InitialiseSprite(c_acExplosionSheetFileName, v2Dimensions, v2Origin, v4ExplosionUVCoords[0], a_m3SpawnPosRot);
	// Initialise Animation Controller
	animationController.Initialise(iSpriteID, v4ExplosionUVCoords, 12);
	// Draw Sprite
	DrawSprite();
	// Set Layer
	SetLayer(1);
	// Set Sprite to Active
	bActive = true;
}
