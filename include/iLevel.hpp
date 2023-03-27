#ifndef ILEVEL_HPP
#define ILEVEL_HPP

//interface iLevel vererbt die 3 methoden die jedes der Levels implementieren muss
class iLevel
{
public:
	//Methoden sind alle  pure virtual, daher ist die klasse abstract oder eher ein interface
	//wird von den drei levels Hard, Medium und Easy geerbt und implementiert
	virtual int minimax(char board[][SIDE], int depth, bool isAI)=0; //evaluationsfunction
	virtual int bestMove(char board[][SIDE], int moveIndex)= 0; //zug asufuehrung funktion
	virtual void playTicTacToe(int whoseTurn)=0; //spielfunktion
	
};


#endif