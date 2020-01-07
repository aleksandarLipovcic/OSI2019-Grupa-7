#pragma once
#include"Pitanja.h"
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>

class Kviz
{
	std::vector<Pitanja> nizPitanja;
	int osvojeniBodovi;
	void slucajniNizOdDo(int, int, std::vector<int> &);

public:
	Kviz();
	~Kviz();
	void pokreniKviz();
};
