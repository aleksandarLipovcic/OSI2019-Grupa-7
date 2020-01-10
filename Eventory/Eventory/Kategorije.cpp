#include "Kategorije.h"

Kategorije::Kategorije()
{
	std::string line;
	std::ifstream myfile("kategorije.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			nizKategorija.push_back(line);
		}
		myfile.close();
	}
	else std::cout << "Neuspjesno otvaranje datoteke";
	izmjena = false;
}

Kategorije::~Kategorije()
{
	if (izmjena)
	{
		std::ofstream myfile("kategorije.txt");
		if (myfile.is_open())
		{
			for (std::vector<std::string>::iterator it = nizKategorija.begin(); it != nizKategorija.end(); ++it)
				myfile << *it << '\n';
			myfile.close();
		}
		else std::cout << "Neuspjesno otvaranje datoteke";
	}
}

std::string Kategorije::getKategorija(int i)
{
	return nizKategorija[i];
}

int Kategorije::getBrojKategorija()
{
	return nizKategorija.size();
}

void Kategorije::dodajKategoriju(std::string kategorija)
{
	izmjena = true;
	nizKategorija.push_back(kategorija);
}

void Kategorije::obrisiKategoriju(int i)
{
	izmjena = true;
	nizKategorija.erase(nizKategorija.begin() + i);
}

