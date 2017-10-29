//////////////////////////////////////////////////////////////////////////
// File: <UIController.h>
// Author: <Alex Kitching>
// Date Created: <25/05/17>
// Brief: <Header file for UIController classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#ifndef _UIController_H_
#define _UIController_H_

extern int g_iScreenWidth;
extern int g_iScreenHeight;

class UIController
{
public:
	// Constructors
	UIController();
	~UIController() {};

	// Functions
	void DrawUI(const int a_iPlayer1Lives, const int a_iPlayer2Lives, const int a_iPlayer1Ammo, const int a_iPlayer2Ammo) const;
	void DrawPlayerSpecial(const int a_iPlayerID);
	void StopDrawingPlayerSpecial(const int a_iPlayerID);
private:
	// Variables
	bool bPlayer1SpecialEquipped;
	bool bPlayer2SpecialEquipped;
};

#endif // !_UIController_H_
