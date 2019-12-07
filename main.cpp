#define PDC_DLL_BUILD 1
#define PDC_WIDE 1
#ifdef _WIN32
//Windows includes
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#include "Trie.h"
#include "TrieNode.h"
#include "binary.h"
#include "Sorts.h"
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
#include <ctime>
#include <chrono>


using namespace std;

//Create and display main and subwindows
void displayWindows();

//take keyboard input, save to vector then display to subwindow
void keyboard_input(char text);

//Insert newline, add previous line to vector, increment row_loc and return col_loc to default value
void newline();

//Open file and save to vector
void openFile();

//Save information in vector (the screen) to a file
void saveFile();

//compares word in vector to TrieNode
void callTrie();

void printInsertSort();
void printQuickSort();
void printSelectSort();
void printBubbleSort();

//Global variables
WINDOW* main_window = nullptr;
WINDOW* sub_window;
WINDOW* autocomplete;

//int top = 0;
int row_loc = 3;
int col_loc = 2;
int vertical_size = 0;
int horizontal_size = 0;
int num_cols = 0;
int num_rows = 0;
int suggestCount;
string chosenWord;

vector<vector<char>> row_insert;
vector<char> col_insert;
vector<char> binary;

vector<char> trieCompare;
vector<string> new_match;
vector<string> saveToBinary;
vector<string> forSorting;

Trie autocompleteList;

//system time
const time_t ctt = time(0);

int main(int argc, char* argv[])
{

	displayWindows();

	string word;
	ifstream myfile;
	myfile.open("keywords.txt");

	if (myfile.good() == false)
	{
		string error = "File not found";
		mvwaddstr(sub_window, 5, 10, error.c_str());
	}

	while (getline(myfile, word))
	{
		autocompleteList.addWord(word);
	}

	myfile.close();

	char typing = ' ';

	for (int i = 0; i < num_cols - 2; i++)
	{
		row_insert.push_back(vector<char>{});

		for (int j = 0; j < num_rows - 2; j++)
		{
			row_insert[i].push_back(char{});
		}
	}

	keyboard_input(typing);

	wrefresh(sub_window);
}

void displayWindows()
{
	//WINDOW* main_window = nullptr;
	/*int num_cols = 0;
	int num_rows = 0;*/

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
	//WINDOW* sub_window;
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


	//Instructions for user
	attron(A_BOLD);
	string instruct = "  ^X - EXIT  ^N - AUTO-COMPLETE  ^S - SAVE FILE   ^O - OPEN FILE";
	string sortCommand = "^A - INSERTION SORT ^B - BUBBLE SORT ^C - QUICK SORT ^D - SELECTION SORT";
	mvwaddstr(main_window, 3, (num_cols / 2) - 45, sortCommand.c_str());
	mvwaddstr(main_window, 1, (num_cols / 2) - 40, instruct.c_str());
	attroff(A_BOLD);
}

void keyboard_input(char text)
{

	int word_wrap = num_cols - 100;

	//while typing any key but CTRL X, getch() will save value to type_input
	//then it will be added to subwin as a char based on the current location of col_loc and
	//row_loc, counter for column will then increment by one unless it's at the end of the 
	//screen, then row_loc will increment by one and col_loc will revert to default location
	while (text != 24)
	{
		int type_input = getch();

		if (type_input == 15) //CTRL O
		{
			openFile();
		}

		if (type_input == 14) // CTRL N
		{
			callTrie();
		}

		if (type_input == 1) //CTRL A, insertion sort
		{
			printInsertSort();
			forSorting.clear();
		}

		if (type_input == 2) //CTRL A, bubble sort
		{
			printBubbleSort();
			forSorting.clear();
		}

		if (type_input == 3) //CTRL C, quick sort
		{
			printQuickSort(); 
			forSorting.clear();
		}

		if (type_input == 4) //CTRL D, select sort
		{
			printSelectSort();
			forSorting.clear();
		}


		//if enter key is pressed, move to new line
		if (type_input == 10)
		{

			newline();

		}
		else if (type_input == 19) //CTRL S
		{
			saveFile();

		}
		else
		{
			string temp;
			mvwaddch(sub_window, row_loc, col_loc, type_input);
			if (text == 32) //Space bar
			{
				trieCompare.clear();
			}
			trieCompare.push_back(type_input);
					
			col_insert.push_back(type_input);
			binary.push_back(type_input);
			col_loc++;
			text = type_input;
			if (col_loc >= word_wrap)
			{

				row_insert[row_loc] = col_insert;
				col_insert.clear();
				row_loc++;
				col_loc = 1;
			}
			wrefresh(sub_window);
		}

		//user presses CTRL X to exit, subwindow clears, main window clears
		//then both windows exit
		if (text == 24) 
		{
			wclear(sub_window);
			clear();
			refresh();
			wrefresh(sub_window);

			//end curses mode, deletes both windows
			delwin(sub_window);
			endwin();
		}
	}
}

void newline()
{
	row_insert[row_loc] = col_insert;
	col_insert.clear();
	row_loc++;
	col_loc = 1;
}

void openFile()
{
	int word_wrap = num_cols - 50;

	//vector<char> myFile;
	ifstream srcfile;
	srcfile.open("test.txt");
	char input_char;

	while (!srcfile.eof())
	{
		srcfile.get(input_char);
		col_insert.push_back(input_char);

		if (input_char == '\n' || col_insert.size() >= word_wrap)
		{
			for (int i = 0; i < col_insert.size(); i++)
			{
				binary.push_back(col_insert[i]);
				mvwaddch(sub_window, row_loc, col_loc, col_insert[i]);
				col_loc++;
			}
			row_insert[row_loc] = col_insert;
			col_insert.clear();
			row_loc++;
			col_loc = 1;
		}
	}

	srcfile.close();
	wrefresh(sub_window);
}

void saveFile()
{
	row_insert[row_loc] = col_insert;
	findFrequency(binary);
	saveFrequency(binary);
	col_insert.clear();
	vector<char> testing;
	ofstream outfile;
	outfile.open("test2.txt");

	//successfully writes row_insert to file, but has issues with formatting
	for (int i = 0; i < row_insert.size(); i++)
	{
		for (int j = 0; j < row_insert[i].size(); j++)
		{
			outfile << row_insert[i][j];
		}
		outfile << endl;
	}
	outfile.close();
	string save = "File saved: ";
	string saveTime = save + asctime(localtime(&ctt));
	//attron(A_STANDOUT);
	mvwaddstr(main_window, 4, (num_cols / 2) + 40, saveTime.c_str());
	wrefresh(main_window);
	//attroff(A_STANDOUT);
}

void callTrie()
{
	//clear any previous versions of auto-complete window
	wclear(autocomplete);
	
	autocomplete = subwin(main_window, num_rows - 30, num_cols - 125, 5, 120);
	box(autocomplete, 0, 0);
	wattron(autocomplete, A_STANDOUT);
	mvwaddstr(autocomplete, 1, 15, "SUGGESTED WORDS:");
	wattroff(autocomplete, A_STANDOUT);
	int suggested_row_loc = row_loc;

	string compareWord;

	for (int i = 0; i < trieCompare.size(); i++)
	{
		compareWord += tolower(trieCompare[i]); //add word currently being typed to string to use for searching Trie
	}

	string suggestedWord;
	new_match = autocompleteList.search(compareWord);

	for (int i = 0; i < new_match.size(); i++)
	{
		suggestCount = i;
		suggestedWord = to_string(i+1) + " - " + new_match[i];
		mvwaddstr(autocomplete, suggested_row_loc, 2, suggestedWord.c_str());
		suggested_row_loc++;
	}

	if (new_match.size() <= 0)
	{
		suggestedWord = "NO MATCHES FOUND";
		mvwaddstr(autocomplete, 4, 15, suggestedWord.c_str());
	}

	wrefresh(sub_window);
	wrefresh(autocomplete);
}

void printQuickSort()
{
	string temp;
	for (int i = 0; i < col_insert.size(); i++)
	{
			temp += col_insert[i];
			if (col_insert[i] == ' ')
			{
				forSorting.push_back(temp);
				temp = "";
			}
	}

	temp += " ";

	forSorting.push_back(temp);

	Quicksort(forSorting);

	col_loc = 2;
	row_loc += 2;

	mvwaddstr(sub_window, row_loc, col_loc, "QUICK SORT:");

	row_loc++;

	for (int i = 0; i < forSorting.size(); i++)
	{
		mvwaddstr(sub_window, row_loc, col_loc, forSorting[i].c_str());
		col_loc += forSorting[i].length();
	}
}

void printSelectSort()
{
	string temp;
	for (int i = 0; i < col_insert.size(); i++)
	{
		temp += col_insert[i];
		if (col_insert[i] == ' ')
		{
			forSorting.push_back(temp);
			temp = "";
		}
	}

	temp += " ";

	forSorting.push_back(temp);

	Selectsort(forSorting);

	col_loc = 2;
	row_loc += 2;

	mvwaddstr(sub_window, row_loc, col_loc, "SELECTION SORT:");

	row_loc++;

	for (int i = 0; i < forSorting.size(); i++)
	{
		mvwaddstr(sub_window, row_loc, col_loc, forSorting[i].c_str());
		col_loc += forSorting[i].length();
	}
}

void printBubbleSort()
{
	string temp;
	for (int i = 0; i < col_insert.size(); i++)
	{
		temp += col_insert[i];
		if (col_insert[i] == ' ')
		{
			forSorting.push_back(temp);
			temp = "";
		}
	}

	temp += " ";

	forSorting.push_back(temp);

	BubbleSort(forSorting);

	col_loc = 2;
	row_loc += 2;

	mvwaddstr(sub_window, row_loc, col_loc, "BUBBLE SORT:");

	row_loc++;

	for (int i = 0; i < forSorting.size(); i++)
	{
		mvwaddstr(sub_window, row_loc, col_loc, forSorting[i].c_str());
		col_loc += forSorting[i].length();
	}
}

void printInsertSort()
{
	string temp;
	for (int i = 0; i < col_insert.size(); i++)
	{
		temp += col_insert[i];
		if (col_insert[i] == ' ')
		{
			forSorting.push_back(temp);
			temp = "";
		}
	}

	temp += " ";

	forSorting.push_back(temp);
	
	InsertionSort(forSorting);

	col_loc = 2;
	row_loc += 2;

	mvwaddstr(sub_window, row_loc, col_loc, "INSERTION SORT:");

	row_loc++;

	for (int i = 0; i < forSorting.size(); i++)
	{
		mvwaddstr(sub_window, row_loc, col_loc, forSorting[i].c_str());
		col_loc += forSorting[i].length();
	}
}