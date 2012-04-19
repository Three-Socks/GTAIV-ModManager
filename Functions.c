void draw_title(float x, float y, float width, float height, uint r, uint g, uint b, uint a, char *val)
{
	SET_TEXT_FONT(6);
	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(1, 0, 0, 0, 255);
	SET_TEXT_PROPORTIONAL(1);
	SET_TEXT_WRAP(0.00000000, 1.00000000);	

	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(width, height);
	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(1);
	SET_TEXT_RIGHT_JUSTIFY(0);
	DISPLAY_TEXT_WITH_LITERAL_STRING(x, y, "STRING", val);
}

void set_up_draw(int type, float width, float height, uint r, uint g, uint b, uint a)
{

	SET_TEXT_FONT(0);

	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(0, 0, 0, 0, 255);

	if (type == 1)
	{
		SET_TEXT_BACKGROUND(1);
	}
	else if (type == 2)
	{
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 255);
	}
	else if (type == 3)
	{
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
	}

	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(width, height);
	SET_TEXT_PROPORTIONAL(1);

	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(0);
	SET_TEXT_RIGHT_JUSTIFY(0);

}

float draw_text(char *gxtName, float x, float y, char *val)
{
	float result;
	result = GET_STRING_WIDTH_WITH_STRING(gxtName, val);
	DISPLAY_TEXT_WITH_LITERAL_STRING(x, y, gxtName, val);
	return result;
}