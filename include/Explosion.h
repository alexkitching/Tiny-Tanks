//////////////////////////////////////////////////////////////////////////
// File: <Explosion.h>
// Author: <Alex Kitching>
// Date Created: <25/05/17>
// Brief: <Header file for Explosion classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _Explosion_H_
#define _Explosion_H_

#include "Sprite.h"
#include "Vector4.h"
#include "AnimationController.h"

class Matrix3;
class Explosion : public Sprite
{
public :
	Explosion(const Matrix3 a_m3SpawnPosRot);
	~Explosion() {};
	void Update(const float a_fDeltaTime) override;
	void CollideWith(Sprite* a_Sprite) override {};
	void CollideWithMap() override {};
	void Destroy() override;
private:
	void Initialise(const Matrix3 a_m3SpawnPosRot);

	// Sprite Image Definition
	// File Names
	const char c_acExplosionSheetFileName[33];
	// UV Coordinates
	Vector4 v4ExplosionUVCoords[12];

	// Sprite Animation Controller
	AnimationController animationController;
};

#endif // !_Explosion_H_
