//+++helper und friend functions+++
//definition der helfer functinen und friend funktions
#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

#include "main_header.hpp"

//+++Gruesse+++
void welcome()  //output  Gruss der app
{
	cout << endl;
	cout<<  "\t0-----------------------------------------0\n";
	cout << "\t|   *** Willkommen zu Tic Tic Toe! ***    |\n";
	cout << "\t0-----------------------------------------0\n\n";
	
	/*cout << "OXO\n\tOXO is a video game developed by A S Douglas in 1952 which simulates a game of noughts and crosses (tic-tac-toe). It was one of the first games developed in the early history of video games. Douglas programmed the game as part of a thesis on human-computer interaction at the University of Cambridge.\n\nIt was written on the Electronic Delay Storage Automatic Calculator (EDSAC). EDSAC was one of the first stored-program computers, with memory that could be read from or written to, and had three small cathode ray tube screens to display the state of the memory; Douglas re-purposed one screen to demonstrate portraying other information to the user, such as the state of a noughts and crosses game. After the game served its purpose, it was discarded on the original hardware but later successfully reconstructed.\n\nOXO, along with a draughts game by Christopher Strachey completed around the same time, is one of the earliest known games to display visuals on an electronic screen. Under some definitions, it thus may qualify as the first video game, though other definitions exclude it due to its lack of moving or real-time updating graphics.";*/
}

void levelWelcome(string level)
{
	cout << "\n-------------------------------------------------------------------\n\n";
	cout << "\t\t\t Tic-Tac-Toe (" << level << ")\n"; 
	cout << "\n-------------------------------------------------------------------\n\n";
	
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


//+++fehlerausgaben Menue ++++
void printWrongNumErr(int x) 
{
	cout << "\nBitte Zahl zwischen 1 und "<< x <<" eingeben (\"0\" um Spiel zu verlassen):\n\n";
}


//+++Abschiede+++
void farewell()  //abschied des programms als solches
{
	cout << "\nBis zum nächsten mal!\n" << endl;
}


//+++helper functions+++
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
	cout << '\n' << "Drücke bitte die \"Enter\" Taste..." << endl;
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

//+++tic tac toe functions+++
// Funktion um den status des Spielbordes zu zeigen
void showBoard(char board[][SIDE]) 
{ 
	
	printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);  
} 

// Funktion fuer Beschreiben wo gesezt werden kann
void showInstructions() 
{ 
	printf("\nWaehle ein Feld von 1 bis 9 wie unten angezeigt fuer deinen Zug:\n\n"); 
	
	printf("\t\t\t 1 | 2 | 3 \n"); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t 4 | 5 | 6 \n"); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t 7 | 8 | 9 \n\n"); 
} 

//funktionen fuer input und fhlerausgabe bei input des spiels
void wrongInputErr()
{
	cout << "Ungueltige Eingabe\n";
	cout << "Bitte 'j' wenn du beginnen moechtest, 'n' wenn der PC beginnen soll.\n\toder gib 'q' ein wenn du das Spiel verlassen willst\n";
}

void getInput()
{
	cout<< "Moechtest du den ersten Zug?(j/n):\n\toder gib 'q' ein wenn du das Spiel verlassen willst\n";
}

void versusWrongInputErr()
{
	cout << "Ungueltige Eingabe\n";
	cout << "Bitte '1' fuer Spieler 1 (X), '2' fuer Spieler 2 (O).\n\t oder '0' um das Spiel zu verlassen\n";
}

void versusGetInput()
{
	cout<< "Wer beginnt?\n1- Spieler 1 (X)\n2- Spieler 2 (O)\n0- Spiel verlassen\n";
}


//+++Friend functions+++
// Bord wird leer initialisiert
void initialise(char board[][SIDE]) 
{	
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
			board[i][j] = ' '; 
	} 
} 


//Funktion die den gewinner ausgibt
void declareWinner(int whoseTurn) 
{ 
	if (whoseTurn == COMPUTER) 
		cout << "PC hat gewonnen!\n"; 
	else
		cout << "Spieler hat gewonnen!\n"; 
} 

//Funktion fuer gewinner im Versus modus
void declareWinnerVersus(int whoseTurn) 
{ 
	if (whoseTurn == PLAYER1) 
		cout << "Spieler 1 (X) hat gewonnen!\n"; 
	else
		cout << "Spieler 2 (O) hat gewonnen!\n"; 
} 




//funktion die true zurueckgibt wenn eine Zeile komplett ist mit dem zug des spielers (oder pc)
bool rowCrossed(char board[][SIDE]) 
{ 
	for (int i = 0; i < SIDE; i++) 
	{ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') 
			return (true); 
	} 
	return(false); 
} 

//funktion die true zurueckgibt wenn eine Spalte komplett ist mit dem zug des spielers (oder pc)
bool columnCrossed(char board[][SIDE]) 
{ 
	for (int i = 0; i < SIDE; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') 
			return (true); 
	} 
	return(false); 
} 

//funktion die true zurueckgibt wenn eine Diagonale komplett ist mit dem zug des spielers (oder pc)
bool diagonalCrossed(char board[][SIDE]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != ' ') 
		return(true); 
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] != ' ') 
		return(true); 

	return(false); 
} 


//funktion gibt true zurueck  wenn das spiel zuende ist, ansonsten false
bool gameOver(char board[][SIDE]) 
{ 
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board)); 
}




#endif