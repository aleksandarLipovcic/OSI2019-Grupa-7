#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

class Kategorije
{
	bool izmjena;
	std::vector<std::string> nizKategorija;
public:
	friend std::ostream& operator<<(std::ostream& stream, const Kategorije& other)
	{
		for (int i = 0; i <(int)other.nizKategorija.size(); ++i)
			stream << i+1 << ". " << other.nizKategorija[i] << std::endl;
		return stream;
	}
	Kategorije();
	~Kategorije();
	std::string getKategorija(int);
	int getBrojKategorija();
	void dodajKategoriju(std::string kategorija);
	void obrisiKategoriju(int);
};

