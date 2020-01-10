#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

class InformacijeOGradu
{
	std::vector<std::string> nizInformacija;
public:
	friend std::ostream& operator<<(std::ostream& stream, const InformacijeOGradu& other)
	{
		for (int i = 0; i < (int)other.nizInformacija.size(); ++i)
			stream << other.nizInformacija[i] << std::endl;
		return stream;
	}
	InformacijeOGradu();
	~InformacijeOGradu();
};

