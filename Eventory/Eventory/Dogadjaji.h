#pragma once
#include"ListaDogadjaja.h"
#include"Kategorije.h"
#include"KorisnickiNalozi.h"

class Dogadjaji
{
	ListaDogadjaja lista;
public:
	Dogadjaji();
	~Dogadjaji();
	bool pregledDogadjaja();
	bool filtriranjeDogadjaja();
	bool kreiranjeDogadjaja();
	bool brisanjeDogadjaja();
	bool izmjenaDogadjaja();
	bool odobravanjeKomentara();
	bool izmjenaKategorija();
	bool sablon(std::string);
	void setAdminInfo(bool);
};

