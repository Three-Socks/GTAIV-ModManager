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

// Error ID's
enum eModManagerErrorID
{
	MODMANAGER_ERROR_ID_UNKNOWN,
	MODMANAGER_ERROR_ID_INVALID,
	MODMANAGER_ERROR_ID_SCRIPT
};

char* load_script;
bool script_loaded, script_requested;

char* modmanager_script[MAX_MENU_ITEMS];