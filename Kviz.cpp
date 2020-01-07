#include "Kviz.h"
#include "KorisnickiNalozi.h"
#define BROJ_PITANJA_U_FAJLU 31
#define BROJ_PITANJA_ZA_PRIKAZ 10

void Kviz::slucajniNizOdDo(int min, int max, std::vector<int> &slucajniNiz)
{
	int temp;
	bool kraj = true;
	do
	{
		temp = rand() % max + min;
		if (!slucajniNiz.size()) slucajniNiz.push_back(temp);
		else if (slucajniNiz.size() == 10) kraj = false;
		else
		{
			for (int i = 0; i < (int)slucajniNiz.size(); ++i)
			{
				if (slucajniNiz[i] == temp)
				{
					kraj = false;
					break;
				}
			}
			if (kraj) slucajniNiz.push_back(temp);
			else kraj = true;
		}
	} while (kraj);
	std::sort(slucajniNiz.begin(), slucajniNiz.end());
}

Kviz::Kviz()
{
	std::vector<int> slucajniNiz;
	slucajniNizOdDo(0, BROJ_PITANJA_U_FAJLU, slucajniNiz);
	osvojeniBodovi = 0;
	for (int i = 0; i < BROJ_PITANJA_ZA_PRIKAZ; ++i)
	{
		Pitanja pitanje(slucajniNiz[i]);
		nizPitanja.push_back(pitanje);
	}
}

Kviz::~Kviz()
{
}

void Kviz::pokreniKviz()
{
	header();
	std::cout << R"(					 _____ _   _ _____ _   _ _____ _____________   __	 _   ___   _ _____ ______ 
					|  ___| | | |  ___| \ | |_   _|  _  | ___ \ \ / /	| | / / | | |_   _|___  / 
					| |__ | | | | |__ |  \| | | | | | | | |_/ /\ V / 	| |/ /| | | | | |    / /  
					|  __|| | | |  __|| . ` | | | | | | |    /  \ /  	|    \| | | | | |   / /   
					| |___\ \_/ / |___| |\  | | | \ \_/ / |\ \  | |  	| |\  \ \_/ /_| |_./ /___ 
					\____/ \___/\____/\_| \_/ \_/  \___/\_| \_| \_/  	\_| \_/\___/ \___/\_____/ )" << std::endl;
	header();

	int odgovor;
	for (int i = 0; i < 10; ++i)
	{
		std::cout << nizPitanja[i];
		std::cin >> odgovor;
		getchar();
		if (odgovor-1 == nizPitanja[i].getPozicijaTacnogOdgovora())
		{
			std::cout << std::endl << "Odgovor je tacan." << std::endl;
			osvojeniBodovi++;
		}
		else
		{
			std::cout << std::endl << "Netacno. \nTacan odgovor je " << nizPitanja[i].getPozicijaTacnogOdgovora() + 1 << std::endl;
		}
		header();
	}
	header();
	std::cout << "Kviz je zavrsen.\nBroj osvojenih bodova je: " << osvojeniBodovi * 10 << "% .\n";
	header();
}