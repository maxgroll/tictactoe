#include "../include/main_header.hpp"

//Ist als einzige datei als struct definiert da sie eine hiflsdatei fuer das ausführende programm ist
//ausserdem habe ich dies schon funktionierende structur von vorherigen projekt genommen
struct login //struct login
{
	bool logcheck = false;
};

//funktion in main_header.hpp deklariert, hier definiert und in main() im programm aufgerufen
//nimmt eingaben des users als parameter
bool checkLogin(string username, string password)
{
	login login; //erstellt login objekt
	//daten aus passwords.txt werden geholt zum vergliech mit eingegebenen daten
	ifstream inf{"data/Passwords.txt"};
    if (!inf) 
    {
       cerr << " Datei konnte nicht geoeffnet werden!\n";
       exit(0);
    }
	string user;
	string pass;
	getline(inf, user);
	getline(inf, pass);
	inf.close();

	//prüft ob user eingabe und die gespeicherten daten uebereinstimmen und
	if(user == username  && pass == password)
	{
		login.logcheck = true; //setzt logcheck auf true wenn ja
	}
	else
	{
		login.logcheck = false; //auf false wenn nein
	}
	return login.logcheck; //gibt den wert zurueck
}
//funktion in main_header deklariert, hier definiert und in main() im programm aufgerufen
//erfragt den username und gibt ihn zurück fuer pruefung in checklogin()
string getUser(string &user)
{
	cout << "Username:\n";
	cin >> user;
	return user;
}
//funktion in main_header deklariert, hier definiert und in main() im programm aufgerufen
//erfragt den password und gibt ihn zurück fuer pruefung in checklogin()
string getPassword(string &password)
{
	cout << "Password:\n";
	cin >> password;
	return password;
}
