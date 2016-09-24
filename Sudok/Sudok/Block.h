#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "common.h"
#include "My_colors.h"
#include "My_fonts.h"


class Block
{

public:
	Block();
	Block(float x1, float x2, float y1, float y2);
	void _Draw_cell();
	void _Draw_digit(ALLEGRO_FONT *font, bool is_correct);
	void _Draw_digits_for_input(ALLEGRO_FONT *font);
	void _Set_number(int digit);
	short _Get_number();
	void _Is_draw (int x, int y);

private:
	int coord_x1;
	int coord_x2;
	int coord_y1;
	int coord_y2;

	short number;
	bool show = false;
	bool allow_to_draw = true;
	bool draw_dig = false;

};

#endif /* _BLOCK_H_ */