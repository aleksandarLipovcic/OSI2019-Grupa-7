#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<vector>
#define BROJ_ODGOVORA_NA_PITANJE 3

class Pitanja
{
	int pozicijaTacnogOdgovora;
	std::vector<std::string> odgovori;
	std::string tekstPitanja, redniBroj;
	void izdvojiTekstPitanja(std::string);
	void izdvojiOdgovore(std::string);

public:
	friend std::ostream& operator<<(std::ostream& stream, const Pitanja& other)
	{
		stream << other.tekstPitanja << std::endl;
		for (int i = 0; i < BROJ_ODGOVORA_NA_PITANJE; ++i)
			stream << i + 1 << ". " << other.odgovori[i] << std::endl;
		return stream;
	}
	Pitanja(int);
	~Pitanja();
	int getPozicijaTacnogOdgovora();
};