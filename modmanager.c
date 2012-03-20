/**
 * GTAIV ModManager V1
 *
 * This file is from: https://bitbucket.org/ThreeSocks/gtaiv-modmanager/
 *
 * By Three-Socks
 *
 * Important: Make sure you replace the natives.h with your compiler includes. The one inside the /inc folder. It contains a fix that is needed for modmanager to compile correctly.
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

script mod[21];

int item_highlighted = 1;
int mod_count = 0; 
float edc_width = 0;
float Ipos_y, title_y, title_width, title_height;
uint title_r = 253, title_g = 160, title_b = 35;

float pos_x = 0.16500000, width = 0.40000000, height = 0.40000000;
uint r, g, b, a = 255;

void Init(void)
{

	// Script config
	// Add you scripts to these three arrays (file, name, enabled (always = 0)) and then increment the mod_count if needed.

	// The file name of the script
	mod[1].file = "brucie_garage";
	mod[2].file = "xyzh_coords_example";
	mod[3].file = "button_input_example";
	mod[4].file = "teleport_example";
	mod[5].file = "";

	// The name to display
	mod[1].name = "Brucies Garage Shop Mod";
	mod[2].name = "XYZH Coords Example";
	mod[3].name = "Button Input Example";
	mod[4].name = "Teleport to Brucie's Garage";
	mod[5].name = "";

	// How many scirpts there are.
	mod_count = 4;
	
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
		title_y = 0.21200000;
		title_width = 0.77999990;
		title_height = 1.20000000;
	}
	else
	{
		title_y = 0.21800000;
		title_width = 0.60000000;
		title_height = 0.98300000;
	}
}

void DrawMenu(void)
{
	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_DPAD_DOWN))
	{
		if (item_highlighted == mod_count)
		{
			item_highlighted = 1;
		}
		else
		{
			item_highlighted++;
		}
	}

	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_DPAD_UP))
	{
		if (item_highlighted == 1)
		{
			item_highlighted = mod_count;
		}
		else
		{
			item_highlighted--;
		}
	}

	int I;
	Ipos_y = title_y + 0.13000000;
	for (I = 1; I < (mod_count + 1); I++)
	{
		r = 255;
		g = 255;
		b = 255;
		Ipos_y = Ipos_y + 0.04000000;

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
				draw_text("STRING", pos_x + edc_width + 0.09000000, Ipos_y, "Enabled");
			}
			else
			{
				set_up_draw(0, width, height, 255, 255, 255, a);
				draw_text("STRING", pos_x + edc_width + 0.09000000, Ipos_y, "Disabled");
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
	DRAW_RECT(0.00000000, 0.00000000, 2.00000000, 2.00000000, 0, 0, 0, 255);
	INIT_FRONTEND_HELPER_TEXT();
	DRAW_FRONTEND_HELPER_TEXT("LEAVE", "INPUT_F_CANCEL", 0);
	DRAW_FRONTEND_HELPER_TEXT("CONFIRM", "INPUT_F_ACCEPT", 0);

	draw_title(0.50000000, title_y, title_width, title_height, title_r, title_g, title_b, 255, "SCO ModManager");
	DrawMenu();
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
			UNPAUSE_GAME();
			SET_PLAYER_CONTROL(GetPlayerIndex(), true);
			TERMINATE_THIS_SCRIPT();
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
		DoMenu();
	}
}