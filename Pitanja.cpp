#include "Pitanja.h"

void Pitanja::izdvojiTekstPitanja(std::string line)
{
	std::size_t found1, found2;
	found1 = line.find_first_of("|");
	found2 = line.find_first_of("|", found1 + 1);
	tekstPitanja.append(line, found1 + 1, found2 - found1 - 1);
}

void Pitanja::izdvojiOdgovore(std::string line)
{
	std::string temp;
	std::size_t found1, found2;
	found1 = line.find_first_of("|");
	found2 = line.find_first_of("|", found1 + 1);
	for (int i = 0; i < 3; ++i)
	{
		found1 = found2;
		found2 = line.find_first_of("|", found1 + 1);
		temp.append(line, found1 + 1, found2 - found1 - 1);
		odgovori.push_back(temp);
		temp = "";
	}
	temp = odgovori[0];
	odgovori[0] = odgovori[pozicijaTacnogOdgovora];
	odgovori[pozicijaTacnogOdgovora] = temp;
}

Pitanja::Pitanja(int redniBroj)
{
	pozicijaTacnogOdgovora = rand() % 3;
	std::string line;
	std::ifstream myfile("pitanjaIOdgovori.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (redniBroj == stoi(line, nullptr))
			{
				this->redniBroj = redniBroj;
				izdvojiTekstPitanja(line);
				izdvojiOdgovore(line);
			}
		}
		myfile.close();
	}
	else std::cout << "Neuspjesno otvaranje datoteke";
}

Pitanja::~Pitanja()
{
}

int Pitanja::getPozicijaTacnogOdgovora()
{
	return pozicijaTacnogOdgovora;
}