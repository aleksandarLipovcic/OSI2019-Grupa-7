#pragma once
#include"Kategorije.h"
#include"KorisnickiNalozi.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include<string>
#include<cstring>
#include<algorithm>
#include<functional>

class ListaDogadjaja
{
	std::vector<std::string> nizDogadjaja;
	bool izmjena,admin;
	std::string datum;


	int uporediDatume(std::string, std::string);
	void mojSort(std::vector<std::string>&izdvojeniDogadjaji,std::string );
	bool uslovZaSort(std::string s1, std::string s2, std::string uslov);

public:
	friend std::ostream& operator<<(std::ostream& stream, ListaDogadjaja& other)
	{
		for (int i = 0; i < (int)other.nizDogadjaja.size(); ++i)
		{
			std::string ime(other.nizDogadjaja[i]);
			stream << i + 1 << ". " << other.getNaziv(ime) << std::endl;
		}
		return stream;
	}
	ListaDogadjaja();
	~ListaDogadjaja();
	bool prikaziDogadjaj(std::string);
	bool pregledZeljenihDogadjaja(int);
	bool pregledDogadjajaOdredjeneKategorije();
	int getBrojDogadjaja();
	void obrisiDogadjaj(int);
	bool kreirajIliIzmjeniDogadjaj(std::string uslov,int redniBrojDogadjajaZaIzmjenu);
	bool sortirajDogadjaje(std::vector<std::string>&);
	void prikaziNeodobreneKomentare(std::string);
	void izdvojiSaNeodobrenimKomentarima(std::vector<std::string>&);
	void komentarisanjeDogadjaja(std::string nazivDogadjaja);
	bool pregledDogadjajaPo(std::string,std::string);
	char* convert(std::string str);
	std::string getNaziv(std::string)const;
	std::string getKategorijaDogadjaja(std::string)const;
	std::string getDatum(std::string)const;
	std::string getInfoKom(std::string)const;
	void setInfoKom(std::string&, char)const;
	void setAdminInfo(bool);
	void ispisiSa(std::string,std::string, std::vector<std::string>&);
	bool provjeriDatum(std::string&);
	int uporediNaziv(std::string, std::string);
	bool provjeriIntervalDatuma(std::string);
	
};
