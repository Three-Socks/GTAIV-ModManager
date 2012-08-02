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

void modmanager_addScript(char* item_text, char* item_script)
{
	menu_addItem(item_text);
	modmanager_script[menu_len] = item_script;

	bool enabled;
	if (GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(item_script) == 1)
		enabled = true;

	menu_addItemBool(enabled);
	menu_addAction();
}

void modmanager_apply(void)
{
	if (menu_item[item_selected].extra_val)
	{
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(modmanager_script[item_selected]);
		menu_item[item_selected].extra_val = false;
	}
	else
	{
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(modmanager_script[item_selected]);

		START_NEW_SCRIPT(modmanager_script[item_selected], 1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED(modmanager_script[item_selected]);
		script_loaded = false;

		menu_item[item_selected].extra_val = true;
	}
}