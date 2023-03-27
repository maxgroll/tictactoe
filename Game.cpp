/* class Game ausführendes programm mit main() 
wird als eintige klasse hier direkt deklariert und definiert da es de ausführende klasse ist

--als erstes werden als einziger ort alle eigenen headers importiert damit die datei so wie die dateien die aufgerufen werden laufen können.

--login.cpp wird importier da deises fuer den login gebraucht wird

--in dieser datei (controller) läuft in der main() funktion das ganze programm und es wird entschieden welche dateien zu welchen zeitpunkt aufgerufen werden...

*/

//main-header
#include "include/main_header.hpp"
//hilfsfunktionen und friend funktions header (helper_functions)
#include "include/helper_functions.hpp"


//alle Klassen .hpp files
#include "include/iLevel.hpp"  //interface was die funktionen fuer die LevelKlassen vorgibt
//level klassen
#include "include/Easy.hpp"
#include "include/Medium.hpp"
#include "include/Hard.hpp"
#include "include/Versus.hpp"


//cpp klassendateien
#include "source/Easy.cpp"
#include "source/Medium.cpp"
#include "source/Hard.cpp"
#include "source/Versus.cpp"

//Login cpp
#include "source/login.cpp"

//klasse Game fuehrt das program aus wird also als einzige klasse direkt in cpp declariert und definiert
class Game
{
public:
	int input; // variable input die für alle eingaben und den switch benutzt wird
	enum options{QUIT = 0, EASY, MEDIUM, HARD, VERSUS, END=VERSUS}; //enum fuer die optionen des switches
	
};

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
		Game game;
		welcome(); //Gruss aus hilfsfunktionen wird aufgerufen
		do{
			printProgMenu(); //Programm menue wird aus helper_functions geholt und ausgegeben
			get_input: //sollte der input fehlschlagen wird man hierher zurueckgefuert
			cin >> game.input; //input wird entgegengenomen
			// falls input keinem integer entspricht liefert fail() true zurück
			if(cin.fail() || game.input > game.END ) //wenn der input groesser als enum END kommt auch true zurück
			{
				clearBuffer();
				printWrongNumErr(game.END); //fehler ausgabe 
				goto get_input; //zurück zum input
			}
			if(game.input == game.QUIT) //wenn der input enum "0" entspricht...
			{
				system(CLEAR);
				farewell(); // ausgabe von abschied 
				break; // programm verlassen
			}
		
			switch(game.input) //ansonsten den input als parameter fuer den switch
			{
				//Fuer die cases werden die options aus dem enum benutzt
				case game.EASY: 
				{
					system(CLEAR);
					Easy easy; //objekt erstellen
					levelWelcome(easy.LEVEL); //willkommensgruss mit Level Angabe
					char cont='j'; //char fuer die do while loop
					do {
						char choice; //char fuer eingabe
						getInput(); //abfrage wird geholt aus helper_functions.hpp
						easy_get_choice: //label
						cin >> choice;
						system(CLEAR);
						if(choice=='q') //wenn 'q' raus
						{
							clearBuffer();
							break;
						}
						else if (choice!='n' && choice!='j') //wenn nicht richtiger char
						{
							clearBuffer();
							wrongInputErr(); //error ausgabe
							goto easy_get_choice; //erneute abfrage 
						}
						//function die das spiel startet wir aus der Klasse (level) geholt
						//wenn choice 'n' also nicht den ersten Zug erhalten, dann faengt PC an, sont Spieler
						easy.playTicTacToe(choice=='n'? COMPUTER : HUMAN); 
						cout << "\nSpiel verlassen?(j/n) : "; //wenn j wird spiel verlassen
						cin >> cont;
						system(CLEAR);
					} while(cont=='n');
				}
				break;
				//siehe case game.EASY, hat genau den selben aufbau
				case game.MEDIUM:
				{
					system(CLEAR);
					Medium medium;
					levelWelcome(medium.LEVEL);
					char cont='j';
					do {
						char choice;
					 	getInput();
						medium_get_choice:
						cin >> choice;
						system(CLEAR);
						if(choice=='q')
						{
							clearBuffer();
							break;
						}
						else if (choice!='n' && choice!='j')
						{
							clearBuffer();
							wrongInputErr();
							goto medium_get_choice; 
						}
						medium.playTicTacToe(choice=='n'? COMPUTER : HUMAN);
						cout << "\nSpiel verlassen?(j/n) : ";
						cin >> cont;
						system(CLEAR);
					} while(cont=='n');
				}
				break;
				//siehe case game.EASY, hat genau den selben aufbau
				case game.HARD:
				{
					system(CLEAR);
					Hard hard;
					levelWelcome(hard.LEVEL);
					char cont='j';
					do {
						char choice;
					 	getInput();
						hard_get_choice:
						cin >> choice;
						system(CLEAR);
						if(choice=='q')
						{
							clearBuffer();
							break;
						}
						else if (choice!='n' && choice!='j')
						{
							clearBuffer();
							wrongInputErr();
							goto hard_get_choice; 
						}
						hard.playTicTacToe(choice=='n'? COMPUTER : HUMAN);
						cout << "\nSpiel verlassen?(j/n) : ";
						cin >> cont;
						system(CLEAR);
					} while(cont=='n');
				}
				break;
				//case Versus fast gleich aufgebaut als die anderen mit einigen Unterschieden
				//es wird mit konstanten nummern fuer Spieler 1 und 2 gearbeitet
				//die Function die das spiel startet, startet mit spieler 1 und 2 nicht mit PC und Spieler
				case game.VERSUS:
				{
					system(CLEAR);
					Versus versus;
				    levelWelcome(versus.LEVEL);
					char cont='j';
					do {
						int choice;
						versusGetInput();
						versus_get_choice:
						cin >> choice;
						system(CLEAR);
						if(!cin)
						{
							clearBuffer();
							versusWrongInputErr();
							goto versus_get_choice;
						}
						if(choice == 0)
						{
							clearBuffer();
							break;
						}
						else if (choice!=1 && choice!=2)
						{
							clearBuffer();
							versusWrongInputErr();
							goto versus_get_choice;
						}
						//!!!hier wird gefragt welcher Spieler anfangen will
						versus.playTicTacToe(choice==1? PLAYER1 : PLAYER2);
						cout << "\nSpiel verlassen?(j/n) : ";
						cin >> cont;
						system(CLEAR);
					} while(cont=='n');
					system(CLEAR);	
				}
				break;
			
				default:
					printWrongNumErr(game.END); ////fehler ausgabe 
				break;
			}
		}while(game.input != game.QUIT); //hauptmenue läuft bis QUIT enum eingegeben wird
	
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



