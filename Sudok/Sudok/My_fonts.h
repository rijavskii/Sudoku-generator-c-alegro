#ifndef _MY_FONT_H_
#define _MY_FONT_H_

#include "common.h"

enum eMyFonts
{
	 e_menu
	,e_menu_bold
	,e_table_digit
	,e_small_digits
};

ALLEGRO_FONT getFont(eMyFonts eFont);

#endif /* _MY_COLOR_H_ */