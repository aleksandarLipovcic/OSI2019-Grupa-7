#include "InformacijeOGradu.h"

InformacijeOGradu::InformacijeOGradu()
{
	std::string line;
	std::ifstream myfile("informacijeOGradu.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			nizInformacija.push_back(line);
		}
		myfile.close();
	}
	else std::cout << "Ne uspjesno otvaranje datoteke";
}

InformacijeOGradu::~InformacijeOGradu()
{
}
