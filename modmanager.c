/**
 * This file is from ModManager https://bitbucket.org/ThreeSocks/gtaiv-modmanager
 *
 * ModManager
 *
 * @package menu
 * @author Three-Socks http://psx-scene.com/forums/members/three-socks/
 * @license LICENSE.txt DON'T BE A DICK PUBLIC LICENSE (DBAD)
 *
 * @version 1.3
 */

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>

//#define PC
#define MAX_MENU_ITEMS 52
#define MAX_MENU_LEVLS 5
#define STYLE 2

// Menu
#include "menu/menu.h"

// ModManager
#include "modmanager_lang.h"
#include "modmanager_locals.h"

#include "modmanager_functions.c"

// Project
#include "project_error.c"
#include "project_set.c"
#include "project_action.c"

// Menu
#include "menu/menu_core.c"

void main(void)
{
	menu_core_startup();
	draw_startup();

	while(true)
	{
		WAIT(0);

		if (!IS_STRING_NULL(load_script) && !script_loaded)
			load_script_prioritized();

		// Core menu function (Catch button press. Set menu).
		if (IS_STRING_NULL(load_script))
			menu_core();

		// Draw background/header/text.
		drawCurvedWindow();

		// Draw button input.
		drawFrontend();
	
		drawHeader();
		menu_draw();
	}
}