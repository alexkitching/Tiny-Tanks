//////////////////////////////////////////////////////////////////////////
// File: <Obstacles.h>
// Author: <Alex Kitching>
// Date Created: <24/05/17>
// Brief: <Header file for all Obstacle classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _Obstacles_H_
#define _Obstacles_H_

#include "Sprite.h"
namespace Obstacle
{
	class Pencil : public Sprite
	{
	public:
		// Constructors
		Pencil(const Vector2 a_v2SpawnPos, const float a_fStartRot);
		~Pencil() {};
	private:
		// Functions
		void Initialise(const Vector2 a_v2SpawnPos, const float a_fStartRot);
		void Update(const float a_fDeltaTime) override {};
		void CollideWith(Sprite* a_Sprite) override {};
		void CollideWithMap() override {};
		void Destroy() override;
		// Sprite Image Definition
		// File Names
		char const c_acPencilFileName[32];
	};

	class Eraser : public Sprite
	{
	public:
		// Constructors
		Eraser(const Vector2 a_v2SpawnPos, const float a_fStartRot);
		~Eraser() {};
	private:
		// Functions
		void Initialise(const Vector2 a_v2SpawnPos, const float a_fStartRot);
		void Update(const float a_fDeltaTime) override {};
		void CollideWith(Sprite* a_Sprite) override {};
		void CollideWithMap() override {};
		void Destroy() override;

		// Sprite Image Definition
		// File Names
		char const c_acEraserFileName[32];
	};
}


#endif // !_Obstacles_H_
