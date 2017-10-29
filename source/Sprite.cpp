//////////////////////////////////////////////////////////////////////////
// File: <Sprite.cpp>
// Author: <Alex Kitching>
// Date Created: <30/03/17>
// Brief: <Source file for the Sprite class.>
/////////////////////////////////////////////////////////////////////////

#include "Sprite.h";
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "UGFW.h";

extern int g_iScreenHeight;
extern int g_iScreenWidth;

Sprite::Sprite() :
	iPlayerID(-1), // Assigned to Players
	iSpriteID(-1),
	v3Velocity(Vector3::Zero),
	bCollideable(true),
	bMapCollideable(true),
	bActive(false),
	bDrawn(false),
	v2Dimensions(Vector2::Zero),
	v2Origin(Vector2(0.5f, 0.5f)),
	Type(STATIC) // Default Type to Static
{
}

Sprite::~Sprite()
{
	UG::DestroySprite(iSpriteID);
}

Vector3 Sprite::GetPosition() const
{
	return m3PosRot.GetRow(2);
}

Vector2 Sprite::GetDimensions() const 
{
	return v2Dimensions;
}

Vector3* Sprite::GetCurrentVerts() const
{
	float fCurrentHalfWidth = 0.5 * GetDimensions().GetX();
	float fCurrentHalfHeight = 0.5 * GetDimensions().GetY();
	Vector3 v3CurrentVerts[4];
	Vector3 v3CurrentPos = m3PosRot.GetRow(2);
	v3CurrentVerts[0] = Vector2(-fCurrentHalfWidth, fCurrentHalfHeight); // Top Left
	v3CurrentVerts[1] = Vector2(fCurrentHalfWidth, fCurrentHalfHeight); // Top Right
	v3CurrentVerts[2] = Vector2(fCurrentHalfWidth, -fCurrentHalfHeight); // Bottom Right
	v3CurrentVerts[3] = Vector2(-fCurrentHalfWidth, -fCurrentHalfHeight); // Bottom Left
	for (int i = 0; i < 4; i++)
	{ // Align Current Verts by Current Rotation
		v3CurrentVerts[i] = v3CurrentVerts[i] * this->m3PosRot;
		v3CurrentVerts[i] = v3CurrentPos + v3CurrentVerts[i];
	}
	return v3CurrentVerts;
}

Vector3 Sprite::GetVelocity() const
{
	return v3Velocity;
}

int Sprite::GetPlayerID() const
{
	return iPlayerID;
}

GameObjectType Sprite::GetType() const
{
	return Type;
}

bool Sprite::IsCollideable() const
{
	return bCollideable;
}

bool Sprite::IsMapCollideable() const
{
	return bMapCollideable;
}

void Sprite::SetActive(const bool a_active)
{
	bActive = a_active;
}

bool Sprite::IsActive() const
{
	return bActive;
}

void Sprite::InitialiseSprite(const char * ac_cFileName, const Vector2 a_v2Dimensions, const Vector2 a_v2Origin)
{
	iSpriteID = UG::CreateSprite(ac_cFileName, a_v2Dimensions, a_v2Origin);
	v2Dimensions = a_v2Dimensions;
	Matrix4 m4x4 = Matrix4::Identity;
	UG::GetSpriteMatrix(iSpriteID, m4x4);
	m3PosRot = Matrix3(m4x4.GetValue(0, 0), m4x4.GetValue(0, 1), m4x4.GetValue(0, 2),
		m4x4.GetValue(1, 0), m4x4.GetValue(1, 1), m4x4.GetValue(1, 2),
		m4x4.GetValue(3, 0), m4x4.GetValue(3, 1), 1.f);
}

void Sprite::InitialiseSprite(const char * ac_cFileName, const Vector2 a_v2Dimensions, const Vector2 a_v2Origin, const Vector4 a_v4UVCoords)
{
	iSpriteID = UG::CreateSprite(ac_cFileName, a_v2Dimensions, a_v2Origin, a_v4UVCoords);
	v2Dimensions = a_v2Dimensions;
	Matrix4 m4x4 = Matrix4::Identity;
	UG::GetSpriteMatrix(iSpriteID, m4x4);
	m3PosRot = Matrix3(m4x4.GetValue(0, 0), m4x4.GetValue(0, 1), m4x4.GetValue(0, 2),
					   m4x4.GetValue(1, 0), m4x4.GetValue(1, 1), m4x4.GetValue(1, 2),
					   m4x4.GetValue(3, 0), m4x4.GetValue(3, 1), 1.f);
}

void Sprite::InitialiseSprite(const char * ac_cFileName, const Vector2 a_v2Dimensions, const Vector2 a_v2Origin, const Vector4 a_v4UVCoords, const Matrix3 a_m3PosRot)
{
	iSpriteID = UG::CreateSprite(ac_cFileName, a_v2Dimensions, a_v2Origin, a_v4UVCoords);
	v2Dimensions = a_v2Dimensions;
	Matrix4 m4x4 = Matrix4::Identity;
	UG::GetSpriteMatrix(iSpriteID, m4x4);
	m3PosRot = a_m3PosRot;
}

void Sprite::SetLayer(const unsigned int a_uiLayer)
{
	UG::SetSpriteLayer(iSpriteID, a_uiLayer);
}
// An update function to call each frame to update our sprites data
void Sprite::UpdateSprite(const float a_fDelta)
{
	// OpenGL which is the underlying rendering pipeline that is being used by the framework
	// draws all components using a 4x4 matrix to represent their world coordinates, here I am constructing that matrix
	// from the 3x3 matrix that we are using internally.
	// Set the sprites matrix.
	Matrix3 m3WorldTransform = Matrix3::Identity;
	GetWorldTransform(m3WorldTransform);

	Matrix4 m4x4;
	m4x4.SetValue(0, 0, m3WorldTransform.GetValue(0, 0)), m4x4.SetValue(0, 1, m3WorldTransform.GetValue(0, 1)), m4x4.SetValue(0, 2, m3WorldTransform.GetValue(0, 2)), m4x4.SetValue(0, 3, 0.f);

	m4x4.SetValue(1, 0, m3WorldTransform.GetValue(1, 0)), m4x4.SetValue(1, 1, m3WorldTransform.GetValue(1, 1)), m4x4.SetValue(1, 2, m3WorldTransform.GetValue(1, 2)), m4x4.SetValue(1, 3, 0.f);

	m4x4.SetValue(2, 0, 0.f), m4x4.SetValue(2, 1, 0.f), m4x4.SetValue(2, 2, 1.f), m4x4.SetValue(2, 3, 0.f);

	m4x4.SetValue(3, 0, m3WorldTransform.GetValue(2, 0)), m4x4.SetValue(3, 1, m3WorldTransform.GetValue(2, 1)), m4x4.SetValue(3, 2, 0.f), m4x4.SetValue(3, 3, 1.f);
	
	UG::SetSpriteMatrix(iSpriteID, m4x4);
}

// Function to move sprite
// Movement vector not guaranteed unit vector since it may be scaled via a velocity.
void Sprite::MoveSprite()
{
	Vector3 v3CurrentPos;
	v3CurrentPos = m3PosRot.GetRow(2);
	// Multiplying the movement vector by the local transform will put the vector in local space of the object.
	v3CurrentPos += (v3Velocity * m3PosRot);

	m3PosRot.SetRow(2, v3CurrentPos);
}

void Sprite::DrawSprite()
{
	UG::DrawSprite(iSpriteID);
	bDrawn = true;
}

void Sprite::StopDrawingSprite()
{
	UG::StopDrawingSprite(iSpriteID);
	bDrawn = false;
}

void Sprite::DestroySprite()
{
	bActive = false;
	if (bDrawn) // Sprite is Still Drawn
	{
		StopDrawingSprite();
	}
	UG::DestroySprite(iSpriteID);
}

void Sprite::SetPosition(const Vector2 a_v2Pos)
{
	Vector3 v3NewPos = Vector3(a_v2Pos.GetX(), a_v2Pos.GetY(), 1.f);
	m3PosRot.SetRow(2, v3NewPos);
}

void Sprite::SetPosition(const Vector3 a_v2Pos)
{
	Vector3 v3NewPos = a_v2Pos;
	m3PosRot.SetRow(2, v3NewPos);
}

bool Sprite::CheckMapCollision()
{
	Vector3 v3CurrentPos = m3PosRot.GetRow(2);
	if (v3CurrentPos.GetX() >= g_iScreenWidth - v2Dimensions.GetX())
	{ // If at right Map Boundary
		return true;
	}
	else if (v3CurrentPos.GetX() <= v2Dimensions.GetX())
	{ // If at left Map Boundary
		return true;
	}

	if (v3CurrentPos.GetY() >= g_iScreenHeight - v2Dimensions.GetY())
	{ // If at top Map Boundary
		return true;
	}
	else if (v3CurrentPos.GetY() <= v2Dimensions.GetY())
	{ // If at bottom map boundary
		return true;
	}
	// If no hit
	return false;
}