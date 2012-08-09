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

void modmanager_script_config(void)
{
	// Shortcuts
	uint mainMenu = last_selected[1];
	uint subMenu = last_selected[2];

	// Main
	if (menu_level == 1)
	{
		modmanager_addScript("Three-Socks Trainer 1.0 FINAL", "3s_trainer_startup");
		menu_addItem("Developer Tools");

		return;
	}
	else if (menu_level == 2)
	{
		if (item_selected == 2)
		{
			modmanager_addScript("Ribonucleic's Particle Effects Manager", "particlemanager");
			modmanager_addScript("XYZH Coords", "xyzh_coords_example");
			modmanager_addScript("Disable Pause Menu", "disable_pause");
			return;
		}
	}
	
	project_error(MODMANAGER_ERROR_ID_INVALID);
}