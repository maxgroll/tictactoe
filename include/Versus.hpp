#ifndef VERSUS_HPP
#define VERSUS_HPP

//classe Versus, zwei spieler methode tic tac toe wird angepasst in Versus.cpp
class Versus
{
public:
	const string LEVEL = "Versus"; //constante fuer begruessung

	////Methoden werden in klassen cpp definiert
	void playTicTacToe(int whoseTurn);
	//friend functions sind in helper_functions.hpp definiert
	friend void initialise(char board[][SIDE]);
	friend void declareWinnerVersus(int whoseTurn);
	friend bool rowCrossed(char board[][SIDE]);
	friend bool columnCrossed(char board[][SIDE]);
	friend bool diagonalCrossed(char board[][SIDE]);
	friend bool gameOver(char board[][SIDE]);
};

#endif