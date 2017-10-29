//////////////////////////////////////////////////////////////////////////
// File: <Tank.h>
// Author: <Alex Kitching>
// Date Created: <6/4/17>
// Brief: <Header file for all Tank Turret classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _TankTurret_H_
#define _TankTurret_H_

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Sprite.h"
#define _USE_MATH_DEFINES
#include <math.h>

class TankTurret : public Sprite
{
public:
	TankTurret(); // Constructor
	~TankTurret(); // Destructor

	// Functions
	void Initialise(const unsigned int a_iPlayerID, Node* a_Parent);
	Matrix3 GetBulletPosRot();
	void Destroy();
	void Update(const float a_fDeltaTime) override;
	void CollideWith(Sprite* a_Sprite) override {}; // Turret has no Collision
	void CollideWithMap() override {}; // No Collision with Map

private:
	// Sprite Image Definition
	// TankSheet
	char const c_acTankSheetFileName[32];
	// UV Coordinates
	Vector4 fv4TurretUVCoords[2];
};


#endif // !_TankTurret_H_
