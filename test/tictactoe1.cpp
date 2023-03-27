#include <iostream>
#include <string>
#include <list>


static const int nk = 100;

// declaring the possible states
static enum {START, PLAYING, QUIT, OWIN, XWIN, DRAW} state;
typedef struct 
{
	char symbol;
	int move;
	bool selected;
	bool win;
};
player;


void display_board();				
void get_move();                    
void display_result();				
void select_game_type();            
void get_player_symbol();           
void find_winner();                 
void update_board();                               
void update_screen();               
void verify_move();                
void reset_state();                 
void reset_board();                 
void initialise_player_move();              
void display_game_progress();       
void update_game();                 
bool wrong_symbol();                
bool wrong_selection();             
bool game_over();                   
bool free_square();      
void generate_moves(char _board[9], std::list<int> &move_list);
void check_game_state(char board[9]);
int evaluate_position(char _board[9], player _player);
int MiniMax(char _board[9], player _player);	
int MinMove(char _board[9], player _player);	
int MaxMove(char _board[9], player _player);
           


static player player1, player2, current_player;
static std::string game_type; 
static std::string prev_game_type;
static char board[9] = {0}; 
static char cSymbol;
static int nMove; 


int main() 
{
	select_game_type();

	if(state != QUIT) 
	{

		get_player_symbol();

		while(state != QUIT) 
		{
			while(state == PLAYING) 
			{
				initialise_player_move();
				get_move();
				update_game();
			}

			if(game_over()) 
			{
				find_winner();
				display_result();
				
				reset_state();
				reset_board();
				
			}

			select_game_type();
		}
	}
	return 0;
}


// Menu
void select_game_type() 
{
	std::cout <<"   1 - Play a Game Against the Computer"<<std::endl;

	std::cout << "   2 - Quit the Program" << std::endl;
	std::cout <<"Enter Selection "<<std ::endl;
	int choice;
	std::cin >> choice;
	if(!std::cin.good()) 
	{
		std::cout << "please notice that you can only enter integers for the selection" << std::endl;
		update_screen();
	}
	switch(choice) 
	{
		case 1:
			game_type = "h";
			break;

		case 2:
			state = QUIT;
			break;
		default:
			std::cout << "Invalid Selection." << std::endl;
			update_screen();
	}
	if(choice > 0 && choice < 3) 
	{
		if(prev_game_type != "" && game_type != prev_game_type) 
		{



			get_player_symbol();
		}
		if(game_type.length() > 0) 
		{
			prev_game_type = game_type;
		}
	}
}



// symbol of the current player
void get_player_symbol() 
{
	if(game_type == "h") 
	{
		int selection = rand() % 2;
		
		if(selection == 0) 
		{
			rand() % 2 == 0 ? player2.symbol = 'X' : player2.symbol = 'O';
			cSymbol = player2.symbol;
			player2.selected = 1;
			std::cout << "CPU Will Play " << player2.symbol << std::endl;
		}
		else if(selection == 1)
		{
			std::cout << " Please Enter Your Symbol (X,O): ";
			std::cin >> player1.symbol;
			player1.symbol = toupper(player1.symbol);
			cSymbol = player1.symbol;
			player1.selected = 1;
		}
	} 

	
	if(!std::cin.good() || wrong_symbol()) 
	{
		std::cout << "Please Enter 'X' or 'O' " << std::endl;
		system("pause");
		get_player_symbol();
	}
	if(!player2.selected) 
	{
		player1.symbol == 'X' ? player2.symbol = 'O' : player2.symbol = 'X';
		player1.symbol == 'O' ? player2.symbol = 'X' : player2.symbol = 'O';
	}
	else if(!player1.selected) 
	{
		player2.symbol == 'X' ? player1.symbol = 'O' : player1.symbol = 'X';
		player2.symbol == 'O' ? player1.symbol = 'X' : player1.symbol = 'O';
	}
	state = PLAYING;
}

// gets move for the current turn
void get_move() 
{
	std::cin.sync();
	if(game_type == "h")
	{
		if(player1.selected) 
		{
			std::cout << "\n" << " Please Enter Your Move (1-9): ";
			std::cin >> player1.move;
			if(!std::cin.good())
			{
				std::cin.clear();
				std::cin.sync();
			}
			nMove = player1.move;
			cSymbol = player1.symbol;
			current_player = player1;
			player1.selected = 0;
			player2.selected = 1;

		}
		else if(player2.selected)
		{
			player2.move = MiniMax(board, player2);
			nMove = player2.move;
			cSymbol = player2.symbol;
			current_player = player2;
			player1.selected = 1;
			player2.selected = 0;
			reset_state();
		}
	} 
	verify_move();
	if(game_over())
	{
		return;
	}
}


// finds the winner 
void find_winner() 
{
	if(state == XWIN && player1.symbol == 'X')
	{
		player1.win = 1;
	} else if(state == OWIN && player1.symbol == 'O')
	{
		player1.win = 1;
	} else if(state == XWIN && player2.symbol == 'X') 
	{
		player2.win = 1;
	} else if(state == OWIN && player2.symbol == 'O') 
	{
		player2.win = 1;
	}
}


// verifies whether symbol entered is valid or not
bool wrong_symbol() 
{
	return (cSymbol != 'X' && cSymbol != 'O');
}

// checks for wrong move selection
bool wrong_selection() 
{
	return !(nMove > 0 && nMove < 10);
}

// reinitialises player moves
void initialise_player_move() 
{
	player1.move = -1;
	player2.move = -1;
}

// checks for the end of the game
bool game_over() 
{
	return (state == XWIN || state == OWIN || state == DRAW);
}

// resets the state of the game
void reset_state() 
{
	state = PLAYING;
}

// clears the board
void reset_board() 
{
	for(int i=0;i < 9;i++)
	{
		board[i] = 0;
	}
}

// updates currrent board position
void update_board() 
{
	if(state == PLAYING) 
	{
		if(player1.move != -1 && player2.move == -1) 
		{
			board[player1.move - 1] = player1.symbol;
		}
		else if(player2.move != -1) 
		{
			board[player2.move - 1] = player2.symbol;
		}
	}
}


// displays outcome 
void display_result()
 {
	if(player1.win) 
	{
		std::cout << "You Have Won The Game!" << std::endl;
	}
	else if(player2.win) 
	{
		std::cout << "CPU Has Won The Game!" << std::endl;
	} 
	else if(player1.win == 0 && player2.win == 0)
	{
		std::cout << "The Game Was a Draw." << std::endl;
	}
	system("pause");
	system("cls");
}

// makes updates
void update_game()
 {
	update_board();
	display_game_progress();
	check_game_state(board);
}

// checks if the square selected is empty
bool free_square() 
{
	if(player1.move != -1 && player2.move == -1) 
	{
		return board[player1.move - 1] == 0;
	} 
	else if(player2.move != -1) 
	{
		return board[player2.move - 1] == 0;
	}
	return 0;
}

// displays the tic tac toe board
void display_board() 
{
	std::cout << std::endl;
	std::cout << " " << board[0] << " | " << board[1] << " | " << board[2] << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout <<  " " << board[3] << " | " << board[4] << " | " << board[5] << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout <<  " " << board[6] << " | " << board[7] << " | " << board[8] << std::endl;
	std::cout << std::endl;
	std::cin.sync();
}

// displays the progress of the game
void display_game_progress() 
{
	system("cls");
	display_board();
}

// verifies validity of the current move n if its not valid it will ask to provide a valid move again
void verify_move() 
{
	if(wrong_selection() || !free_square()) 
	{
		std::cout << "Invalid Move." << std::endl;
		if(player2.move == -1) 
		{
			player1.selected = 1;
			player2.selected = 0;
		} else 
		{
			player1.selected = 0;
			player2.selected = 1;
		}
		system("pause");
		if(game_type == "h") 
		{
			player1.selected = 1;
			player2.selected = 0;
		}
		get_move();
	}
}



// refreshes the game screen
void update_screen()
 {
	system("pause");
	system("cls");
	std::cin.clear();
	std::cin.sync();
	select_game_type();
}

// determines if the current board position is a win or draw
void check_game_state(char board[9])
 {
	if ((board[0] == cSymbol && board[1] == cSymbol && board[2] == cSymbol) ||
		(board[3] == cSymbol && board[4] == cSymbol && board[5] == cSymbol) ||
		(board[6] == cSymbol && board[7] == cSymbol && board[8] == cSymbol) ||
		(board[0] == cSymbol && board[3] == cSymbol && board[6] == cSymbol) ||
		(board[1] == cSymbol && board[4] == cSymbol && board[7] == cSymbol) ||
		(board[2] == cSymbol && board[5] == cSymbol && board[8] == cSymbol) ||
		(board[0] == cSymbol && board[4] == cSymbol && board[8] == cSymbol) ||
		(board[2] == cSymbol && board[4] == cSymbol && board[6] == cSymbol)) 
	{
		if(cSymbol == 'X') 
		{
			state = XWIN;
		} 
		else if(cSymbol == 'O') 
		{
			state = OWIN;
		}
	}
	else 
	{
		state = DRAW;
		for(int i = 0; i < 9; ++i) 
		{
			if(board[i] == 0) {
				state = PLAYING;
				break;
			}
		}
	}
}

// generates all the possible moves
void generate_moves(char _board[9], std::list<int> &move_list)
 {
	for(int i = 0; i < 9; ++i) 
	{
		if(_board[i] == 0) 
		{
			move_list.push_back(i);
		}
	}
}

// evaluates the current board position
int evaluate_position(char _board[9], player _player) 
{
	check_game_state(_board);
	if(game_over()) 
	{
		if((state == XWIN && _player.symbol == 'X') ||
			(state == OWIN && _player.symbol == 'O'))
		{
			return +nk;
		} else if((state == XWIN && _player.symbol == 'O') ||
			(state == OWIN && _player.symbol == 'X')) 
		{
			return -nk;
		}
		else if(state == DRAW) 
		{
			return 0;
		}
	}
	return -1;
}

// returns best move for the current computer player
int MiniMax(char _board[9], player _player) 
{
	int best_val = -nk, index = 0;
	std::list<int> move_list;
	char best_moves[9] = {0};
	generate_moves(_board, move_list);
	while(!move_list.empty()) 
	{
		_board[move_list.front()] = _player.symbol;
		cSymbol = _player.symbol;
		int val = MinMove(_board, _player);
		if(val > best_val) 
		{
			best_val = val;
			index = 0;
			best_moves[index] = move_list.front() + 1;
		} else if(val == best_val) 
		{
			best_moves[++index] = move_list.front() + 1;
		}
		_board[move_list.front()] = 0;
		move_list.pop_front();
	}
	if(index > 0) 
	{
		index = rand() % index;
	}
	return best_moves[index];
}

// finds best move for min player
int MinMove(char _board[9], player _player) 
{
	int pos_value = evaluate_position(_board, _player);
	if(pos_value != -1)
	{
		return pos_value;
	}
	int best_val = +nk;
	std::list<int> move_list;
	generate_moves(_board, move_list);
	while(!move_list.empty()) 
	{
		_player.symbol == 'X' ? cSymbol = 'O' : cSymbol = 'X';
		_board[move_list.front()] = cSymbol;
		int val = MaxMove(_board, _player);
		if(val < best_val) 
		{
			best_val = val;
		}
		_board[move_list.front()] = 0;
		move_list.pop_front();
	}
	return best_val;
}

// finds best move for max player
int MaxMove(char _board[9], player _player) 
{
	int pos_value = evaluate_position(_board, _player);
	if(pos_value != -1) 
	{
		return pos_value;
	}
	int best_val = -nk;
	std::list<int> move_list;
	generate_moves(_board, move_list);
	while(!move_list.empty()) 
	{
		_player.symbol == 'X' ? cSymbol = 'X' : cSymbol = 'O';
		_board[move_list.front()] = cSymbol;
		int val = MinMove(_board, _player);
		if(val > best_val) 
		{
			best_val = val;
		}
		_board[move_list.front()] = 0;
		move_list.pop_front();
	}
	return best_val;
}