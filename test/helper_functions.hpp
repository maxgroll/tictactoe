//+++helper und friend functions+++
//definition der helfer functinen und friend funktions die nun nicht mehr in eine extra header datei ausgelagert werden muessen
#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

#include "main_header.hpp"

//+++Gruesse+++
void welcome()  //output  Gruss der app
{
	cout << endl;
	cout<<  "\t0-----------------------------------------0\n";
	cout << "\t|   *** Willkommen zu Tic Tic Toe! ***    |\n";
	cout << "\t0-----------------------------------------0\n";
}

void welcome(string name)  //output  Gruss menues
{
	name = name;
	cout << endl;
	cout << "\t   *** " << name << " ***  \n";
}

//+++Menues+++
void printProgMenu() //output des Menus fuer das programm
{
	cout << "\nHauptmenue!\n\n";
	cout << "Bitte Auswahl (Zahl) eingeben: (Oder '0' um die App zu verlassen)\n" << endl;
	cout << "1.- Easy (leichtes Level)" << endl;
	cout << "2.- Medium (mittleres Level)" << endl;
	cout << "3.- Hard (hartes Level)" << endl;
	cout << "4.- Versus (spiele gegen einen Freund)" << endl;
	cout << "0.- Exit\n" << endl;
}


//+++fehlerausgaben Menues++++
void printWrongNumErr(int x) //output fehlermeldung menue-eingabe des hauptmenues
{
	cout << "\nBitte Zahl zwischen 1 und "<< x <<" eingeben (\"0\" um die App zu verlassen):\n\n";
}


//+++Abschiede+++
void farewell()  //abschied des programms als solches
{
	cout << "\nBis zum nächsten mal!\n" << endl;
}

void menuFarewell(string name)  //abschied der menues, nimmt namen als parameter
{
	cout << "\nSie verlassen jetzt das " << name << " Menue!" << endl;
}


//+++friend functions+++
void clearBuffer()
{
		cin.clear(); //buffer leeren
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void keyWait()
{
	cin.clear(); //inputstream wird geloescht
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); //input stream wird ignoriert
	do 
	{
	cout << '\n' << "Drücken Sie die \"Enter\" Taste..." << endl;
	} while (cin.get() != '\n'); // es wird auf "enter" gewartet
	system(CLEAR);
}

string ucFirst(string input) 
{
	for (int i = 0; i < input.length(); i++)
	{
		if (i == 0)
		{
			input[i] = toupper(input[i]);
		}
		else if (input[i - 1] == ' ')
		{
			input[i] = toupper(input[i]);
		}
		else
		{
			input[i] = tolower(input[i]);
		}
	}
	return input;
}




void update_screen()
{
	cin.get();
	system(CLEAR);
	std::cin.clear();
	std::cin.sync();
	//select_game_type();
}

// resets the state of the game
void reset_state() 
{
	state = PLAYING;
}


// checks for the end of the game
bool game_over() 
{
	return (state == XWIN || state == OWIN || state == DRAW);
}

void showBoard()
{
	std::cout << std::endl;
	std::cout << " 1 | 2 | 3" << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << " 4 | 5 | 6" << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << " 7 | 8 | 9" << std::endl;
	std::cout << std::endl;
}



#endif