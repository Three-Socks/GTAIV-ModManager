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

#include "locals.h"
#include "functions.c"

void MainLevel_Init(void)
{
	// Script config
	// Add you scripts to these two arrays (file, name) and then change the mod_count.

	// The name to display
	mod[1].name = "Garage Mod Shop";
	mod[2].name = "Disable Police Patrol at Airport";
	mod[3].name = "Skylift Pick Up";
	mod[4].name = "Developer Tools";
	mod[5].name = "Example Mods";

	// The file name of the script. Use mod[#].multi to define another level.
	mod[1].multi = true;
	mod[2].file = "disable_airportpol";
	mod[3].file = "skylift_pickup";
	mod[4].multi = true;
	mod[5].multi = true;

	// How many scirpts there are.
	mod_count = 5;
	
}

// Script config continued...
// Multi Level script config.
void MultiLevel_Init(void)
{
	if (item_highlighted == 1)
	{
		// The name to display
		mod[1].name = "Garage Mod Shop 2.0";
		mod[2].name = "Garage Anywhere (R1+UP)";
		mod[3].name = "Teleport to Brucies Garage";
		mod[4].name = "Teleport to Northwood Scrap Yard";

		// The file name of the script
		mod[1].file = "garage";
		mod[2].file = "garage_anywhere";
		mod[3].file = "teleport_example";
		mod[4].file = "teleport_scrapyard";
		
		mod_count = 4;
	}
	else if (item_highlighted == 4)
	{
		mod[1].name = "XYZH Coords Example";

		mod[1].file = "xyzh_coords_example";

		mod_count = 1;
	}
	else if (item_highlighted == 5)
	{
		mod[1].name = "Button Input Example";
		mod[2].name = "Open Garages Example";
		mod[3].name = "Vehicle Example";

		mod[1].file = "button_input_example";
		mod[2].file = "open_garages_example";		
		mod[3].file = "vehicle_example";

		mod_count = 3;
	}
	
	// End script config
	// No more editing needed below this point if all your doing is adding scripts...
}

void find_script_enabled(void)
{
	int I;
	for (I = 1; I <= mod_count; I++)
	{
		if (!mod[I].multi)
		{
			if (GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(mod[I].file) >= 1)
			{
				mod[I].enabled = true;
			}
			else
			{
				mod[I].enabled = false;
			}
		}
	}
}

void DrawMenu(void)
{
	Ipos_y = start_pos_y;

	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_DPAD_DOWN))
	{
		if (item_highlighted == mod_count)
		{
			item_highlighted = 1;
			start_pos_y = title_y + space_from_title;
		}
		else
		{
			item_highlighted++;
		}

		if (item_highlighted >= 13)
		{
			start_pos_y -= menu_spacing;
		}
	}

	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_DPAD_UP))
	{
		if (item_highlighted == 1)
		{
			item_highlighted = mod_count;

			if (mod_count >= 13)
			{
				start_pos_y = (title_y + space_from_title) - ((mod_count - 12) * menu_spacing);
			}
		}
		else
		{
			item_highlighted--;
		}

		if (item_highlighted >= 13)
		{
			start_pos_y += menu_spacing;
		}
	}

	int I;
	for (I = 1; I <= mod_count; I++)
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
		Ipos_y = Ipos_y + menu_spacing;

		if (Ipos_y < title_y + space_from_title)
		{
			a = 0;
		}

		if (item_highlighted == I)
		{
			r = 253;
			g = 160;
			b = 35;
		}

		set_up_draw(0, text_width, text_height, r, g, b, a);
		float strtext_width = draw_text("STRING", menu_pos_x, Ipos_y, mod[I].name);

		if (edc_width == 0)
		{
			mod[I].width = strtext_width;
			
			if (I == mod_count)
			{
				int edc_I; float edc_max = 0;
				for (edc_I = 1; edc_I <= mod_count; edc_I++)
				{
					if (mod[edc_I].width > edc_max)
					{
						edc_max = mod[edc_I].width;
					}
				}
				edc_width = edc_max;
			}
		}
		else
		{
			if (!mod[I].multi)
			{
				if (mod[I].enabled)
				{
					set_up_draw(0, text_width, text_height, 253, 160, 35, a);
					draw_text("STRING", menu_pos_x + edc_width + 0.0900, Ipos_y, "Enabled");
				}
				else
				{
					set_up_draw(0, text_width, text_height, 255, 255, 255, a);
					draw_text("STRING", menu_pos_x + edc_width + 0.0900, Ipos_y, "Disabled");
				}
			}
		}
			
	}
}

void DoMenu(void)
{
	DrawMenu();

	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_X))
	{
		if (!inMulti && mod[item_highlighted].multi)
		{
			inMulti = true;

			// Reset multi.
			int I;
			for (I = 1; I <= mod_count; I++)
			{
				mod[I].multi = false;
			}

			MultiLevel_Init();

			find_script_enabled();

			edc_width = 0;
			start_pos_y = title_y + space_from_title;
			item_highlighted = 1;
		}
		else
		{
			if (mod[item_highlighted].enabled)
			{
				mod[item_highlighted].enabled = false;
				TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(mod[item_highlighted].file);
			}
			else if (DOES_SCRIPT_EXIST(mod[item_highlighted].file))
			{
				REQUEST_SCRIPT(mod[item_highlighted].file);
				while (!HAS_SCRIPT_LOADED(mod[item_highlighted].file))
				{
					WAIT(0);
				}
				START_NEW_SCRIPT(mod[item_highlighted].file, 1024);
				MARK_SCRIPT_AS_NO_LONGER_NEEDED(mod[item_highlighted].file);

				find_script_enabled();
			}
			else
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", "Unable to load script.", 3500, 1);
			}
		}
	}

	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_O))
	{
		if (inMulti)
		{
			inMulti = false;

			// Reset multi.
			int I;
			for (I = 1; I <= mod_count; I++)
			{
				mod[I].multi = false;
			}

			MainLevel_Init();
			
			find_script_enabled();

			edc_width = 0;
			start_pos_y = title_y + space_from_title;
			item_highlighted = 1;
		}
		else
		{
			UNPAUSE_GAME();
			SET_PLAYER_CONTROL(GetPlayerIndex(), true);
			TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("modmanager");
			TERMINATE_THIS_SCRIPT();
		}
	}
}

void main(void)
{
	MainLevel_Init();

	find_script_enabled();

	if (GET_IS_WIDESCREEN())
	{
		title_y = 0.2120;
	}
	else
	{
		title_y = 0.2180;
	}

	start_pos_y = title_y + space_from_title;

	while(true)
	{
		WAIT(0);
		if (IS_SCREEN_FADED_OUT())
		{
			UNPAUSE_GAME();
			SET_PLAYER_CONTROL(GetPlayerIndex(), true);
			TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("modmanager");
			TERMINATE_THIS_SCRIPT();
		}
		DoMenu();
	}
}