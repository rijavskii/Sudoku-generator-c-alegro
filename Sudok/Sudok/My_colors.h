#ifndef _MY_COLOR_H_
#define _MY_COLOR_H_

#include "common.h"

enum eMyColor
{
	eblack
	,ebackground
	,ecell_background
	,ecell_background_dark
	,eincorrect_digit
	,e_hover
};

ALLEGRO_COLOR getColor(eMyColor aColor);

#endif /* _MY_COLOR_H_ */