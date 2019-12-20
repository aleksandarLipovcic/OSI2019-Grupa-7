#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
/*
Verzija:1.1
Autor:Marko Mihajlovic
Nije jos tesrirano.
*/
using namespace std;

class Nalog
{
private:
	string username;
	string password;
public:
	Nalog();
	Nalog(const Nalog&);
	Nalog(Nalog&&);
	~Nalog();

	Nalog& operator=(const Nalog&);
	Nalog& operator=(Nalog&&);

	string getUsername();
	void setUsername(string);
	string getPassword();
	void setPassword(string);
private:
	//pomoce funkcije za konstruktore i operatore dodjele
	void copy(const Nalog&);
	void move(Nalog&&);
	void del();
	//pomocne funkcije za pravljenje naloga i za ulogovanje sa vec postojecim nalogom
	bool enterUsername();
	bool enterPassword();
	bool checkUsername();
	bool checkPassword();
	//funkcija koja se poziva da se napravi nalog i uloguje sa vec postojecim nalogom
	void napraviNalog();
	bool ulogujSe();

};

