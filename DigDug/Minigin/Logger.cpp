#include "MiniginPCH.h"
#include "Logger.h"
#include <fstream>
#include <SDL.h>
#include "InputManager.h"


//CODE FROM THE SDL2.0 WIKI ON HOW TO CREATE MESSAGEBOX
//https://wiki.libsdl.org/SDL_ShowMessageBox
void dae::Logger::LogError(const std::string& errorMsg) 
{
	const SDL_MessageBoxButtonData buttons[] = {
	//{ /* .flags, .buttonid, .text */        0, 0, "no" },
	//{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
	//{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
	{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Quit" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{   0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{   0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		NULL, /* .window */
		"Error occured", /* .title */
		errorMsg.c_str(), /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		//return -1;
	}
	//if (buttonid == -1) {
	//	SDL_Log("no selection");
	//}
	//else {
	//	SDL_Log("selection was %s", buttons[buttonid].text);
	//}
	if (buttonid == 0) {
		InputManager::GetInstance().QuitGame();
	}
}
