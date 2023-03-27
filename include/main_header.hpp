//+++main header+++
//header guard
#ifndef MAIN_HEADER_HPP
#define MAIN_HEADER_HPP

#include <iostream>  
#include <iomanip> 
#include <string>
#include <limits>
#include <cstdlib>
#include <fstream> 
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
using std::ifstream;
using std::cerr;


//macro um CLEARSCREEN sowohl in windows wie in Mac nutzen zu koennen
#ifdef _WIN32 //windows
#define CLEAR "cls"
#else //andere OS
#define CLEAR "clear"
#endif


//+++forward deklaration von Klassen+++
class iLevel;
class Game;
class Easy;
class Medium;
class Hard;
class Versus;

//+++constants+++
//pc wird als 1 definiert
//Spieler als 2
#define COMPUTER 1 
#define HUMAN 2 

#define SIDE 3 // Lange des Spielbords x oder y achse

// Pc benutzt Symbol "0"
// Spieler Symbol "X" 
#define COMPUTERMOVE 'O' 
#define HUMANMOVE 'X' 


//spieler 1 und 2 werden definiert fuer Versus modus
#define PLAYER1 1 
#define PLAYER2 2 
//Spieler 1 hat 'X' und spieler 2 hat 'O'
#define PLAYER1MOVE 'X' 
#define PLAYER2MOVE 'O' 



//helper functions, werden in helper_functions.hpp definiert
void clearBuffer();
string ucFirst(string input);
void keyWait();

//deklarationen der hilfsfunktionen fuer die menues
void welcome();
//willkommen im level des spiels
void levelWelcome(string level);

void printProgMenu(); //output des Menus fuer das programm
void printWrongNumErr(int x); //output fehlermeldung menue-eingabe des hauptmenues

//void menuFarewell(string name);
void farewell();  //abschied des programms 


//+++login werden direkt in login cpp definiert+++
bool checkLogin(string username, string password);
string getUser(string &user);
string getPassword(string &password);

//Helferfunktionen fuer das spielfeld
void showBoard(char board[][SIDE]);
void showInstructions();

void wrongInputErr();
void getInput();

void versusWrongInputErr();
void versusGetInput();


#endif