//////////////////////////////////////////////////////////////////////////
// File: <Powerups.h>
// Author: <Alex Kitching>
// Date Created: <25/05/17>
// Brief: <Header file for all Powerup classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _Powerups_H_
#define _Powerups_H_

#include "Sprite.h"

namespace Powerup
{
	class Powerup : public Sprite
	{
	public:
		// Constructors
		Powerup();
		Powerup(const Vector2 a_v2SpawnPos, const int a_iSpawnIndex);
		~Powerup() {};

	protected:
		// Functions
		void Update(const float a_fDeltaTime) override {};
		void CollideWith(Sprite* a_Sprite) = 0;
		void CollideWithMap() override {};
		void Destroy() override;

		int iSpawnIndex;
	};

	class Life : public Powerup
	{
	public:
		// Constructors
		Life();
		Life(const Vector2 a_v2SpawnPos, const int a_iSpawnIndex);
		void Initialise(const Vector2 a_v2SpawnPos);
		void CollideWith(Sprite* a_Sprite);
	private:
		// Sprite Image Definition
		// File Names
		const char c_acPowerupFileName[32];
	};

	class Ammo : public Powerup
	{
	public:
		// Constructors
		Ammo();
		Ammo(Vector2 a_v2SpawnPos, int a_iSpawnIndex);
		void Initialise(const Vector2 a_v2SpawnPos);
		void CollideWith(Sprite* a_Sprite);
	private:
		// Sprite Image Definition
		// File Names
		const char c_acPowerupFileName[32];
	};

	class Homing : public Powerup
	{
	public:
		// Constructors
		Homing();
		Homing(Vector2 a_v2SpawnPos, int a_iSpawnIndex);
		void Initialise(const Vector2 a_v2SpawnPos);
		void CollideWith(Sprite* a_Sprite);
	private:
		// Sprite Image Definition
		// File Names
		const char c_acPowerupFileName[32];
	};

	class Mystery : public Powerup
	{
	public:
		// Constructors
		Mystery();
		Mystery(Vector2 a_v2SpawnPos, int a_iSpawnIndex);
		void Initialise(const Vector2 a_v2SpawnPos);
		void CollideWith(Sprite* a_Sprite);
	private:
		// Sprite Image Definition
		// File Names
		const char c_acPowerupFileName[32];
	};
}

#endif // !_Powerups_H_
