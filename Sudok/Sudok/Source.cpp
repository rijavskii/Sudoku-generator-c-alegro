// Sudoku.cpp: определяет точку входа для консольного приложения.

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <iostream>

#include "common.h"
#include "Block.h"
#include "My_colors.h"
#include "My_fonts.h"

using namespace std;

ALLEGRO_DISPLAY *display = NULL;
bool draw = true;
const float FPS = 5.0;
int Width = 840,
Height = 600;

short tmpfield[9][9];

enum eDifficulty
{
	 EASY=1
	,MEDIUM
	,HARD
};

struct sToChange
{
	short val1;
	short val2;
};

struct CURSOR_POSITION
{
	int x;
	int y;
} sudok_cursor;

struct sWindow
{
	int x;
	int y;
}window_position;

//Block *block_examp;

sToChange ChooseLinesToChange();
void SwapRaws(int raw1 = 0, int raw2 = 0);
void SwapColumns(int, int);
void TranspondMatrix();
void ChangeHorAreas();
void ChangeVertAreas();
void GenerateField(const short field[9][9]);
void GenerateTask(eDifficulty );
void Init_allegro();
void Init_cells(Block field[9][9]);
void Draw_background(Block field[9][9]);
void Fill_cells(Block field[9][9]);
void Draw_digits(ALLEGRO_FONT *font, Block field[9][9]);
void Save_to_txt();

int main()
{
	srand(time(NULL));
	const short baseTable[9][9] = { 5, 7, 6, 1, 3, 2, 8, 4, 9,
									9, 3, 4, 5, 8, 7, 1, 2, 6,
									8, 2, 1, 4, 9, 6, 7, 5, 3,
									7, 9, 5, 6, 2, 1, 4, 3, 8,
									3, 4, 2, 8, 5, 9, 6, 7, 1,
									1, 6, 8, 3, 7, 4, 5, 9, 2,
									6, 5, 9, 2, 4, 8, 3, 1, 7,
									2, 1, 3, 7, 6, 5, 9, 8, 4,
									4, 8, 7, 9, 1, 3, 2, 6, 5 };

	//copy table to tmp_table
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tmpfield[i][j]= baseTable[i][j];
		}
	};

	Block SudokuCells[9][9];
	
	Init_allegro();
	Init_cells(SudokuCells);
	
	ALLEGRO_TIMER *timer = al_create_timer(1 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_FONT menu = getFont(e_menu);
	ALLEGRO_FONT digits = getFont(e_table_digit);
	ALLEGRO_FONT menu_bold = getFont(e_menu_bold);
	ALLEGRO_FONT smal_digits = getFont(e_small_digits);
	ALLEGRO_BITMAP *save = al_load_bitmap("save.png");
	ALLEGRO_BITMAP *save1 = al_load_bitmap("save1.png");

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//*ALLEGRO_EVENT event;
	//al_wait_for_event(event_queue, &event);*/
	//al_flip_display();
	
	

	

	al_start_timer(timer);
	al_init_image_addon();
	al_install_mouse();
	
	ALLEGRO_BITMAP *tmp = al_create_bitmap(600, 600);

	bool newGame = false;
	bool toShow = true;
	bool difficult = false;
	bool to_save = false;
	int disp_height = al_get_display_height(display);
	int disp_weight = al_get_display_width (display);
	int pixel = al_get_pixel_block_height(800);
	//al_get_mouse_cursor_position(&sudok_cursor.x, &sudok_cursor.y);
	while (draw)
	{
		al_get_mouse_cursor_position(&sudok_cursor.x, &sudok_cursor.y);
		al_get_window_position(display, &window_position.x, &window_position.y);
		//al_get_mo
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		//event.keyboard.keycode = NULL;
		//al_draw_bitmap(save,770,30,NULL);
		al_draw_textf(&menu, al_map_rgb(0, 0, 0), 610, 100, ALLEGRO_ALIGN_LEFT, "W: %d", pixel);
		al_draw_textf(&menu, al_map_rgb(0, 0, 0), 610, 140, ALLEGRO_ALIGN_LEFT, "H: %i", disp_height);


		/*if (event.type == ALLEGRO_EVENT_TIMER) {
			draw = true;
		}
		else */
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			
			int value = al_show_native_message_box(display, "EXIT", "", "Are you really want to exit?", NULL, ALLEGRO_MESSAGEBOX_YES_NO);

			if (value)
				draw = false;
		}
		//f2 new game ---hard
		if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			if ((event.keyboard.keycode == ALLEGRO_KEY_F2))
			{
				
				GenerateField(baseTable);
				GenerateTask(HARD);
				Fill_cells(SudokuCells);
				newGame = true;
				
			}
			else if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				int value = al_show_native_message_box(display, "EXIT", "", "Are you really want to exit?", NULL, ALLEGRO_MESSAGEBOX_YES_NO);

				if (value)
				draw = false;
			}
		}
		//draw menu----------------------------------------------------
		
			if (difficult)
			{
				//easy difficult button
				if ((sudok_cursor.x > (window_position.x + 615)) && (sudok_cursor.x < ((window_position.x + 615) + al_get_text_width(&menu, "EASY"))) &&
					(sudok_cursor.y > ((window_position.y + 428) - al_get_font_line_height(&menu))) && (sudok_cursor.y < (window_position.y + 418)))
				{
					if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
						if (event.mouse.button & 1)
						{
							difficult = false;
							GenerateField(baseTable);
							GenerateTask(EASY);
							Fill_cells(SudokuCells);
							newGame = true;
							to_save = true;
						}
					al_draw_textf(&menu_bold, getColor(e_hover), 610, 360, ALLEGRO_ALIGN_LEFT, "EASY");
				}
				else
					al_draw_textf(&menu, getColor(eblack), 610, 360, ALLEGRO_ALIGN_LEFT, "EASY");
				
				//medium difficult button
				if ((sudok_cursor.x > (window_position.x + 615)) && (sudok_cursor.x < ((window_position.x + 615) + al_get_text_width(&menu, "MEDIUM"))) &&
					(sudok_cursor.y > ((window_position.y + 477) - al_get_font_line_height(&menu))) && (sudok_cursor.y < (window_position.y + 457)))
				{
					if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
						if (event.mouse.button & 1)
						{
							difficult = false;
							GenerateField(baseTable);
							GenerateTask(MEDIUM);
							Fill_cells(SudokuCells);
							newGame = true;
							to_save = true;
						}
					al_draw_textf(&menu_bold, getColor(e_hover), 610, 400, ALLEGRO_ALIGN_LEFT, "MEDIUM");
				}
				else
					al_draw_textf(&menu, getColor(eblack), 610, 400, ALLEGRO_ALIGN_LEFT, "MEDIUM");
				//hard difficult button
				if ((sudok_cursor.x > (window_position.x + 615)) && (sudok_cursor.x < ((window_position.x + 615) + al_get_text_width(&menu, "HARD"))) &&
					(sudok_cursor.y > ((window_position.y + 515) - al_get_font_line_height(&menu))) && (sudok_cursor.y < (window_position.y + 498)))
				{
					if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
						if (event.mouse.button & 1)
						{
							difficult = false;
							GenerateField(baseTable);
							GenerateTask(HARD);
							Fill_cells(SudokuCells);
							newGame = true;
							to_save = true;
						}
					al_draw_textf(&menu_bold, getColor(e_hover), 610, 440, ALLEGRO_ALIGN_LEFT, "HARD");
				}
				else
					al_draw_textf(&menu, getColor(eblack), 610, 440, ALLEGRO_ALIGN_LEFT, "HARD");
				//back button
				if ((sudok_cursor.x > (window_position.x + 615)) && (sudok_cursor.x < ((window_position.x + 615) + al_get_text_width(&menu, "BACK"))) &&
					(sudok_cursor.y > ((window_position.y + 607) - al_get_font_line_height(&menu))) && (sudok_cursor.y < (window_position.y + 588)))
				{
					if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
						if (event.mouse.button & 1)
						{
							difficult = false;
						}
					al_draw_text(&menu_bold, getColor(e_hover), 610, 530, ALLEGRO_ALIGN_LEFT, "BACK");
				} else 
					al_draw_text(&menu, getColor(eblack), 610, 530, ALLEGRO_ALIGN_LEFT, "BACK");
			}
			else {
				if ((sudok_cursor.x > (window_position.x+618)) && (sudok_cursor.x < ((window_position.x + 618) + al_get_text_width(&menu, "NEW GAME"))) &&
					(sudok_cursor.y > ((window_position.y + 472) - al_get_font_line_height(&menu))) && (sudok_cursor.y < (window_position.y + 458)))
				{
					if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
					if (event.mouse.button & 1) difficult = true;
					al_draw_textf(&menu_bold, getColor(e_hover), 610, 400, ALLEGRO_ALIGN_LEFT, "NEW GAME");
				}
				else
					al_draw_textf(&menu, al_map_rgb(0, 0, 0), 610, 400, ALLEGRO_ALIGN_LEFT, "NEW GAME");


				if ((sudok_cursor.x >(window_position.x + 615)) && (sudok_cursor.x < ((window_position.x + 615) + al_get_text_width(&menu, "EXIT"))) &&
					(sudok_cursor.y >((window_position.y + 607) - al_get_font_line_height(&menu))) && (sudok_cursor.y < (window_position.y + 588)))
				{
					if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
						if (event.mouse.button & 1 )
						{
							
							int value = al_show_native_message_box(display, "EXIT", "", "Are you really want to exit?", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
							
							if(value) break;
						}
					al_draw_text(&menu_bold, getColor(e_hover), 610, 530, ALLEGRO_ALIGN_LEFT, "EXIT");
				}
				else
					al_draw_text(&menu, getColor(eblack), 610, 530, ALLEGRO_ALIGN_LEFT, "EXIT");
			}
			//DrawCells(SudokuCells);
			
			//save sudoku
			if ((sudok_cursor.x > (window_position.x + 778)) && (sudok_cursor.x < (window_position.x + 802)) &&
				(sudok_cursor.y > (window_position.y + 60)) && (sudok_cursor.y < (window_position.y + 84)))
			{
				if ((event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP))
					if ((event.mouse.button & 1) && to_save)
					{
						Save_to_txt();
						al_show_native_message_box(display, "SAVE", "", "Your game was successfuly saved!", NULL, NULL);
					}
					else 
						al_show_native_message_box(display, "Save", "", "Field is empty", NULL, NULL);
				//al_draw_bitmap(save1, 770, 30, NULL);
				//al_draw_bitmap(save, 770, 30, NULL);
			}
			else
			{
				//al_draw_bitmap(save, 770, 30, NULL);
			}
			Draw_background(SudokuCells);
			//int _ = 10;
		/*/____________________________________
			
					/*for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							SudokuCells[i][j]._Draw_digits_for_input(&smal_digits);
						}
					};

		//--------------------------------, sudok_cursor.x-window_position.x-7, sudok_cursor.y-window_position.y-29
			//al_get_window_position(display, &sudok_cursor.x, &sudok_cursor.y);*/
			al_draw_textf(&menu, getColor(eblack), 610, 10, ALLEGRO_ALIGN_LEFT, "X: %i", sudok_cursor.x);
			al_draw_textf(&menu, getColor(eblack), 610, 30, ALLEGRO_ALIGN_LEFT, "y: %i", sudok_cursor.y);
			al_draw_textf(&menu, getColor(eblack), 610, 50, ALLEGRO_ALIGN_LEFT, "x: %i", window_position.x);
			al_draw_textf(&menu, getColor(eblack), 610, 70, ALLEGRO_ALIGN_LEFT, "y: %i", window_position.y);//*/
		
		if(newGame)
			Draw_digits(&digits, SudokuCells);
		if(toShow)
			
		//------------------
			
		//SudokuCells[5][4]._Draw_digits_for_input(&smal_digits);
		
		al_flip_display();
		al_clear_to_color(getColor(ebackground));
	}
	al_rest(1);
	al_destroy_display(display);

	getchar();
	return 0;
}


sToChange ChooseLinesToChange()
{
	int raw1, raw2;
	while (true)
	{
		raw1 = rand() % 9;
		raw2 = rand() % 9;
		if ((raw1 / 3 == raw2 / 3)&&(raw1 != raw2))
		{

			sToChange rand;
			rand.val1 = raw1;
			rand.val2 = raw2;

			return rand;
		}
	}
}

void SwapRaws(int raw1, int raw2)
{
	int j = 0;
	int k = 0;

	for (int i = 0; i < 9; i ++)
	{
		int tmp;
		//change rows
		tmp = tmpfield[raw1][i];
		tmpfield[raw1][i] = tmpfield[raw2][i];
		tmpfield[raw2][i]= tmp;
	}
}

void SwapColumns(int col1, int col2)
{
	for (int i = 0; i < 9; i++)
	{
		int tmp;
		
		//change columns
		tmp = tmpfield[i][col1];
		tmpfield[i][col1] = tmpfield[i][col2];
		tmpfield[i][col2] = tmp;
	}
}

void TranspondMatrix()
{
	int tmp_matrix[9][9] = { 0 };

	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			tmp_matrix[i][j] = tmpfield[j][i];
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tmpfield[i][j] = tmp_matrix[i][j];
		}
	};

}

void ChangeHorAreas()
{
	int area1 = rand() % 3;
	int area2 = rand() % 3;

	area1 *= 3;
	area2 *= 3;

	if (area1 != area2)
	{
		for (int i=0;i<3;i++)
		{
				SwapRaws(area1+i,area2+i);
		}
	}
}

void ChangeVertAreas()
{
	int area1 = rand() % 3;
	int area2 = rand() % 3;

	area1 *= 3;
	area2 *= 3;

	if (area1 != area2)
	{
		for (int i = 0;i<3;i++)
		{
			SwapColumns(area1 + i, area2 + i);
		}
	}
}

void GenerateField(const short field[9][9])
{
	short genField = (rand() % 50) + 30;
	short sortMethod;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tmpfield[i][j] = field[i][j];

		}
	};
	sToChange tmp;
	for (int i = 0;i <= genField;i++)
	{
		sortMethod = rand()%5;
		switch (sortMethod)
		{
		case 0:
			TranspondMatrix();
			break;
		case 1:
			tmp = ChooseLinesToChange();
			SwapRaws(tmp.val1, tmp.val2);
			break;
		case 2:
			tmp = ChooseLinesToChange();
			SwapRaws(tmp.val1, tmp.val2);
			break;
		case 3:
			ChangeHorAreas();
			break;
		case 4:
			ChangeVertAreas();
			break;
		}
	}
}

void GenerateTask(eDifficulty difficult)
{
	short cellsToHide;
	switch (difficult)
	{
	case EASY:

		cellsToHide = (rand() % 6) + 20;
		break;

	case MEDIUM:
		cellsToHide = (rand() % 6) + 25;
		break;
	
	case HARD:
		cellsToHide = (rand() % 6) + 30;
		break;
	}
	
	short raw;
	short column;
	for (int i = 0; i < cellsToHide;)
	{
		raw = rand() % 9;
		column = rand() % 9;
		
		if (!(tmpfield[raw][column])) continue;

		//newSudoku[raw][column].show = false;
		tmpfield[raw][column] = 0;

		i++;
	}
}

void Init_allegro()
{
	
	if (!al_init()) {
		fprintf(stderr, "Couldn't initialize allegro!\n");
		exit (-1);
	}
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "Couldn't initialize primitives addon!\n");
		exit (-1);
	}

	//al_init_font_addon(); // initialize the font addon
	//al_init_ttf_addon();  // initialize the ttf (True Type Font) addon // initialize the ttf (True Type Font) addon

	display = al_create_display(Width, Height);
	al_set_window_title(display, "Sudoku game");
	al_set_window_position(display, 0, 0);
	
	if (!display) {
		fprintf(stderr, "Couldn't create allegro display!\n");
		exit (-1);
	}

	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();  // initialize the ttf (True Type Font) addon // initialize the ttf (True Type Font) addon
	al_init_image_addon();

}

void Init_cells(Block field[9][9])
{
	float cord_x1 = 40,
		  cord_y1 = 30,
		  cord_x2 = 100,
		  cord_y2 = 90;

	for (int i = 0; i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			Block tmp(cord_x1, cord_x2, cord_y1, cord_y2);

			field[i][j] = tmp;
			cord_x1 = cord_x2;
			cord_x2 += 60;
		}
		cord_x1 = 40;
		cord_x2 = 100;
		cord_y1 = cord_y2;
		cord_y2 += 60;
	}
}

void Fill_cells(Block field[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			field[i][j]._Set_number(tmpfield[i][j]);
		}
	};
}

void Draw_background(Block field[9][9])
{
	//al_clear_to_color(getColor(ebackground));
	//al_draw_filled_rectangle(40, 30, 580, 570, getColor(ecell_background));
	for (int i = 0; i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			field[i][j]._Draw_cell();
		}
	}
	al_draw_rectangle(38, 28, 582, 572, getColor(eblack), 4);
	
	al_draw_line(218, 28, 218, 572, getColor(eblack),4);
	al_draw_line(398, 28, 398, 572, getColor(eblack), 4);

	al_draw_line(38, 208, 582, 208, getColor(eblack), 4);
	al_draw_line(38, 388, 582, 388, getColor(eblack), 4);
	//al_flip_display();
}

void Draw_digits(ALLEGRO_FONT *font, Block field[9][9])
{
	for (int i = 0; i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			field[i][j]._Draw_digit(font, true);
		}
	}
}

void Save_to_txt()
{
	/*time_t rawtime;
	struct tm * timeinfo;
	char buffer[30];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int year = timeinfo->tm_year;
	int month = timeinfo->tm_mon;
	int day = timeinfo->tm_mday;
	int hours = timeinfo->tm_hour;
	int minutes = timeinfo->tm_min;
	int sec = timeinfo->tm_sec;*/
	//snprintf(buffer, 30, "Saves/%i-%i-%i %i:%i:%i.txt", 1900+year, ++month, day, hours, minutes, sec);
	//strftime(buffer, 25, "%d-%m-%Y-%H:%M", timeinfo);
	
	//string str(buffer);
	char folder[30] = {"Saves/"};
	char name[8];
	_itoa_s(rand()%10000000,name,10);
	strcat_s(folder, name);
	strcat_s(folder, ".txt");
	string str = (folder);
	ofstream myFile;
	myFile.open(str);

	if (!myFile)
	{
		al_show_native_message_box(display, "SAVE", "", "Cannot create file", NULL, NULL);
	}
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j == 8)
				myFile << tmpfield[i][j] << endl;
			else
				myFile << tmpfield[i][j] << " ";
		}
		
	}
	myFile.close();


}