#include "My_fonts.h"

ALLEGRO_FONT  getFont(eMyFonts font)
{
	switch (font)
	{
	case e_menu:
		return *al_load_font ("algerian.ttf", 32, 0);
	case e_menu_bold:
		return *al_load_font("algerian.ttf", 30, 0);
	case e_table_digit:
		return *al_load_font ("AlfredoHeavy.ttf", 32, 0);
	case e_small_digits:
		return *al_load_font ("AlfredoHeavy.ttf", 16, 0);

	}
	
}