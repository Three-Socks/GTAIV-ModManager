void modmanager_script_config(void)
{
	// Shortcuts
	uint mainMenu = last_selected[1];
	uint subMenu = last_selected[2];

	// Main
	if (menu_level == 1)
	{
		modmanager_addScript("Three-Socks Trainer 1.0 BETA3", "3s_trainer_startup");
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