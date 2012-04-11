/**
 * GTAIV ModManager V1.1
 *
 * This file is from: https://bitbucket.org/ThreeSocks/gtaiv-modmanager/
 *
 * By Three-Socks
 *
 * Important: Make sure you replace the natives.h with your compiler includes. The one inside the /inc folder. It contains a bug fix that is needed for modmanager to compile correctly.
 *
 */

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>

#include "Functions.c"

#define BUTTON_X  0x10
#define BUTTON_O  0x11
#define BUTTON_DPAD_UP  0x8
#define BUTTON_DPAD_DOWN  0x9

typedef struct _script
{
	char *file;
	char *name;
	int enabled;
	float width;
} script;

script mod[50];

int item_highlighted = 1;
int mod_count = 0; 
float edc_width = 0;
float Ipos_y, start_pos_y, title_y, title_width, title_height;
uint title_r = 253, title_g = 160, title_b = 35;

float pos_x = 0.2000, width = 0.4000, height = 0.4000;
uint r, g, b, a;

void Init(void)
{

	// Script config
	// Add you scripts to these two arrays (file, name) and then change the mod_count.

	// The file name of the script
	mod[1].file = "garage";
	mod[2].file = "xyzh_coords_example";
	mod[3].file = "button_input_example";
	mod[4].file = "open_garages_example";
	mod[5].file = "vehicle_example";
	mod[6].file = "disable_airportpol";
	mod[7].file = "skylift_pickup";
	mod[8].file = "teleport_example";
	mod[9].file = "teleport_scrapyard";
	mod[10].file = "";

	// The name to display
	mod[1].name = "Garage Mod Shop";
	mod[2].name = "XYZH Coords Example";
	mod[3].name = "Button Input Example";
	mod[4].name = "Open Garages Example";
	mod[5].name = "Vehicle Example";
	mod[6].name = "Disable Police Patrol at Airport";
	mod[7].name = "Skylift Pick Up";
	mod[8].name = "Teleport to Brucies Garage";
	mod[9].name = "Teleport to Northwood Scrap Yard";
	mod[10].name = "";

	// How many scirpts there are.
	mod_count = 9;
	
	// End script config
	// No more editing needed below this point if all your doing is adding scripts...

	int I;
	for (I = 1; I < (mod_count + 1); I++)
	{
		if ((GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(mod[I].file)) >= 1)
		{
			mod[I].enabled = 2;
		}
	}

	CLEAR_PRINTS();
	CLEAR_HELP();

	if (GET_IS_WIDESCREEN())
	{
		title_y = 0.2120;
		title_width = 0.77999990;
		title_height = 1.2000;
	}
	else
	{
		title_y = 0.2180;
		title_width = 0.6000;
		title_height = 0.9830;
	}

	start_pos_y = title_y + 0.1300;
}

void DrawMenu(void)
{
	Ipos_y = start_pos_y;

	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_DPAD_DOWN))
	{	

		if (item_highlighted == mod_count)
		{
			item_highlighted = 1;
			start_pos_y = title_y + 0.1300;
		}
		else
		{
			item_highlighted++;
		}
		
		if (item_highlighted >= 13)
		{
			start_pos_y -= 0.0400;
		}

	}

	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_DPAD_UP))
	{
	
		if (item_highlighted == 1)
		{
			item_highlighted = mod_count;

			if (mod_count >= 13)
			{
				start_pos_y = (title_y + 0.1300) - ((mod_count - 12) * 0.0400);
			}
		}
		else
		{
			item_highlighted--;
		}

		if (item_highlighted >= 13)
		{
			start_pos_y += 0.0400;
		}

	}

	int I;
	for (I = 1; I < (mod_count + 1); I++)
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
		Ipos_y = Ipos_y + 0.0400;

		if (Ipos_y < title_y + 0.1300)
		{
			a = 0;
		}

		if (item_highlighted == I)
		{
			r = 253;
			g = 160;
			b = 35;
		}

		set_up_draw(0, width, height, r, g, b, a);
		float strwidth = draw_text("STRING", pos_x, Ipos_y, mod[I].name);

		if (edc_width == 0)
		{
			mod[I].width = strwidth;
			
			if (I == mod_count)
			{
				int edc_I; float edc_max = 0;
				for (edc_I = 1; edc_I < (mod_count + 1); edc_I++)
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
			if (mod[I].enabled == 2)
			{
				set_up_draw(0, width, height, 253, 160, 35, a);
				draw_text("STRING", pos_x + edc_width + 0.0900, Ipos_y, "Enabled");
			}
			else
			{
				set_up_draw(0, width, height, 255, 255, 255, a);
				draw_text("STRING", pos_x + edc_width + 0.0900, Ipos_y, "Disabled");
			}
		}

	}
}

void DoMenu(void)
{
	if (!IS_FONT_LOADED(6))
	{
		LOAD_TEXT_FONT(6);
	}
	PAUSE_GAME();
	HIDE_HUD_AND_RADAR_THIS_FRAME();
	DRAW_RECT(0.5000, 0.5000, 1.0000, 1.0000, 0, 0, 0, 255);
	INIT_FRONTEND_HELPER_TEXT();
	DRAW_FRONTEND_HELPER_TEXT("LEAVE", "INPUT_F_CANCEL", 0);
	DRAW_FRONTEND_HELPER_TEXT("CONFIRM", "INPUT_F_ACCEPT", 0);

	DrawMenu();
	draw_title(0.5000, title_y, title_width, title_height, title_r, title_g, title_b, 255, "ModManager 1.1");

	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_X))
	{
		if (mod[item_highlighted].enabled == 2)
		{
			mod[item_highlighted].enabled = 0;
			TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(mod[item_highlighted].file);
		}
		else if (DOES_SCRIPT_EXIST(mod[item_highlighted].file))
		{
			REQUEST_SCRIPT(mod[item_highlighted].file);
			while (!HAS_SCRIPT_LOADED(mod[item_highlighted].file))
			{
				REQUEST_SCRIPT(mod[item_highlighted].file);
				WAIT(0);
			}
			START_NEW_SCRIPT(mod[item_highlighted].file, 1024);
			MARK_SCRIPT_AS_NO_LONGER_NEEDED(mod[item_highlighted].file);
			
			int I;
			for (I = 1; I < (mod_count + 1); I++)
			{
				if ((GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(mod[I].file)) >= 1)
				{
					mod[I].enabled = 2;
				}
			}
		}
		else
		{
			PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", "Unable to load script.", 3500, 1);
		}
	}

	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_O))
	{
		UNPAUSE_GAME();
		SET_PLAYER_CONTROL(GetPlayerIndex(), true);
		TERMINATE_THIS_SCRIPT();
	}
}

void main(void)
{
	SET_PLAYER_CONTROL(GetPlayerIndex(), false);
	Init();

	while(true)
	{
		WAIT(0);
		if (IS_SCREEN_FADED_OUT())
		{
			UNPAUSE_GAME();
			SET_PLAYER_CONTROL(GetPlayerIndex(), true);
			TERMINATE_THIS_SCRIPT();
		}
		DoMenu();
	}
}