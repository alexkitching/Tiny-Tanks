/////////////////////////////////////////////////////////////////////////
// File: <TankBullet.h>
// Author: <Alex Kitching>
// Date Created: <19/05/17>
// Brief: <Header file for Tank Bullet classes functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _TankBullet_H_
#define _TankBullet_H_

#include "Sprite.h"
#include "AnimationController.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class Matrix3;
class TankBullet : public Sprite
{
public:
	TankBullet();
	TankBullet(const Matrix3 a_m3StartPosRot, const unsigned int a_iOwnerID);
	virtual ~TankBullet() {};
	virtual void Update(const float a_fDeltaTime) = 0;
	void CollideWith(Sprite* a_sprite) override;
	void CollideWithMap() override;
	void Destroy() override;

protected:
	void CreateExplosion();
	// Owner ID Variables
	unsigned int iOwnerID;

	// Speed Variables
	float fSpeed;
};

class BasicBullet : public TankBullet
{
public:
	BasicBullet();
	BasicBullet(const Matrix3 a_m3StartPosRot, const unsigned int a_iOwnerID);
	void Initialise();
	void Initialise(const Matrix3 a_m3StartPosRot);
	void Update(const float a_fDeltaTime) override;
private:
	// Sprite Image Definition
	// File Names
	const char c_acBulletSheetFileName[44];
	// UV Coordinates
	Vector4 v4BulletUVCoords[8];
	
	// Sprite Animation Controller
	AnimationController animationController;
};

class HomingBullet : public TankBullet
{
public:
	HomingBullet();
	HomingBullet(const Matrix3 a_m3StartPosRot, const unsigned int a_iOwnerID);
	void Initialise();
	void Initialise(const Matrix3 a_m3StartPosRot);
	void Update(const float a_fDeltaTime) override;
	void DefaultMove(const float a_fDeltaTime);
	void HomingMove(const float a_fDeltaTime, Vector3 a_v3BullettoEnemy);
private:
	unsigned int iEnemyID;
	// Sprite Image Definition
	// File Names
	const char c_acBulletSheetFileName[45];
	// UV Coordinates
	Vector4 v4BulletUVCoords[8];

	// Sprite Animation Controller
	AnimationController animationController;
};
#endif // !_TankBullet_H_
