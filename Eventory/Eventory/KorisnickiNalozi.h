#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>

class KorisnickiNalozi
{
	std::string korisnickoIme,lozinka;
public:
	KorisnickiNalozi(std::string , std::string);
	~KorisnickiNalozi();
	bool daliPostojiNalog();
	std::string getKorisnickoIme();
};

std::string ucitajLozinku(std::string);
std::string ucitajKorisnickoIme();
void grb();
void header();
void footer();