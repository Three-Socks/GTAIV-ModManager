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

void project_error(uint error_id)
{
	if (menu_item[item_selected].action)
		actionError = true;

	menu_clean();

	// Invalid Menu.
	menu_header = modmanager_error;

	if (error_id == MODMANAGER_ERROR_ID_INVALID)
		menu_addItem(modmanager_error_invalid);
	else if (error_id == MODMANAGER_ERROR_ID_SCRIPT)
		menu_addItem(modmanager_error_script);

	menu_addItem(modmanager_error_goback);
	inError = true;

	PLAY_AUDIO_EVENT("FRONTEND_MENU_ERROR");
}