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

void project_doAction(void)
{
	menu_items_set = true;

	// Helpers
	uint num_val_selected = menu_item[item_selected].num_val;
	uint mainMenu = last_selected[1];
	uint subMenu = last_selected[2]; 

	if (!script_loaded)
		load_script = modmanager_script[item_selected];
	else
		modmanager_apply();

	return;

	project_error(MODMANAGER_ERROR_ID_INVALID);
}

void load_script_prioritized(void)
{
	if (DOES_SCRIPT_EXIST(load_script))
	{
		if (!script_requested)
		{
				REQUEST_SCRIPT(load_script);
				script_requested = true;
		}

		if (HAS_SCRIPT_LOADED(load_script))
		{
			load_script = null_string;
			script_loaded = true;
			script_requested = false;
			project_doAction();
		}
	}
	else
	{
		load_script = null_string;
		project_error(MODMANAGER_ERROR_ID_SCRIPT);
	}
}