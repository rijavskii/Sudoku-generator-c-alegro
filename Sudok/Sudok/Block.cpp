
//#include <allegro5\allegro.h>
#include "Block.h"

/*
ALLEGRO_COLOR black = al_map_rgb(0, 0, 0),
background = al_map_rgb(194, 200, 218),
cell_background = al_map_rgb(190, 190, 220),
cell_background_dark = al_map_rgb(140, 140, 200),
incorrect_digit = al_map_rgb(200, 0, 0);
*/
Block::Block(float x1, float x2, float y1, float y2)
{
	coord_x1 = x1;
	coord_x2 = x2;
	coord_y1 = y1;
	coord_y2 = y2;
}

Block::Block()
{

}

void Block::_Set_number(int digit)
{
	if (digit)
	{
		show = true;
		allow_to_draw = false;
	}
	else
	{
		show = false;
		allow_to_draw = true;
	}
	number = digit;
}

short Block::_Get_number()
{
	return number;
}

void Block::_Draw_cell()
{
	

	if (!show)
	{
		al_draw_filled_rectangle(coord_x1, coord_y1, coord_x2, coord_y2, getColor(ecell_background));
	}
	else
	{
		al_draw_filled_rectangle(coord_x1, coord_y1, coord_x2, coord_y2, getColor(ecell_background_dark));
	}

	al_draw_rectangle(coord_x1, coord_y1, coord_x2, coord_y2, getColor(eblack), 1);

	//al_flip_display();

}

void Block::_Draw_digit(ALLEGRO_FONT *font, bool is_correct)
{
	
	// *font = al_load_font("AlfredoHeavy.ttf", 32, 0);
	if (number)
	{
		if (is_correct)
			al_draw_textf(font, getColor(eblack), coord_x1 + 30, coord_y1 + 15, ALLEGRO_ALIGN_CENTER, "%i", number);
		else
			al_draw_textf(font, getColor(eincorrect_digit), coord_x1 + 30, coord_y1 + 15, ALLEGRO_ALIGN_CENTER, "%i", number);
	}
	//al_flip_display();
}

void Block::_Draw_digits_for_input(ALLEGRO_FONT *font)
{
	int tmpcord_x = coord_x1+10;
	int tmpcord_y = coord_y1+2;
	
	if (!draw_dig)
	{
		for (int i = 1; i <= 9; i++)
		{
			al_draw_textf(font, getColor(eblack), tmpcord_x, tmpcord_y, ALLEGRO_ALIGN_CENTER, "%i ", i);
			tmpcord_x += 20;
			if ((i % 3) == 0)
			{
				tmpcord_x = coord_x1 + 10;
				tmpcord_y += 20;
			}
		}
	}
}

void Block::_Is_draw(int x, int y)
{
	if (x > coord_x1 && x<coord_x2 && y>coord_y1 && y < coord_y2)
	{

	}
}

