//+++hier werden die funktionen der Medium.hpp klasse definiert+++

//hpp der Klasse wird included
#include "../include/Medium.hpp"

/*
fuer erklaerung siehe Hard.cpp
das spiel wurde erst auf dem hard level entwickelt (mit KI) und wurde fuer de anderen levels "duemmer" gemacht
durch das einfuegen von zufallsgeneratoren fuer die errechnung der moeglichkeiten und auch der Zuege

!!!Aenderungen sind unten nochmal kommentiert
*/
//evaluations funktion
int Medium::minimax(char board[][SIDE], int depth, bool isAI)
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
				for(int i=0; i<SIDE; i++)
				{
					for(int j=0; j<SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE;
							score = minimax(board, depth + 1, false);
							board[i][j] = ' ';
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
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
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

//bester zug wird errechnet (aber dümmer gestellt)
int Medium::bestMove(char board[][SIDE], int moveIndex)
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
					bestScore = rand() % 2 == 0 ? score : bestScore+3; //medium dumm, die haelfte der zuege ist random
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

//speilfunction
void Medium::playTicTacToe(int whoseTurn) 
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
			n = bestMove(board, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			board[x][y] = COMPUTERMOVE; 
			printf("PC hat ein %c in Feld %d gesetzt\n\n", COMPUTERMOVE, n+1);
			showBoard(board);
			moveIndex ++; 
			whoseTurn = HUMAN;
		} 
		
		else if (whoseTurn == HUMAN) 
		{
			cout << "Du kannst folgende Positionen besetzen : ";
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
				board[x][y] = HUMANMOVE; 
				printf ("\nSpieler hat ein %c in Feld %d gesetzt\n\n", HUMANMOVE, n+1); 
				showBoard(board); 
				moveIndex ++; 
				whoseTurn = COMPUTER;
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
 
	if (gameOver(board) == false && moveIndex == SIDE * SIDE) 
		cout << "Das Spiel war unentschieden!\n"; 
	else
	{ 
		if (whoseTurn == COMPUTER) 
			whoseTurn = HUMAN; 
		else if (whoseTurn == HUMAN) 
			whoseTurn = COMPUTER; 
		
		declareWinner(whoseTurn); 
	} 
} 