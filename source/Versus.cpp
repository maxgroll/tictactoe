//+++hier werden die funktionen der Versus.hpp klasse definiert+++

//hpp der Klasse wird included
#include "../include/Versus.hpp"


/*
hier wird nur die Spielfunktion gebraucht daher wird diese klasse angepasst
minimax evaluationsfunction und zugausrechnung werden hier nicht benoetigt da zwei spieler

!!!Aenderungen sind unten nochmal kommentiert
*/
//!!nur speilfunction
void Versus::playTicTacToe(int whoseTurn) 
{ 
	char board[SIDE][SIDE]; //brett
	int moveIndex = 0, x = 0, y = 0; //zugindex | x achse index | y achse index
	initialise(board); //bord wird initialisiert (siehe helper_functions.hpp)
	showInstructions(); //beschreibung wird ausgegeben (siehe helper_functions.hpp)
	
	// gespielt wird bis unentschieden oder gewonnen
	while (gameOver(board) == false && moveIndex != SIDE*SIDE) 
	{ 
		int n; //zum speichern des zuges
		if (whoseTurn == PLAYER1) //spieler eins ist dran
		{
			cout << "Spieler 1 (X):\nDu kannst folgende Positionen besetzen : ";
			for(int i=0; i<SIDE; i++)
				for (int j = 0; j < SIDE; j++)
					if (board[i][j] == ' ')
			printf("%d ", (i * 3 + j) + 1);
			cout << "\n\nBitte gebe eine Position ein = ";
			cin >> n; //position(feld) speichern
			n--; //minus 1 da index
			x = n / SIDE; //errechen der x position
			y = n % SIDE; //errechnen der y position
			system(CLEAR);
			if(board[x][y] == ' ' && n<9 && n>=0) //wenn feld frei und gueltig
			{
				board[x][y] = PLAYER1MOVE; //zug setzen
				printf ("\nSpieler 1 hat ein %c in Feld %d gesetzt\n\n", PLAYER1MOVE, n+1); //ausgeben
				showBoard(board); //upgedatetes board zeigen (siehe helper_functions.hpp)
				moveIndex ++; //index des zuges wird erhoet
				whoseTurn = PLAYER2; //zug an Spieler zwei weitergegeben
			}
			else if(board[x][y] != ' ' && n<9 && n>=0) //falls feld besetzt
			{
				cout << "\nDieses Feld ist besetzt, bitte wahle eine anderes Feld:\n\n";
			}
			else if(n<0 || n>8) // oder nicht gueltig
			{
				cout << "Das ist kein gueltiges Feld\n";
			}
		} 
		
		else if (whoseTurn == PLAYER2) //spielr 2 ist dran (funktionert genau wie speiler 1)
		{
			cout << "Spieler 2 (O):\nDu kannst folgende Positionen besetzen : ";
			for(int i=0; i<SIDE; i++)
				for (int j = 0; j < SIDE; j++)
					if (board[i][j] == ' ')
			printf("%d ", (i * 3 + j) + 1);
			cout << "\n\nBitte gebe eine Position ein = ";
			cin >> n;
			n--;
			x = n / SIDE;
			y = n % SIDE; 
			system(CLEAR);
			if(board[x][y] == ' ' && n<9 && n>=0)
			{
				board[x][y] = PLAYER2MOVE; 
				printf ("\nSpieler 2 hat ein %c in Feld %d gesetzt\n\n", PLAYER2MOVE, n+1); 
				showBoard(board); 
				moveIndex ++; 
				whoseTurn = PLAYER1;
			}
			else if(board[x][y] != ' ' && n<9 && n>=0)
			{
				cout << "\nDieses Feld ist besetzt, bitte wahle eine anderes Feld:\n\n";
				clearBuffer();
			}
			else if(n<0 || n>8)
			{
				cout << "Das ist kein gueltiges Feld\n";
				clearBuffer();
			}
		} 
	} 

	// sollte es unentschieden
	if (gameOver(board) == false && moveIndex == SIDE * SIDE) 
		cout << "Das Spiel war unentschieden!\n"; 
	else //sonst
	{ 
		// spieler wechseln
		if (whoseTurn == PLAYER1) 
			whoseTurn = PLAYER2; 
		else if (whoseTurn == PLAYER2) 
			whoseTurn = PLAYER1; 
		
		declareWinnerVersus(whoseTurn); //gewinner ausgeben (siehe helper_functions.hpp)
	} 
} 