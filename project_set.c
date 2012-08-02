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

#pragma once

void project_set(void)
{
	menu_items_set = true;

	// Shortcuts
	uint mainMenu = last_selected[1];
	uint subMenu = last_selected[2]; 

	menu_header = modmanager_header;
	custom_bool_on = modmanager_enabled;
	custom_bool_off = modmanager_disabled;

	// Main
	if (menu_level == 1)
	{
		modmanager_addScript("Three-Socks Trainer", "3s_trainer_startup");
		menu_addItem("Developer Tools");

		return;
	}
	else if (menu_level == 2)
	{
		if (item_selected == 2)
		{
			modmanager_addScript("XYZH Coords", "xyzh_coords_example");
			modmanager_addScript("Disable Pause Menu", "disable_pause");
			return;
		}
	}

	project_error(MODMANAGER_ERROR_ID_INVALID);
}

void project_catchFunctionButtonPress(void)
{
}