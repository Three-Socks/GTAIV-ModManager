/**
 * GTAIV ModManager V1.2
 *
 * This file is from: https://bitbucket.org/ThreeSocks/gtaiv-modmanager/
 *
 * By Three-Socks
 *
 * Important: Make sure you use the /inc/natives.h with the one included in the IVPS3.Scocl.zip (http://psx-scene.com/forums/f276/%5Btut%5D-how-compile-code-example-scripts-102230/#post963207). 
 * It contains a bug fix that is needed for modmanager to compile correctly.
 *
 */

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>

#include "functions.c"

void DoModManager(void)
{
	if (!IS_FONT_LOADED(6))
	{
		LOAD_TEXT_FONT(6);
	}
	HIDE_HUD_AND_RADAR_THIS_FRAME();
	DRAW_RECT(0.5000, 0.5000, 1.0000, 1.0000, 0, 0, 0, 167);
	INIT_FRONTEND_HELPER_TEXT();
	DRAW_FRONTEND_HELPER_TEXT("LEAVE", "INPUT_F_CANCEL", 0);
	DRAW_FRONTEND_HELPER_TEXT("CONFIRM", "INPUT_F_ACCEPT", 0);

	float title_y, title_width, title_height;

	if (GET_IS_WIDESCREEN())
	{
		title_y = 0.2120, title_width = 0.77999990, title_height = 1.2000;
	}
	else
	{
		title_y = 0.2180, title_width = 0.6000, title_height = 0.9830;
	}

	draw_title(0.5000, title_y, title_width, title_height, 253, 160, 35, 255, "ModManager 1.2");
}

void main(void)
{
	SET_PLAYER_CONTROL(GetPlayerIndex(), false);

	CLEAR_PRINTS();
	CLEAR_HELP();

	REQUEST_SCRIPT("modmanager_menu");
	while (!HAS_SCRIPT_LOADED("modmanager_menu"))
	{
		WAIT(0);
	}
	START_NEW_SCRIPT("modmanager_menu", 1024);
	MARK_SCRIPT_AS_NO_LONGER_NEEDED("modmanager_menu");

	while(true)
	{
		WAIT(0);
		DoModManager();
	}
}