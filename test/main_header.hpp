//+++main header+++
//header guard
#ifndef MAIN_HEADER_HPP
#define MAIN_HEADER_HPP

#include <iostream>  
#include <iomanip> 
#include <string>
#include <vector>
#include <regex>
#include <limits>
#include <cstdlib>
#include <fstream> 
#include <iterator>
#include <cmath> 
#include <ctime> 
#include <cctype>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <list>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::streamsize;
using std::numeric_limits;
using std::regex;
using std::ifstream;
using std::cerr;
using std::stringstream;
using std::fstream;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::streamsize;
using std::istream;
using std::istream_iterator;
using std::vector;
using std::setfill;
using std::setw;


//macro um CLEAR sowohl in windows wie in Mac nutzen zu koennen
#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


//+++forward deklaration von Klassen+++
class Board;
class Player;

//+++constants+++

static const int nk = 100;

// declaring the possible states
static enum {START, PLAYING, QUIT, OWIN, XWIN, DRAW} state;

//constanter wert fuer die anzahl der columns



//+++deklaration von friend functions werden in helper_functions.hpp definiert+++
void clearBuffer();
string ucFirst(string input);
void keyWait();

//deklarationen der hilfsfunktionen fuer die menues
void welcome();

void printProgMenu(); //output des Menus fuer das programm
void printWrongNumErr(int x); //output fehlermeldung menue-eingabe des hauptmenues

void menuFarewell(string name);
void farewell();  //abschied des programms als solches


//+++login werden direkt in login cpp definiert+++
bool checkLogin(string username, string password);
string getUser(string &user);
string getPassword(string &password);


//void update_screen();
//void reset_state();

#endif