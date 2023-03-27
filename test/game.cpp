/* ausführendes programm mit main() 

--als erstes werden als einziger ort alle eigenen headers importiert damit die datei so wie die dateien die aufgerufen werden laufen können.

--login.cpp wird importier da deises fuer den login gebraucht wird

--in dieser datei (controller) läuft in der main() funktion das ganze programm und es wird entschieden welche dateien zu welchen zeitpunkt aufgerufen werden...

*/
//alle header werden included
//main-header
#include "include/main_header.hpp"
//hilfsfunktionen und friend funktions header (helper_functions)
#include "include/helper_functions.hpp"
//alle Klassen .hpp files

//Login
#include "login.cpp"
//menue hpp dateien


//cpp klassendateien
#include "Board.hpp"
#include "Player.hpp"



//menue klassen cpp dateien

#include "Player.cpp"
#include "Board.cpp"




//klasse program fuehrt das program aus wird also als einzige klasse direkt in cpp declariert und definiert



//main führt das Programm aus und kontrolliert welche action ausgeführt wird
int main(int argc, char **argv) //args koennen entgegengenommen werden fuer login
{
	system(CLEAR);
	//deklaration der variablen fuer login
	string password;
 	string username;
	if(argc > 3 || argc == 2) //wenn mehr als 3 args oder nur 2 args
	{
		cout << "\nFehleingabe! Es koennen nur 2 Argumente beigefuegt werden!\n\n";
		cout << "Sie koennen auch das programm starten und die Daten werden erfragt!\n\n";
		exit(0);
	}
	if(argc == 3) //wenn genau der programm name, user und passwort
	{
		username = argv[1];  // werden die daten gespeichert zur ueberpruefung
		password = argv[2];
	}
	else //sollten keine args eingegen werden und nur das programm aufgerufen kommt die login maske
	{
	login: //label login, sollte der login fehlschlagen und erneut gewünscht sein wird man hierher zurückgeschickt mit goto
	//variablen werden an die funktionen geschickt, damit diese den wert setzen und zurückgeben
	getUser(username);
	getPassword(password);
	}
	//login wird geprüft in login.cpp in diesm fall ist der Admin login vorgegeben in Passwords.txt zum testen
	if(checkLogin(username, password)) //sollte das login erfolgreich sein wird das programm gestartet
	{
		system(CLEAR);
		Board board; //Program Objekt wird erstellt
		Player player;
		welcome(); //Gruss aus hilfsfunktionen wird aufgerufen
		do{
			printProgMenu(); //Programm menue wird aus helper_functions geholt und ausgegeben
			get_input: //sollte der input fehlschlagen wird man hierher zurueckgefuert
			cin >> board.input; //input wird entgegengenomen
			// falls input keinem integer entspricht liefert fail() true zurück
			if(cin.fail() || board.input > board.END ) //wenn der input groesser als enum END kommt auch true zurück
			{
				clearBuffer();
				printWrongNumErr(board.END); //fehler ausgabe 
				goto get_input; //zurück zum input
			}
			if(board.input == board.QUIT) //wenn der input enum "0" entspricht...
			{
				system(CLEAR);
				farewell(); // ausgabe von abschied 
				break; // programm verlassen
			}
		
			switch(board.input) //ansonsten den input als parameter fuer den switch
			{
				case board.EASY: 
				{
					system(CLEAR);
					cout << "EASY\n";
					keyWait();
					
				}
				break;
			
				case board.MEDIUM:
				{
					system(CLEAR);
					cout << "MEDIUM\n";
					keyWait();
					
				}
				break;
			
				case board.HARD:
				{
					system(CLEAR);
					player.select_game_type();

					if(state != QUIT) 
					{

						player.get_player_symbol();

						while(state != QUIT) 
						{
							while(state == PLAYING) 
							{
								player.initialise_player_move();
								player.get_move();
								board.update_game();
							}

							if(game_over()) 
							{
								board.find_winner();
								board.display_result();
				
								reset_state();
								reset_board();
				
							}

							player.select_game_type();
						}
					}
				}
				break;
				
				case board.VERSUS:
				{
					system(CLEAR);
					cout << "VERSUS\n";
					keyWait();
					
				}
				break;
			
				default:
					printWrongNumErr(board.END); ////fehler ausgabe 
				break;
			}
		}while(board.input != board.QUIT); //hauptmenue läuft bis QUIT enum eingegeben wird
	
	}
	//das ist der else vom login, sollte dieser fehlschlagen ist, wird...
	else
	{
		char c; //char deklariert
		cout << "\nFehlerhafte Daten!\n\n"; //fehlermeldungen ausgegeben
		cout << "n.- Daten erneut eingeben\nq.- App verlassen\n\n"; //optionen ausgegeben
		get_char:
		cin >> c; //char entgegengenommen
		if(c == 'n') //char geprüft ob neue eingabe erwuenscht ist
		{
			goto login; //wenn ja zurück zu login
		}
		else if(c == 'q') //wenn q also prog verlassen gewaehlt
		{
			farewell(); //abschied ausgeben
			exit(0); //programm verlassen
		}
		else //sollte keiner der beiden optionen eingegebn werden
		{
		   cout << "Bitte 'n' oder 'q' eingeben\n"; //fehlermeldung
		   goto get_char; //zurück zur eingabe		
		}	
	}
	return 0; //muss immer bei main dabei sein
}



