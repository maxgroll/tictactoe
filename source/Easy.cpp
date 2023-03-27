//+++hier werden die funktionen der Easy.hpp klasse definiert+++

//hpp der Klasse wird included
#include "../include/Easy.hpp"


/*
fuer erklaerung siehe Hard.cpp
das spiel wurde erst auf dem hard level entwickelt (mit KI) und wurde fuer de anderen levels "duemmer" gemacht
durch das einfuegen von zufallsgeneratoren fuer die errechnung der moeglichkeiten und auch der Zuege

!!!Aenderungen sind unten nochmal kommentiert
*/
int Easy::minimax(char board[][SIDE], int depth, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (gameOver(board) == true)
	{
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else
	{
		if(depth < 9)
		{
			if(isAI == true)
			{
				bestScore = -999;
				for(int i = 0; i < SIDE; i++)
				{
					for(int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE;
							score = minimax(board, depth + 1, false);
							board[i][j] = ' ';
							
							if(score > bestScore)
							{
								//in diesem fall wird der bestscore randomized fuer das easy level
								bestScore = rand() % 2 == 0 ? score : bestScore; //easy dumm gemacht durch random
							}
						}
					}
				}
				return bestScore; //bester score, in diesem fall nicht so bester wird zurueckgegeben
			}
			else
			{
				bestScore = 999;
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = HUMANMOVE;
							score = minimax(board, depth + 1, true);
							board[i][j] = ' ';
							if (score < bestScore)
							{
								bestScore = rand() % 2 == 0 ? score : bestScore+1; //easy dumm gemacht durch random
							}
						}
					}
				}
				return bestScore; //rueckgabe von (eigentlich) bestmoeglichem score
			}
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

//Function die den bestmoeglichen Zug errechnet basieren auf dem minimax ergebnis
//in diesem fall fuer Easy level wird auch dieser durch random dumm gemacht
int Easy::bestMove(char board[][SIDE], int moveIndex)
{
	srand(time(0));
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;
				score = minimax(board, moveIndex+1, false);
				board[i][j] = ' ';
				if(score > bestScore)
				{
					bestScore = rand() % 3 == 0 ? score : bestScore+2; //easy dumm gemacht durch random
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

// Function die das Speil ausfuehrt
void Easy::playTicTacToe(int whoseTurn) 
{ 
	char board[SIDE][SIDE]; 
	int moveIndex = 0, x = 0, y = 0;
	initialise(board);
	showInstructions(); 
	
	while (gameOver(board) == false && moveIndex != SIDE*SIDE) 
	{ 
		int n;
		if (whoseTurn == COMPUTER) 
		{
			//bester zug wird errechnet
			n = bestMove(board, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			board[x][y] = COMPUTERMOVE; //zug wird gesetzt
			printf("PC hat ein %c in Feld %d gesetzt\n\n", COMPUTERMOVE, n+1); //und ausgegeben
			showBoard(board); //das brett wird gezeigt in seinen jetzigen zustand
			moveIndex ++; // index wird erhoet
			whoseTurn = HUMAN; //zug weitergegen an Spieler
		} 
		//Zug von Spieler
		else if (whoseTurn == HUMAN) 
		{
			cout << "Du kannst folgende Positionen besetzen : ";
			//freie felder werden als zahlen ausgegeben
			for(int i = 0; i < SIDE; i++)
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
				board[x][y] = HUMANMOVE;  //zug wird gesetzt
				printf ("\nSpieler hat ein %c in Feld %d gesetzt\n\n", HUMANMOVE, n+1); //ausgegeben
				showBoard(board); //zustand des bretts
				moveIndex ++; //index erhoet
				whoseTurn = COMPUTER; //zug weitergegeben an PC
			}
			//sollte das feld nicht frei sein
			else if(board[x][y] != ' ' && n<9 && n>=0)
			{
				cout << "\nDieses Feld ist besetzt, bitte wahle eine anderes Feld:\n\n";
				clearBuffer();
			}
			//oder eine ungueltige zahl eingegeben werden
			else if(n<0 || n>8)
			{
				cout << "Das ist kein gueltiges Feld\n";
				clearBuffer();
			}
		} 
	} 

	// Wenn das spiel unentschieden
	if (gameOver(board) == false && moveIndex == SIDE * SIDE) 
		cout << "Das Spiel war unentschieden!\n"; 
	else //wenn nicht
	{ 
		// wird der spieler(pc) gewchselt solange das brett noch freie felder hat
		if (whoseTurn == COMPUTER) 
			whoseTurn = HUMAN; 
		else if (whoseTurn == HUMAN) 
			whoseTurn = COMPUTER; 
		
		declareWinner(whoseTurn); //funktion die den Gewinner ausrechnet und ausgibt wird aufgerufen 
	} 
} 