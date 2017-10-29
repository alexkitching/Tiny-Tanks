//////////////////////////////////////////////////////////////////////////
// File: <Sprite.h>
// Author: <Alex Kitching>
// Date Created: <30/03/17>
// Brief: <Header file for all Sprite classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _Sprite_H_
#define _Sprite_H_

#include "Node.h"
#include "Vector2.h"
#include "Vector3.h"
#include "GameObjectTypes.h"

class Matrix3;
class Vector4;
class Sprite : public Node
{
public:
	// Constructors
	Sprite();
	virtual ~Sprite();

	// Functions
	virtual void Update(const float a_fDeltaTime) = 0;
	virtual void CollideWith(Sprite* a_Sprite) = 0;
	virtual void CollideWithMap() = 0;

	virtual void Destroy() = 0;

	Vector3 GetPosition() const;
	Vector2 GetDimensions() const;
	Vector3* GetCurrentVerts() const;
	Vector3 GetVelocity() const;

	int GetPlayerID() const;

	GameObjectType GetType() const;

	bool IsCollideable() const;
	bool IsMapCollideable() const;

	void SetActive(const bool a_active);
	bool IsActive() const;
	
	// Collision Detection Function
	bool CheckMapCollision();


protected:

	// Functions
	void InitialiseSprite(const char * ac_cFileName, const Vector2 a_v2Dimensions, const Vector2 a_v2Origin);
	void InitialiseSprite(const char * ac_cFileName, const Vector2 a_v2Dimensions, const Vector2 a_v2Origin, const Vector4 a_v4UVCoords);
	void InitialiseSprite(const char * ac_cFileName, const Vector2 a_v2Dimensions, const Vector2 a_v2Origin, const Vector4 a_v4UVCoords, const Matrix3 a_m3PosRot);
	void SetLayer(const unsigned int a_uiLayer);
	void UpdateSprite(const float a_fDelta);
	void MoveSprite();
	void DrawSprite();
	void StopDrawingSprite();
	void DestroySprite();
	void SetPosition(const Vector2 a_v2Pos);
	void SetPosition(const Vector3 a_v2Pos);

	
	int iPlayerID; // Only assigned to Player Sprites
	int iSpriteID;
	GameObjectType Type;

	Vector3 v3Velocity;
	bool bCollideable;
	bool bMapCollideable;
	bool bActive;
	bool bDrawn;
	Vector2 v2Dimensions;
	Vector2 v2Origin;
private:
};

#endif # !_Sprite_H_