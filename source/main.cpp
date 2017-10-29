////////////////////////////////////////////////////////////////////
// File: <main.cpp>
// Author: <Alex Kitching>
// Date Created: <2/3/17>
// Brief: <Source file for the Main Function.>
////////////////////////////////////////////////////////////////////

#include "UGFW.h"
#include "GameController.h"
#include <time.h>

#pragma region Global Variables
// Screen Dimensions
int g_iScreenWidth = 0;
int g_iScreenHeight = 0;
#pragma endregion

int main(int argv, char* argc[])
{
	srand(static_cast<unsigned int>(time(0))); // Seed Random Gen

	if (UG::Create(1024, 768, false, "TinyTanks", 100, 100)) // Initialise Framework
	{
		// Set Background Colour and ScreenSize
		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));
		UG::GetScreenSize(g_iScreenWidth, g_iScreenHeight);

		// Create GameController Singleton
		GameController *gameController = &GameController::GetGameController();
		// Run Game Loop
		gameController->RunGameLoop();
		// Destroy GameController
		GameController::DestroyGameController();
	}
	return 0;
}
