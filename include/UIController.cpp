//////////////////////////////////////////////////////////////////////////
// File: <UIController.cpp>
// Author: <Alex Kitching>
// Date Created: <25/05/17>
// Brief: <Source file for all UIController classes, functions and variables.>
/////////////////////////////////////////////////////////////////////////

#include "UIController.h"
#include "UGFW.h"
#include <sstream>

UIController::UIController()
{
}

void UIController::DrawUI(const int a_iPlayer1Lives, const int a_iPlayer2Lives, const int a_iPlayer1Ammo, const int a_iPlayer2Ammo) const
{
	// Setup UI Strings
	std::stringstream ssPlayer1Lives;
	std::stringstream ssPlayer1Ammo;
	std::stringstream ssPlayer2Lives;
	std::stringstream ssPlayer2Ammo;
	ssPlayer1Lives << a_iPlayer1Lives;
	ssPlayer1Ammo << a_iPlayer1Ammo;
	ssPlayer2Lives << a_iPlayer2Lives;
	ssPlayer2Ammo << a_iPlayer2Ammo;
	std::string sPlayer1Lives = "Lives: " + ssPlayer1Lives.str() + "/5";
	std::string sPlayer1Ammo = "Ammo: " + ssPlayer1Ammo.str() + "/6";
	std::string sPlayer2Lives = "Lives: " + ssPlayer2Lives.str() + "/5";
	std::string sPlayer2Ammo = "Ammo: " + ssPlayer2Ammo.str() + "/6";
	std::string sPlayerSpecial = "Homing Missile Equipped.";
	const char * c_cPlayer1Lives = sPlayer1Lives.c_str();
	const char * c_cPlayer1Ammo = sPlayer1Ammo.c_str();
	const char * c_cPlayer2Lives = sPlayer2Lives.c_str();
	const char * c_cPlayer2Ammo = sPlayer2Ammo.c_str();
	const char * c_cPlayerSpecial = sPlayerSpecial.c_str();

	// Draw Player 1 Stats
	UG::DrawString("Player 1", 30, g_iScreenHeight - 30);
	UG::DrawString(c_cPlayer1Lives, 30, g_iScreenHeight - 60);
	UG::DrawString(c_cPlayer1Ammo, 30, g_iScreenHeight - 90);
	if (bPlayer1SpecialEquipped) // Player 1 has Special Equipped
	{
		UG::DrawString(c_cPlayerSpecial, 30, g_iScreenHeight - 120); // Draw Player Special String
	}

	// Draw Player 2 Stats
	UG::DrawString("Player 2", g_iScreenWidth - 160, g_iScreenHeight - 30);
	UG::DrawString(c_cPlayer2Lives, g_iScreenWidth - 160, g_iScreenHeight - 60);
	UG::DrawString(c_cPlayer2Ammo, g_iScreenWidth - 160, g_iScreenHeight - 90);
	if (bPlayer2SpecialEquipped) // Player 2 has Special Equipped
	{
		UG::DrawString(c_cPlayerSpecial, 160, g_iScreenHeight - 120); // Draw Player Special String
	}
}

void UIController::DrawPlayerSpecial(const int a_iPlayerID)
{
	if (a_iPlayerID == 0) // Player 1
	{
		bPlayer1SpecialEquipped = true;
	}
	else if(a_iPlayerID == 1) // Player 2
	{
		bPlayer2SpecialEquipped = true;
	}
}

void UIController::StopDrawingPlayerSpecial(const int a_iPlayerID)
{
	if (a_iPlayerID == 0) // Player 1
	{
		bPlayer1SpecialEquipped = false;
	}
	else if (a_iPlayerID == 1) // Player 2
	{
		bPlayer2SpecialEquipped = false;
	}
}
