#define BUTTON_X 0x10
#define BUTTON_O 0x11
#define BUTTON_DPAD_UP 0x8
#define BUTTON_DPAD_DOWN 0x9

typedef struct _script
{
	char* file;
	char* name;
	bool multi;
	bool enabled;
	float width;
} script;

script mod[25];

bool inMulti = false;

uint r, g, b, a, item_highlighted = 1, mod_count = 0;

float edc_width = 0, Ipos_y, start_pos_y, title_y, 
menu_pos_x = 0.2000, text_width = 0.4000, text_height = 0.4000, menu_spacing = 0.0400, space_from_title = 0.1300;