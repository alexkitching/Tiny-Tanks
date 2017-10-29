//////////////////////////////////////////////////////////////////////////
// File: <TankTurret.cpp>
// Author: <Alex Kitching>
// Date Created: <6/4/17>
// Brief: <Source file for the Tank Turret class.>
/////////////////////////////////////////////////////////////////////////

#include "TankTurret.h"
#include "UGFW.h"
#include "Util.h"

TankTurret::TankTurret() :
	// Initialise Variable List
	// Sprite Image Definition
	// TankSheet
	c_acTankSheetFileName("./images/tanks/turretsheet.png"),
	// UV Coordinates
	fv4TurretUVCoords{ { SetSpriteUVCoords(31.f, 0.f, 61.f, 60.f, 61.f, 60.f) }, // Player 1
				       { SetSpriteUVCoords(0.f, 0.f, 30.f, 60.f, 61.f, 60.f) } } // Player 2
{
	v2Dimensions = Vector2(30.f, 59.f);
	v2Origin = Vector2(0.5f, 0.3f);
	Type = PLAYER;
}

TankTurret::~TankTurret()
{
}

void TankTurret::Initialise(const unsigned int a_iPlayerID, Node* a_Parent)
{
	// Create and Draw Sprite and Assign parent
	InitialiseSprite(c_acTankSheetFileName, v2Dimensions, v2Origin, fv4TurretUVCoords[a_iPlayerID]);
	SetParent(a_Parent);
	SetPosition(Vector2(m3PosRot.GetValue(2, 0), m3PosRot.GetValue(2, 1) + 5.f)); // Move Turret to Correct Location on Tank
	DrawSprite();
	SetLayer(2);
}

Matrix3 TankTurret::GetBulletPosRot()
{
	// Get End of Turret Relative Position
	Vector3 v3TopVert = Vector3(0.f, 0.75 * GetDimensions().GetY(), 0.f);

	// Get Current Position of Turret
	Matrix3 m3WorldTx = Matrix3::Identity;
	GetWorldTransform(m3WorldTx);
	Vector3 v3CurrentPos = m3WorldTx.GetRow(2);

	// Add Relative Turret End Position to Current Position
	v3CurrentPos += v3TopVert * m3WorldTx;

	// Set Matrix and Return
	m3WorldTx.SetRow(2, v3CurrentPos);
	return m3WorldTx;
}

void TankTurret::Update(const float a_fDeltaTime)
{
	UpdateSprite(a_fDeltaTime); // Update Sprite
}

void TankTurret::Destroy()
{
	DestroySprite(); // Destroy Sprite
}
