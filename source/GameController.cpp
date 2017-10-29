#include "GameController.h"
#include "UGFW.h"
#include <iostream>

GameController::GameController(bool a_bRunning, GameState a_gsStartState):
	// Initialise Variable List
	bRunning(a_bRunning),
	gsCurrentState(a_gsStartState),
	levelController(&LevelController::GetLevelController()),
	iPauseReason(-1),
	fNavDelayTime(0.2f)
{
}

GameController::~GameController()
{
	// Destroys Level Controller with GameController
	LevelController::DestroyLevelController();
}

GameController& GameController::GetGameController()
{
	static GameController* gameController = NULL; // Creates Blank Game Controller Singleton
	if (gameController == NULL) // If Singleton is Blank
	{
		gameController = new GameController(true, MENU); // Assign new GameController Object
		std::cout << "GameController created." << std::endl; // Print to Console
	}

	return *gameController; // Return GameController Singleton
}

void GameController::DestroyGameController()
{
	// Get Instance of Game Controller
	GameController *gameController = &GetGameController();

	if (gameController != NULL) // If Gamecontroller singleton is present
	{
		delete gameController; // Deletes GameController
		std::cout << "GameController destroyed." << std::endl; // Prints to Console
	}
}

void GameController::RunGameLoop()
{
	do
	{
		UG::ClearScreen(); // Clear Drawing
		fDeltaTime = UG::GetDeltaTime(); // Retrieve Delta Time
		switch (gsCurrentState) // Switch Between Game States
		{
		case MENU:
		{
			Menu.Update(fDeltaTime); // Update Menu
			break;
		}
		case GAMEPLAY:
		{
			if (!levelController->LevelInitialised()) // Level Not Initialised
			{
				levelController->InitialiseLevel(); // Initialise Level
			}
			levelController->UpdateObjects(fDeltaTime); // Update Level Objects
			break;
		}
		case PAUSED:
		{
			PauseMenu(); // Pause Menu
			break;
		}
		case GAMEOVER:
		{
			bRunning = false; // Program No longer running
			UG::Close(); // Close the program
			break;
		}
		}
	} while (UG::Process()); // Updates Current Frame
	UG::Dispose(); // Unloads Framework
}

void GameController::ChangeState(const GameState a_gsState)
{
	gsCurrentState = a_gsState; // Changes GameState
}

void GameController::PauseGame(const int a_iReason)
{
	iPauseReason = a_iReason; // Assigns Pause Reason
	ChangeState(PAUSED); // Change to PauseMenu
}

void GameController::PauseMenu()
{
	switch (iPauseReason) 
	{
	case 0: // Pause
			// Display Messages
		UG::DrawString("Game Paused", g_iScreenWidth * 0.4, g_iScreenHeight * 0.6);
		UG::DrawString("Press Escape again to Exit or Enter to Continue.", g_iScreenWidth * 0.2, g_iScreenHeight * 0.5);

		if (UG::IsKeyDown(UG::KEY_ESCAPE) && fNavDelayTime <= 0.f) // Escape Pressed
		{
			iPauseReason = -1; // Reset Pause Reason
			levelController->ResetLevel(); // Reset Level
			ChangeState(MENU); // Change to Menu
			// Set Nav Delay Time
			fNavDelayTime = 0.2f; // Reset Nav Delay
		}
		else if (UG::IsKeyDown(UG::KEY_ENTER) && fNavDelayTime <= 0.f) // Enter Pressed
		{
			iPauseReason = -1; // Reset Pause Reason
			ChangeState(GAMEPLAY); // Continue Gameplay
			// Set Nav Delay Time
			fNavDelayTime = 0.2f; // Reset Nav Delay
		}
		break;

	case 1: // Player 1 Won
		// Display Messages
		UG::DrawString("Player 1 Wins!", g_iScreenWidth * 0.4, g_iScreenHeight * 0.6);
		UG::DrawString("Press Escape to Exit.", g_iScreenWidth * 0.4, g_iScreenHeight * 0.5);

		if (UG::IsKeyDown(UG::KEY_ESCAPE) && fNavDelayTime <= 0.f) // Escape Pressed
		{
			iPauseReason = -1; // Reset Pause Reason
			levelController->ResetLevel(); // Reset Level
			ChangeState(MENU); // Change to Menu
			// Set Nav Delay Time
			fNavDelayTime = 0.2f; // Reset Nav Delay
		}
		break;

	case 2: // Player 2 Won
		UG::DrawString("Player 2 Wins!", g_iScreenWidth * 0.4, g_iScreenHeight * 0.6);
		UG::DrawString("Press Escape to Exit.", g_iScreenWidth * 0.4, g_iScreenHeight * 0.5);

		if (UG::IsKeyDown(UG::KEY_ESCAPE) && fNavDelayTime <= 0.f) // Escape Pressed
		{
			iPauseReason = -1; // Reset Pause Reason
			levelController->ResetLevel(); // Reset Level
			ChangeState(MENU); // Change to Menu
			// Set Nav Delay Time
			fNavDelayTime = 0.2f; // Reset Nav Delay
		}
		break;
	}
	if (fNavDelayTime > 0.f) // If Nav Delay has not elapsed
	{
		fNavDelayTime -= fDeltaTime; // Reduce Delay
	}
}
