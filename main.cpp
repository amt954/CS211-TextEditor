#define PDC_DLL_BUILD 1
#define PDC_WIDE 1
#ifdef _WIN32
//Windows includes
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#else
//Linux / MacOS includes
#include <curses.h>
#endif
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <iterator>


using namespace std;


//int top = 0;

int main(int argc, char* argv[])
{

	cout << "Argument output: " << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
	}

	WINDOW* main_window = nullptr;
	int num_cols = 0;
	int num_rows = 0;

	//SETUP

	//initialize our screen
	main_window = initscr();

	//resize our window
	resize_term(5000, 5000);
	getmaxyx(main_window, num_rows, num_cols);
	resize_term(num_rows - 1, num_cols - 1);
	getmaxyx(main_window, num_rows, num_cols);
	attron(A_DIM);
	wborder(main_window, 0, 0, 0, 0, 0, 0, 0, 0);
	attroff(A_DIM);

	//create text field
	WINDOW* sub_window;
	sub_window = subwin(main_window, num_rows - 2, num_cols - 2, 1, 1);


	//Use to verify location of sub_window
	//box(sub_window, 0, 0);

	//turn off keyboard echo
	noecho();

	//allow scrolling
	scrollok(sub_window, TRUE);

	//turn on keypad input
	keypad(main_window, true);

	//hide the cursor
	curs_set(FALSE);
	wmove(sub_window, 0, 0);
	wrefresh(sub_window);

	//MAIN PROGRAM LOGIC GOES HERE

	//add file menu header to screen
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color(); /* Start color */
	init_pair(1, COLOR_WHITE, COLOR_BLACK); //sets the color of text and background

	wattron(main_window, COLOR_PAIR(1));
	wattron(main_window, A_UNDERLINE);
	mvaddstr(0, 2, "File");
	mvaddstr(0, 8, "Edit");
	mvaddstr(0, 14, "Options");
	mvaddstr(0, 23, "Tools");
	mvaddstr(0, 30, "About");
	wattroff(main_window, A_UNDERLINE);
	wattroff(main_window, COLOR_PAIR(1));

	//refresh tells curses to draw everything
	refresh();
	touchwin(stdscr);

	//END OF PROGRAM LOGIC GOES HERE

	//Pause for user input
	attron(A_STANDOUT);
	mvwaddstr(main_window, 2, (num_cols / 2) - 25, "INPUT ASTERICK * TO EXIT");
	attroff(A_STANDOUT);

	char typing = ' ';
	int row_loc = 3;
	int col_loc = 1;
	int vertical_size = 0;
	int horizontal_size = 0;

	vector<vector<char>> row_insert;
	vector<char> col_insert;

	for (int i = 0; i < num_cols - 2; i++)
	{
		row_insert.push_back(vector<char>{});

		for (int j = 0; j < num_rows - 2; j++)
		{
			row_insert[i].push_back(char{});
		}
	}

	int word_wrap = num_cols - 50;

	//while typing any key but asterick, getch() will save value to type_input
	//then it will be added to subwin as a char based on the current location of col_loc and
	//row_loc, counter for column will then increment by one unless it's at the end of the 
	//screen, then row_loc will increment by one and col_loc will revert to default location
	while (typing != '*')
	{
		int type_input = getch();

		if (type_input == 27)
		{
			//vector<char> myFile;
			ifstream srcfile;
			srcfile.open("Test.txt");
			char input_char;

			while (!srcfile.eof())
			{

				srcfile.get(input_char);
				col_insert.push_back(input_char);

				if (input_char == '\n')
				{
					row_insert[row_loc] = col_insert;
					col_insert.clear();
					row_loc++;
					col_loc = 1;
				}

				if (col_insert.size() >= word_wrap)
				{
					row_insert[row_loc] = col_insert;
					col_insert.clear();
					row_loc++;
					col_loc = 1;
				}
			}
			/*for (int i = 0; i < row_insert.size(); i++)
			{
				for (int j = 0; j < row_insert[i].size(); j++)
				{
					waddch(sub_window, row_insert[i][j]);
					//mvwaddch(sub_window, row_loc, col_loc, row_insert[i][j]);
				}
			}*/

			srcfile.close();
			wrefresh(sub_window);
		}

		//if enter key is pressed, move to new line
		if (type_input == 10)
		{
			row_insert[row_loc] = col_insert;
			col_insert.clear();
			row_loc++;
			col_loc = 1;

			//SCROLLING
			/*if (row_insert.size() > num_rows - 20)
			{
				REQ_SCR_FLINE;
			}*/
			
		}
		else
		{
			mvwaddch(sub_window, row_loc, col_loc, type_input);
			col_insert.push_back(type_input);
			col_loc++;
			typing = type_input;
			//row_insert[col_loc][row_loc] = col_insert;
			wrefresh(sub_window);
		}
		if (col_loc >= word_wrap)
		{
			row_insert[row_loc] = col_insert;
			col_insert.clear();
			row_loc++;
			col_loc = 1;
		}
		if (type_input == '`')
		{
			row_insert[row_loc] = col_insert;
			col_insert.clear();
			ofstream outfile;
			outfile.open("test2.txt");

			//successfully writes row_insert to file, but has issues with formatting
			for (int i = 0; i < row_insert.size(); i++)
			{
				for (int j = 0; j < row_insert[i].size(); j++)
				{
					outfile << row_insert[i][j];
				}
			}
			outfile.close();
		}

		//user presses asterick to exit, subwindow clears, main window clears
		//then both windows exit
		if (typing == '*')
		{
			wclear(sub_window);
			clear();
			refresh();
			wrefresh(sub_window);

			//end curses mode, deletes both windows
			delwin(sub_window);
			endwin();
		}

		wrefresh(sub_window);

	}
}
