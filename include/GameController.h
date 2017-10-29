//////////////////////////////////////////////////////////////////////////
// File: <GameController.h>
// Author: <Alex Kitching>
// Date Created: <6/4/17>
// Brief: <Header file for the Game Controller class, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Enumerations.h"
#include "GameStates.h"
#include "Menu.h"
#include "LevelController.h"

class GameController
{
public:
	static GameController& GetGameController();
	static void DestroyGameController();
	void RunGameLoop();
	void ChangeState(const GameState a_gsState);
	void PauseGame(const int a_iReason); // a_iReason - 0, Pause, 1, Player 1 Won, 2, Player 2 Won
	void PauseMenu();
	

private:
	// Constructors
	GameController(bool a_bRunning, GameState a_gsStartState);
	~GameController();

	// General Variables
	bool bRunning;
	GameState gsCurrentState;
	float fDeltaTime;

	// Pause Menu Variables
	int iPauseReason;
	float fNavDelayTime;

	// Objects
	Menu Menu;
	LevelController* levelController;

};

#endif // ! _GAMECONTROLLER_H_
