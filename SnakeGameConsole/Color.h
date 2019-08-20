#pragma once
#include <windows.h>

/*
* Note(fex): These colors depend on the command promt's 'Color Scheme'.
* Therefore, the game used in different command promts or in different Windows builds may show colors differently.
* Windows 10 build 16257 changed this color scheme for the first time in Windows history (see: https://devblogs.microsoft.com/commandline/updating-the-windows-console-colors/).
* Also, Windows Powershell and other alternative terminals usually use there own custom color scheme.
*/
enum Color
{
	BLACK,
	RED               = FOREGROUND_RED,
	GREEN             = FOREGROUND_GREEN,
	BLUE              = FOREGROUND_BLUE,
	YELLOW            = RED     | GREEN,
	CYAN              = BLUE    | GREEN,
	MAGENTA           = RED     | BLUE,
	GRAY              = RED     | GREEN | BLUE,
	LIGHT_RED         = RED     | FOREGROUND_INTENSITY,
	LIGHT_GREEN       = GREEN   | FOREGROUND_INTENSITY,
	LIGHT_BLUE        = BLUE    | FOREGROUND_INTENSITY,
	LIGHT_YELLOW      = YELLOW  | FOREGROUND_INTENSITY,
	LIGHT_CYAN        = CYAN    | FOREGROUND_INTENSITY,
	PINK              = MAGENTA | FOREGROUND_INTENSITY,
	WHITE             = GRAY    | FOREGROUND_INTENSITY,
	BACK_BLACK        = BLACK,
	BACK_RED          = BACKGROUND_RED,
	BACK_GREEN        = BACKGROUND_GREEN,
	BACK_BLUE         = BACKGROUND_BLUE,
	BACK_YELLOW       = BACK_RED     | BACK_GREEN,
	BACK_CYAN         = BACK_BLUE    | BACK_GREEN,
	BACK_MAGENTA      = BACK_RED     | BACK_BLUE,
	BACK_GRAY         = BACK_RED     | BACK_BLUE | BACK_GREEN,
	BACK_LIGHT_RED    = BACK_RED     | FOREGROUND_INTENSITY,
	BACK_LIGHT_GREEN  = BACK_GREEN   | FOREGROUND_INTENSITY,
	BACK_LIGHT_BLUE   = BACK_BLUE    | FOREGROUND_INTENSITY,
	BACK_LIGHT_YELLOW = BACK_YELLOW  | FOREGROUND_INTENSITY,
	BACK_LIGHT_CYAN   = BACK_CYAN    | FOREGROUND_INTENSITY,
	BACK_PINK         = BACK_MAGENTA | FOREGROUND_INTENSITY,
	BACK_WHITE        = BACK_GRAY    | FOREGROUND_INTENSITY
};
