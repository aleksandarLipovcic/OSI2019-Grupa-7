#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
/*
Verzija:1.0
Autor:Marko Mihajlovic
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
	//pomocne funkcije za pravljenje naloga
	bool enterUsername();
	bool enterPassword();
	//funkcija koja se poziva da se napravi nalog
	void napraviNalog();
};

