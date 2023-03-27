#ifndef HARD_HPP
#define HARD_HPP

//classe Hard, das schwerste Level erbt methoden von interface iLevel
class Hard: public iLevel
{
public:
	const string LEVEL = "Hard"; //constante fuer begruessung
	
	////Methoden werden in klassen cpp definiert
	int minimax(char board[][SIDE], int depth, bool isAI);
	int bestMove(char board[][SIDE], int moveIndex);
	void playTicTacToe(int whoseTurn);
	//friend functions sind in helper_functions.hpp definiert
	friend void initialise(char board[][SIDE]);
	friend void declareWinner(int whoseTurn);
	friend bool rowCrossed(char board[][SIDE]);
	friend bool columnCrossed(char board[][SIDE]);
	friend bool diagonalCrossed(char board[][SIDE]);
	friend bool gameOver(char board[][SIDE]);
};


#endif