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

	menu_header = modmanager_header;
	custom_bool_on = modmanager_enabled;
	custom_bool_off = modmanager_disabled;

	modmanager_script_config();

	modmanager_toggle_width();
}

void project_catchFunctionButtonPress(void)
{
}