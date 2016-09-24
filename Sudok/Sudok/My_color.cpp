#include "My_colors.h"


ALLEGRO_COLOR getColor(eMyColor aColor)
{
	switch (aColor)
	{
		case eblack:
			return al_map_rgb(0, 0, 0);
		case ebackground:
			return al_map_rgb(194, 200, 218);
		case e_hover:
			return al_map_rgb(100, 90, 100);
		case ecell_background:
			return al_map_rgb(190, 190, 220);
		case ecell_background_dark:
			return al_map_rgb(140, 140, 200);
		case eincorrect_digit:
			return al_map_rgb(200, 0, 0);
	}

	return al_map_rgb(0, 0, 0);
}
