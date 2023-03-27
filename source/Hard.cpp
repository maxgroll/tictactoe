//+++hier werden die funktionen der Hard.hpp klasse definiert+++

//hpp klasse wird included
#include "../include/Hard.hpp"

/*dieses war die erste Datei in meinen programm, die Levels Medium und Easy wurden aus deser Datei angepasst und
sozusagen dümmer gemacht durch zufallsgeneration beim errechnen des besmoeglichen Resultats und  Zuges
bei Tic Tac Toe sollte, wenn der algoritmus minimax richtig angewendet ist, bei einem perfekten Spiel sollte nur ein 
unentschieden moeglich sein 
TODO programm weiterhin durchtesten ob dieses der fall ist, es muesste eigentlich unbesiegbar sein.
TODO "Alpha-Beta pruning" verstehen und richtig anwenden damit das programm effizienter wird
*/


/* Diese funktion basiert auf dem minimax algoritmus
sie errechnet das bestmoegliche resultat des spieles anhand der parameter (brett, tiefe und bool abfrage ob Ai ob ai am zug)
https://www.neverstopbuilding.com/blog/minimax
https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/
*/
//minimax ist die evaluations function hier wir recursiv jedes moegliche spielszenario aufgerufen und das bestmoegliche resultat errechnet
int Hard::minimax(char board[][SIDE], int depth, bool isAI)
{
	//variablen score und bestScore um den besten score zu errechnen
	int score = 0;
	int bestScore = 0;
	//checkt als erstes wenn wie das Speil bei jetzigem zustand ausgehen kann, alle moeglichkeiten 
	//errechnet recursiv bei jedem Zug das besmoegliche Resultat
	if (gameOver(board) == true) //brett wird gescheckt mit gameOver in helper_functions ob 3 gleiche symbole in einer reihe sind
	{
		//wenn pc wird negativer wert zurückgegeben also werte fuer minimizer (siehe unten) 
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1; //wenn nichr pc wird positiver wert maximizer (siehe unten)
	}
	else //ansonsten (wenn das spiel noch nicht fertig)
	{
		//sollte die Tiefe (die anzahl der insgesamt moeglichen zuege), die bei jedem zug erhoet wird kleiner als 9 sein
		//9 ist die maximale tiefe bei tic tac toe, oft ended das speil aber schon nach weniger zuegen
		if(depth < 9)
		{
			//sollte isAI true sein (also PC und minuswerte)
			if(isAI == true)
			{
				bestScore = -999; //PC wird als minimizer angesetzt und versucht den tiefts moeglichen score zu erhalten
				for(int i = 0; i < SIDE; i++)
				{
					for(int j = 0; j < SIDE; j++)
					{
						//sollte der errechnete feld frei sein
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE; //wird deas feld auf das symbol des pc gesetzt
							score = minimax(board, depth + 1, false); //minimax wird aufgerufen mit erhoetem depth, und isAI auf false 
							board[i][j] = ' ';
							//sollte das resultat besser sein als das errechnete
							if(score > bestScore)
							{
								bestScore = score; //wird dieses in die variable des errechneten gespeichert
							}
						}
					}
				}
				return bestScore; //und zurueckgegeben
			}
			else
			{
				//das selbe wird mit dem Zug des menchen gemacht
				bestScore = 999; //Spieler ist in diesem fall der maximizer (versucht den hoechts moeglichen score zu erhalten)
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ') //7wenn feld frei
						{
							board[i][j] = HUMANMOVE; //Spieler setzt sein symbol auf feld
							score = minimax(board, depth + 1, true); //hier wird isAI auf true gesetzt, aslo pc ist nachster zug
							board[i][j] = ' ';
							//score wird auf besmoegliche gesetzt
							if (score < bestScore)
							{
								bestScore = score; 
							}
						}
					}
				}
				return bestScore;//und zurueckgegeben
			}
		}
		else
		{
			return 0; //sollte keiner der beiden in dem errechneten zug als gewinner hervortreten, wird "0" (unentschieden) zurueckgegeben
		}
	}
	return 0;
}

//Function um besten naechsten Zug zu errechnen Benutzt den minimax, also die errechnung des bestmoeglichen Resultates
//fuer den PC wird aufgerufen wenn pc am zug also der minimizer
//hier wird dann, nachdem minimax die moeglichkeiten errechnet hat, der beste zug fuer pc ausgewaehlt und ausgefuehrt
int Hard::bestMove(char board[][SIDE], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999; //bestcore is negativ, da pc als minimizer angesetzt ist
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE; //zug wird ausgefuehrt
				score = minimax(board, moveIndex+1, false); //minimax wird nochmals aufgerufen um moeglichkeiten zu errechnen
				board[i][j] = ' ';
				if(score > bestScore) //bestes resultat wird optimiert
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y; //errechnet und position des feldes zurückgegeben
}

// Dies ist die ausfuehrende Function fuer das Spiel
//whoseTurn (wer ist dran?) wird hier gesetzt und entschieden, siehe letzte zeilen der funktion
void Hard::playTicTacToe(int whoseTurn) 
{ 
	char board[SIDE][SIDE]; //brett 
	int moveIndex = 0, x = 0, y = 0; //index fuer bewegungen | x achse index | y achse index
	initialise(board); //bord wird initialisiert (siehe helper_functions.hpp)
	showInstructions(); //beschreibung wird ausgegeben (siehe helper_functions.hpp)
	
	// Es wird gespielt bis gewinner oder unentschieden
	while (gameOver(board) == false && moveIndex != SIDE*SIDE) 
	{ 
		int n; // variable in dem der Zug gespeichert wird
		if (whoseTurn == COMPUTER) //wenn pc dran ist
		{
			n = bestMove(board, moveIndex); //wird der bestmoegliche zug errechnet und gespeichert
			x = n / SIDE; //x position wird errechnet
			y = n % SIDE; //y position wird errechnet
			board[x][y] = COMPUTERMOVE; //und gesetzt
			printf("PC hat ein %c in Feld %d gesetzt\n\n", COMPUTERMOVE, n+1); //ausgabe info ueber den zug
			showBoard(board); //das upgedatete brett wird gezeigt (siehe helper_functions.hpp)
			moveIndex ++; //index des zuges wird erhoet
			whoseTurn = HUMAN; //der zug dem Spieler uebergeben
		} 
		else if (whoseTurn == HUMAN) //ist der Spieler am Zug
		{
			//ausgabe der zu belegenden felder des bretts
			cout << "Du kannst folgende Positionen besetzen : ";
			for(int i=0; i<SIDE; i++)
				for (int j = 0; j < SIDE; j++)
					if (board[i][j] == ' ')
			printf("%d ", (i * 3 + j) + 1);
			cout << "\n\nBitte gebe eine Position ein = ";
			cin >> n;
			n--; //zug wird entgegengenommen und gespeichert
			x = n / SIDE; //x position wird errechnet
			y = n % SIDE; //y position wird errechnet
			system(CLEAR);
			if(board[x][y] == ' ' && n < 9 && n >= 0) //wenn feld frei und erlaubter zug (1-9)
			{
				board[x][y] = HUMANMOVE;  //wird gesetzt
				printf ("\nSpieler hat ein %c in Feld %d gesetzt\n\n", HUMANMOVE, n+1); //ausgabe
				showBoard(board); //upgedatetes brett
				moveIndex ++; //index erhoet
				whoseTurn = COMPUTER; //zug auf pc gesetzt
			}
			else if(board[x][y] != ' ' && n<9 && n>=0) //sollte das feld nicht frei
			{
				cout << "\nDieses Feld ist besetzt, bitte wahle eine anderes Feld:\n\n";
				clearBuffer();
			}
			else if(n<0 || n>8) ///sollte ungueltiger Zug
			{
				cout << "Das ist kein gueltiges Feld\n";
				clearBuffer();
			}
		} 
	} 

	// Wenn das Speil unentschieden 
	if (gameOver(board) == false && moveIndex == SIDE * SIDE) 
		cout << "Das Spiel war unentschieden!\n"; 
	else //wenn nicht
	{ 
		// wird zwischen Spieler und PC der zug gewechselt
		if (whoseTurn == COMPUTER) 
			whoseTurn = HUMAN; 
		else if (whoseTurn == HUMAN) 
			whoseTurn = COMPUTER; 
		
		declareWinner(whoseTurn); //gewinner wird ausgegeben (siehe helper_functions.hpp)
	} 
} 

