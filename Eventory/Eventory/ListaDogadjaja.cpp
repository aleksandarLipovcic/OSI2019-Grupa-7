#include "ListaDogadjaja.h"

ListaDogadjaja::ListaDogadjaja()
{
	std::string line;
	std::ifstream myfile("listaDogadjaja.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			nizDogadjaja.push_back(line);
		}
		myfile.close();
	}
	else std::cout << "Neuspjesno otvaranje datoteke";
	admin=izmjena = false;

	system("echo %date% > data.txt");
	std::ifstream myfile1("data.txt");
	if (myfile1.is_open())
	{
		while (getline(myfile1, line))
		{
			datum.append(line, line.find_first_of(" ") + 1, 10);
			char d1 = datum[0]; char d2 = datum[1]; char m1 = datum[3];char m2 = datum[4];
			datum[0] = m1; datum[1] = m2; datum[3] = d1; datum[4] = d2;
		}
		myfile1.close();
	}
	else std::cout << "Neuspjesno otvaranje datoteke";


}

ListaDogadjaja::~ListaDogadjaja()
{
	if (izmjena)
	{
		std::ofstream myfile("listaDogadjaja.txt");
		if (myfile.is_open())
		{
			for (std::vector<std::string>::iterator it = nizDogadjaja.begin(); it != nizDogadjaja.end(); ++it)
				myfile << *it << std::endl;
			myfile.close();
		}
		else std::cout << "Neuspjesno otvaranje datoteke";
	}
}

void ListaDogadjaja::izdvojiSaNeodobrenimKomentarima(std::vector<std::string>&izdvojeniDogadjaji)
{
	for (int i = 0; i < (int)nizDogadjaja.size(); ++i)
	{
		if (getInfoKom(nizDogadjaja[i]) != "0")
		{
			izdvojeniDogadjaji.push_back(nizDogadjaja[i]);
		}
	}
}

bool ListaDogadjaja::pregledDogadjajaPo(std::string string,std::string uslov)
{
	char temp[10];
	bool krajPrograma = true, krajCiklusa = true;
	std::vector<std::string> nizIzdvojenih;

	do
	{
		system("CLS");
		grb();
		header();
		std::cout << "(Da izaberete opciju ukucajte redni broj zeljene opcije.)" << std::endl;
		std::cout << "(Da zatvorite aplikaciju ukucajte ' kraj '.)" << std::endl;
		std::cout << "(Povratak na prethodnu stranu ' 0 '.)" << std::endl;
		footer();
		header();
		if (uslov == "naziv") 
		{
			std::cout << "FILTRIRANJE DOGADJAJA PO NAZIVU." << std::endl;
			std::cout << string << std::endl;
			ispisiSa(string, uslov,nizIzdvojenih);
			if ((int)nizIzdvojenih.size() == 0)
			{
				std::cout << "NEMA DOGADJAJA SA" << string << " NAZIVOM." << std::endl;
				getchar();
				return true;
			}
		}
		else if (uslov == "datum") 
		{
			bool uslovPetlje = false ;
			do
			{
				std::cout << "FILTRIRANJE DOGADJAJA PO DATUMU U INTERVALU. (dd.mm.gggg dd.mm.gggg)" << std::endl;
				std::cout << string << std::endl;
				uslovPetlje = provjeriIntervalDatuma(string);
				if (uslovPetlje)
				{
					ispisiSa(string, uslov, nizIzdvojenih);
					if ((int)nizIzdvojenih.size() == 0)
					{
						std::cout << "NEMA DOGADJAJA U INTERVALU" << string << std::endl;
						getchar();
						return true;
					}
				}
				else
				{
					std::cout << "INTERVAL NIJE DOBAR" << std::endl;
					getchar();
					return true;
				}
			} while (!uslovPetlje);
		}
		footer();
		



		krajCiklusa = true;
		while (krajCiklusa)
		{
			std::cout << "Unesite redni broj dogadjaja:" << std::endl;
			std::cin >> temp;
			getchar();
			if (temp[0] == '0')
			{
				return true;
			}
			else if (temp[0] == 'k')
			{
				return false;
			}
			else if (atoi(temp)-1 >= 0 && atoi(temp)-1 < (int)nizIzdvojenih.size())
			{
				krajPrograma = prikaziDogadjaj(nizIzdvojenih[atoi(temp) - 1]);
				krajCiklusa = false;
			}
			else
			{
				std::cout << "Ne postoji dogadjaj sa ' " << temp << " ' rednim brojem." << std::endl;
				getchar();
			}
		}

	} while (krajPrograma);
	return false;
}

char * ListaDogadjaja::convert(std::string str)
{
	char* niz = new char[(int)str.size()];
	for (int i = 0; i <= (int)str.size(); i++)
	{
		niz[i] = str[i];
	}
	return niz;
}

std::string ListaDogadjaja::getNaziv(std::string line)const
{
	std::string temp;
	temp.append(line, 16, line.find_first_of("|") -16);
	return temp;
}

std::string ListaDogadjaja::getKategorijaDogadjaja(std::string line)const
{
	std::string temp;
	std::size_t found1,found2;
	found1 = line.find_first_of("|");
	found2 = line.find_first_of("|", found1 + 1);
	temp.append(line, found1 + 1, found2 - found1-1);
	return temp;
}

std::string ListaDogadjaja::getInfoKom(std::string line)const
{
	std::string temp;
	std::size_t found1, found2;
	found1 = line.find_first_of("|");
	found2 = line.find_first_of("|", found1 + 1);
	found1 = found2;
	found2 = line.find_first_of("|", found1 + 1);
	temp.append(line, found1 + 1, found2 - found1 - 1);
	return temp;
}

void ListaDogadjaja::setInfoKom(std::string& line, char c) const
{
	line[line.size() - 2] = c;
}

void ListaDogadjaja::setAdminInfo(bool uslov)
{
	admin = uslov;
}

std::string ListaDogadjaja::getDatum(std::string line)const
{
	std::string temp;
	temp.append(line, 0, 16);
	return temp;
}

void ListaDogadjaja::ispisiSa(std::string string, std::string uslov, std::vector<std::string>& nizIzdvojenih)
{
	std::string pocetak, kraj;
	int broj = 0;
	if (uslov == "datum")
	{
		pocetak.append(string, 0, 10);
		kraj.append(string, 11, 21);
	}
	else if (uslov == "naziv")
	{
		for (int i = 0; i < (int)string.size(); ++i)
		{
			if (string[i] >= 65 && string[i] <= 90)
				string[i] += 32;
		}
	}

	for (int i = 0; i < (int)nizDogadjaja.size(); ++i)
	{
		std::string pomNaziv = getNaziv(nizDogadjaja[i]);
		for (int i = 0; i < (int)pomNaziv.size(); ++i)
		{
			if (pomNaziv[i] >= 65 && pomNaziv[i] <= 90)
				pomNaziv[i] += 32;
		}

		if (uslov == "naziv" && (pomNaziv.find(string) != std::string::npos))
		{
			nizIzdvojenih.push_back(nizDogadjaja[i]);
			std::cout << ++broj << ". " << getNaziv(nizDogadjaja[i]) << std::endl;
		}
		else if (uslov == "datum" && (uporediDatume(getDatum(nizDogadjaja[i]), pocetak) != 2 && uporediDatume(getDatum(nizDogadjaja[i]), kraj) != 1))
		{
			nizIzdvojenih.push_back(nizDogadjaja[i]);
			std::cout << ++broj << ". " << getNaziv(nizDogadjaja[i]) << std::endl;
		}
	}

}

bool ListaDogadjaja::provjeriDatum(std::string& datum)
{
	int broj,brojDana,brojMjeseca;
	std::string pom;
	if ((int)datum.size() == 16)
	{
		if (datum[2] == '.' && datum[5] == '.' && datum[10] == ' '  && datum[13] == '.')
		{
			if (datum[0] >= '0' && datum[0] <= '9' && datum[1] >= '0' && datum[1] <= '9')
			{
				brojDana = std::stoi(pom.assign(datum, 0, 2));
				if (brojDana > 0 && brojDana <= 31)
				{
					if (datum[3] >= '0' && datum[3] <= '9' && datum[4] >= '0' && datum[4] <= '9')
					{
						brojMjeseca= std::stoi(pom.assign(datum, 3, 2));
						if (brojDana > 29 && brojMjeseca == 2)
						{
							return false;
						}
						if (brojDana == 31 && ( brojMjeseca == 2 || brojMjeseca == 4 || brojMjeseca == 6 || brojMjeseca == 9 || brojMjeseca == 11 ))
						{
							return false;
						}
						if (brojMjeseca > 0 && brojMjeseca <= 12)
						{
							if (datum[6] >= '0' && datum[6] <= '9' && datum[7] >= '0' && datum[7] <= '9' &&datum[8] >= '0' && datum[8] <= '9' && datum[9] >= '0' && datum[9] <= '9')
							{
								broj = std::stoi(pom.assign(datum, 6, 4));
								if (broj > 1997 && broj <= 2100)
								{
									if (broj % 4 != 0 && broj % 100 != 0)
									{
										if (brojDana == 29 && brojMjeseca == 2)
										{
											return false;
										}
									}
									if (datum[11] >= '0' && datum[11] <= '9' && datum[12] >= '0' && datum[12] <= '9')
									{
										broj = std::stoi(pom.assign(datum, 11, 2));
										if (broj >= 0 && broj <= 23)
										{
											if (datum[14] >= '0' && datum[14] <= '9' && datum[15] >= '0' && datum[15] <= '9')
											{
												broj = std::stoi(pom.assign(datum, 14, 2));
												if (broj >= 0 && broj <= 59)
												{
													return true;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

int ListaDogadjaja::uporediNaziv(std::string s1, std::string s2)
{
	for (int i = 0; i < (int)s1.size(); ++i)
	{
		if (s1[i] >= 65 && s1[i] <= 90)
			s1[i] += 32;
	}
	for (int i = 0; i < (int)s2.size(); ++i)
	{
		if (s2[i] >= 65 && s2[i] <= 90)
			s2[i] += 32;
	}
	return s1.compare(s2);
}

bool ListaDogadjaja::provjeriIntervalDatuma(std::string string)
{
	std::string pocetak, kraj, pom = {" 00.00"};
	pocetak.append(string, 0, 10);
	kraj.append(string, 11, 21);
	pocetak.append(pom);
	kraj.append(pom);
	if (provjeriDatum(pocetak) && provjeriDatum(kraj))
	{
		if (uporediDatume(pocetak, kraj) == 2)
		{
			return true;
		}
	}
	return false;
}

int ListaDogadjaja::uporediDatume(std::string datumDogadjaja, std::string danasnjiDatum)
{
	int datum1, datum2;
	std::string pom;
	datum1 = std::stoi(pom.assign(datumDogadjaja, 6, 4));
	datum2 = std::stoi(pom.assign(danasnjiDatum, 6, 4));
	if (datum1 > datum2) return 1;
	else if (datum1 < datum2) return 2;
	else
	{
		datum1 = std::stoi(pom.assign(datumDogadjaja, 3, 2));
		datum2 = std::stoi(pom.assign(danasnjiDatum, 3, 2));
		if (datum1 > datum2) return 1;
		else if (datum1 < datum2) return 2;
		else
		{
			datum1 = std::stoi(pom.assign(datumDogadjaja, 0, 2));
			datum2 = std::stoi(pom.assign(danasnjiDatum, 0, 2));
			if (datum1 > datum2) return 1;
			else if (datum1 < datum2) return 2;
			else
				return 0;
		}
	}
}

void ListaDogadjaja::mojSort(std::vector<std::string>& izdvojeniDogadjaji,std::string uslov)
{
	for (int i = 0; i < (int)(izdvojeniDogadjaji.size()) - 1; ++i)
		for (int j = i; j < (int)izdvojeniDogadjaji.size(); ++j)
			if (uslovZaSort(izdvojeniDogadjaji[i], izdvojeniDogadjaji[j],uslov))
			{
				std::string temp = izdvojeniDogadjaji[j];
				izdvojeniDogadjaji[j] = izdvojeniDogadjaji[i];
				izdvojeniDogadjaji[i] = temp;
			}
}

bool ListaDogadjaja::uslovZaSort(std::string s1, std::string s2,std::string uslov)
{
	if (uslov == "poNazivuOpadajuce") 
		return uporediNaziv(getNaziv(s1), getNaziv(s2)) < 0 ? true : false;
	else if(uslov == "poDatumuOpadajuce")  
		return uporediDatume(getDatum(s1), getDatum(s2)) == 2 ? true : false;
	else if(uslov == "poNazivuRastuce")  
		return uporediNaziv(getNaziv(s1) , getNaziv(s2)) > 0 ? true : false;
	else if (uslov == "poDatumuRastuce")  
		return uporediDatume(getDatum(s1), getDatum(s2)) == 1 ? true : false;
	else return false;
}

bool ListaDogadjaja::sortirajDogadjaje(std::vector<std::string>&izdvojeniDogajaji)
{
	char temp[10];
	bool krajPrograma = true, krajCiklusa = true;
	
	do
	{
		system("CLS");
		grb();
		header();
		std::cout << "(Da izaberete opciju ukucajte redni broj zeljene opcije.)" << std::endl;
		std::cout << "(Da zatvorite aplikaciju ukucajte ' kraj '.)" << std::endl;
		std::cout << "(Povratak na prethodnu stranu ' 0 '.)" << std::endl;
		footer();
		header();
		std::cout << "SORTIRANJE DOGADJAJA." << std::endl;
		header();
		std::cout << "| 1. Po datumu opadajuce | 2. Po datumu rastuce |" << std::endl;
		std::cout << "| 3. Po nazivu opadajuce | 4. Po nazivu rastuce |" << std::endl;;
		footer();

		krajCiklusa = true;
		while (krajCiklusa)
		{
			std::cout << "Unesite redni broj opcije iz menija:"<<std::endl;
			std::cin >> temp;
			getchar();
			if (temp[0] == '0')
			{
				return true;
			}
			else if (temp[0] == 'k')
			{
				return false;
			}
			else if (1 == atoi(temp))
			{
				
				krajCiklusa = false;
				mojSort(izdvojeniDogajaji, "poDatumuOpadajuce");
				krajPrograma = false;
				
			}
			else if (2 == atoi(temp))
			{

				krajCiklusa = false;
				mojSort(izdvojeniDogajaji, "poDatumuRastuce");
				krajPrograma = false;
			}
			else if (3 == atoi(temp))
			{

				krajCiklusa = false;
				mojSort(izdvojeniDogajaji, "poNazivuOpadajuce");
				krajPrograma = false;
			}
			else if (4 == atoi(temp))
			{

				krajCiklusa = false;
				mojSort(izdvojeniDogajaji, "poNazivuRastuce");
				krajPrograma = false;
			}
			else
			{
					std::cout << "Ne postoji dogadjaj sa ' " << temp << " ' rednim brojem." << std::endl;
					getchar();
			}
		}
	} while (krajPrograma);
	return true;

}

void ListaDogadjaja::prikaziNeodobreneKomentare(std::string nazivDogadjaja)
{
	int indeks = 0,redniBroj;
	std::vector<int> redniBrojevi;
	system("CLS");
	grb();
	header();
	std::cout << "NEODOBRENI KOMENTARI NA DOGADJAJ." << std::endl;
	std::cout << getNaziv(nazivDogadjaja) << std::endl;
	header();

	std::vector<std::string> nizNedobrenih,nizOdobrenih;
	std::vector<std::string> nizKomentara;
	std::string line;

	std::ifstream myfile(convert(getDatum(nazivDogadjaja) + getNaziv(nazivDogadjaja) + "NeodobreniKomentari.txt"));
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			header();
			std::cout<< ++indeks <<". "<< line<<std::endl;
			nizNedobrenih.push_back(line);
			header();
		}
		myfile.close();
	}
	if ((int)nizNedobrenih.size() == 0)
	{
		std::cout << "NEMA NEODOBRENIH KOMENTARA." << std::endl;
		header();
		getchar();
	}
	else
	{
		std::cout << "Redni broj komentara koje zelite odobriti i '0' za kraj." << std::endl;
		std::cin >> redniBroj;
		getchar();
		while (redniBroj && ((int)redniBrojevi.size() <= (int)nizNedobrenih.size()) && (redniBroj > 0 && redniBroj <= (int)nizNedobrenih.size()))
		{
			redniBrojevi.push_back(redniBroj);
			std::cin >> redniBroj;
			getchar();
		}
		if (redniBrojevi.size() != 0)
		{
			std::ifstream myfilekom(convert(getDatum(nazivDogadjaja) + getNaziv(nazivDogadjaja) + "OdobreniKomentari.txt"));
			if (myfilekom.is_open())
			{
				while (getline(myfilekom, line))
				{
					nizKomentara.push_back(line);
				}
				myfile.close();
			}
			while ((int)redniBrojevi.size())
			{
				nizKomentara.push_back(nizNedobrenih[redniBrojevi.back() - 1]);
				redniBrojevi.pop_back();
			}

			remove(convert(getDatum(nazivDogadjaja) + getNaziv(nazivDogadjaja) + "NeodobreniKomentari.txt"));
			std::ofstream myfilepom(convert(getDatum(nazivDogadjaja) + getNaziv(nazivDogadjaja) + "NeodobreniKomentari.txt"));
			if (myfilepom.is_open())
			{
				myfile.close();
			}
			std::ofstream myfileNeKom(convert(getDatum(nazivDogadjaja) + getNaziv(nazivDogadjaja) + "OdobreniKomentari.txt"));
			if (myfileNeKom.is_open())
			{
				for (std::vector<std::string>::iterator it = nizKomentara.begin(); it != nizKomentara.end(); ++it)
					myfileNeKom << *it << std::endl;
				myfile.close();
			}

			for (int i = 0; i < getBrojDogadjaja(); ++i)
			{
				if (nizDogadjaja[i] == nazivDogadjaja)
				{
					setInfoKom(nizDogadjaja[i], '0');
				}
			}
			izmjena = true;
		}
	}

	
}

void ListaDogadjaja::komentarisanjeDogadjaja(std::string nazivDogadjaja)
{

	system("CLS");
	grb();
	header(); 
	std::cout << "(Povratak na prehodnu stranu ' 0 '.)" << std::endl;
	footer();
	std::cout << "KOMENTARI NA DOGADJAJ." << std::endl;
	std::cout << getNaziv(nazivDogadjaja) << std::endl;
	header();

	std::string koment, line;
	std::vector<std::string> nizKomentara,nizOdobreniKomentara;

	std::ifstream myfile(convert(getDatum(nazivDogadjaja) + getNaziv(nazivDogadjaja) + "OdobreniKomentari.txt"));
	if (myfile.is_open())
	{
		int indeks = 0;
		while (getline(myfile, line))
		{
			nizOdobreniKomentara.push_back(line);
			header();
			std::cout << ++indeks << ". " << line << std::endl;
			header();
		}
		myfile.close();
	}

	std::cout << "Vas komentar je :" << std::endl;
	std::getline(std::cin, koment);
	if (koment != "0" && koment != "\n" && koment != " ")
	{
		std::string temp;
		if (admin)
		{
			temp = "OdobreniKomentari.txt";
			nizKomentara = nizOdobreniKomentara;
		}
		else
		{
			temp = "NeodobreniKomentari.txt";
			std::ifstream myfilekom(convert(getDatum(nazivDogadjaja) + getNaziv(nazivDogadjaja) + temp));
			if (myfilekom.is_open())
			{
				while (getline(myfilekom, line))
				{
					nizKomentara.push_back(line);
				}
				myfile.close();
			}
			
			for (int i = 0; i < getBrojDogadjaja(); ++i)
			{
				if (nizDogadjaja[i] == nazivDogadjaja)
				{
					setInfoKom(nizDogadjaja[i], '1');
				}
			}
			izmjena = true;
		}

		nizKomentara.push_back(koment);

		std::ofstream myfileNeKom(convert(getDatum(nazivDogadjaja) + getNaziv(nazivDogadjaja) + temp));
		if (myfileNeKom.is_open())
		{
			for (std::vector<std::string>::iterator it = nizKomentara.begin(); it != nizKomentara.end(); ++it)
				myfileNeKom << *it << std::endl;
			myfile.close();
		}

		
	}
	getchar();
}

bool ListaDogadjaja::prikaziDogadjaj(std::string nazivDogadjaja)
{
	char temp[10];
	bool krajPrograma = true, krajCiklusa = true;
	std::string naslov, kategorija, datumIVrijeme, opis, line;

	std::ifstream myfile(convert(getDatum(nazivDogadjaja) + getNaziv(nazivDogadjaja) + "TekstDogadjaja.txt"));
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			opis.append(line);
		}
		myfile.close();
	}
	else std::cout << "Neuspjesno otvaranje datoteke";

	do
	{
		system("CLS");
		grb();
		header();
		std::cout << "(Da izaberete opciju ukucajte redni broj zeljene opcije.)" << std::endl;
		std::cout << "(Da zatvorite aplikaciju ukucajte ' kraj '.)" << std::endl;
		std::cout << "(Povratak na prethodnu stranu ' 0 '.)" << std::endl;
		footer();
		std::cout << "PRIKAZ DOGADJAJA." << std::endl;
		header();
		std::cout << "| 1. Komentarisanje dogadjaja |" << std::endl;
		footer();
		header();
		std::cout <<"Naslov dogadjaja:          "<< getNaziv(nazivDogadjaja) << std::endl;
		std::cout <<"Datum i vrijeme dogadjaja: " << getDatum(nazivDogadjaja) << std::endl;
		std::cout <<"Kategorija dogadjaja:      " << getKategorijaDogadjaja(nazivDogadjaja) << std::endl;
		header();
		std::cout << opis << std::endl;
		footer();

		krajCiklusa = true;
		while (krajCiklusa)
		{
			std::cin >> temp;
			getchar();
			if (temp[0] == '0')
			{
				return true;
			}
			else if (temp[0] == 'k')
			{
				return false;
			}
			if (1 == atoi(temp))
			{
				krajCiklusa = false;
				komentarisanjeDogadjaja(nazivDogadjaja);
			}
			else
			{
				std::cout << "Ne postoji dogadjaj sa ' " << temp << " ' rednim brojem." << std::endl;
				getchar();
			}
		}

	} while (krajPrograma);
	return true;
}

bool ListaDogadjaja::pregledZeljenihDogadjaja(int uslov)
{
	char temp[10];
	bool krajPrograma = true, krajCiklusa = true;
	std::vector<std::string> izdvojeniDogajaji;

	for (int i = 0; i < (int)nizDogadjaja.size(); ++i)
	{
		if (uporediDatume(getDatum(nizDogadjaja[i]), datum) == uslov)
		{
			izdvojeniDogajaji.push_back(nizDogadjaja[i]);
		}
	}
	if ((int)izdvojeniDogajaji.size() == 0)
	{
		header();
		if (uslov == 0) std::cout << "NEMA DANASNJIH DOGADJAJA." << std::endl;
		else if (uslov == 1) std::cout << "NEMA BUDUCIH DOGADJAJA." << std::endl;
		else std::cout << "NEMA PROSLIH DOGADJAJA." << std::endl;
		header();
		getchar();
		return true;
	}

	do
	{
		system("CLS");
		grb();
		header();
		std::cout << "(Da izaberete opciju ukucajte redni broj zeljene opcije.)" << std::endl;
		std::cout << "(Da zatvorite aplikaciju ukucajte ' kraj '.)" << std::endl;
		std::cout << "(Povratak na prethodnu stranu ' 0 '.)" << std::endl;
		std::cout << "(Sortiranje dogadjaja ' s '.)" << std::endl;
		footer();
		header();
		if (uslov == 0) std::cout << "PREGLED DANASNJIH DOGADJAJA." << std::endl;
		else if (uslov == 1) std::cout << "PREGLED BUDUCIH DOGADJAJA." << std::endl;
		else std::cout << "PREGLED PROSLIH DOGADJAJA." << std::endl;
		header();
		for (int i = 0; i < (int)izdvojeniDogajaji.size(); ++i)
		{
			std::cout << i + 1 << ". " << getNaziv(izdvojeniDogajaji[i]) << std::endl;
		}
		footer();

		krajCiklusa = true;
		while (krajCiklusa)
		{
			std::cout << "Unesite redni broj dogadjaja koji zelite pogledati: "<<std::endl;

			std::cin >> temp;
			getchar();
			if (temp[0] == '0')
			{
				return true;
			}
			else if (temp[0] == 'k')
			{
				return false;
			}
			else if (temp[0] == 's')
			{
				krajCiklusa = false;
				krajPrograma = sortirajDogadjaje(izdvojeniDogajaji);
			}
			else
			{

				if (atoi(temp)-1 >= 0 && atoi(temp)-1 < (int)izdvojeniDogajaji.size())
				{
					krajCiklusa = false;
					krajPrograma = prikaziDogadjaj(izdvojeniDogajaji[atoi(temp)-1]);
				}
				else
				{
					std::cout << "Ne postoji dogadjaj sa ' " << temp << " ' rednim brojem." << std::endl;
					getchar();
				}

			}
		}
	} while (krajPrograma);
	return false;
}

bool ListaDogadjaja::pregledDogadjajaOdredjeneKategorije()
{
	char temp[10],rbKat[10];
	bool krajPrograma = true, krajCiklusa = true, ponovi = true, prviKrajCiklusa = true;
	Kategorije kategorije;
	std::vector<std::string> izdvojeniDogajaji;

	do
	{
		system("CLS");
		grb();
		header();
		std::cout << "(Da izaberete opciju ukucajte redni broj zeljene opcije.)" << std::endl;
		std::cout << "(Da zatvorite aplikaciju ukucajte ' kraj '.)" << std::endl;
		std::cout << "(Povratak na prethodnu stranu ' 0 '.)" << std::endl;
		footer();
		header();
		std::cout << "PREGLED DOGADJAJA ODREDJENE KATEGORIJE." << std::endl;
		header();
		std::cout << kategorije;
		footer();

		while (prviKrajCiklusa)
		{
			std::cout << "Unesite redni broj kategorije:" << std::endl;
			std::cin >> rbKat; 
			getchar();
			if (rbKat[0] == '0')
			{
				return true;
			}
			else if (rbKat[0] == 'k')
			{
				return false;
			}
			else if (atoi(rbKat)-1 >= 0 && atoi(rbKat)-1 < kategorije.getBrojKategorija())
			{
				izdvojeniDogajaji.clear();
				for (int i = 0; i < (int)nizDogadjaja.size(); ++i)
				{
					if (getKategorijaDogadjaja(nizDogadjaja[i]) == kategorije.getKategorija(atoi(rbKat)-1))
					{
						izdvojeniDogajaji.push_back(nizDogadjaja[i]);
					}
				}
				if ((int)izdvojeniDogajaji.size() == 0)
				{
					std::cout << "NEMA DOGADJAJA IZABRANE KATEGORIJE." << std::endl;
				}
				else
				{
					prviKrajCiklusa = false;
					ponovi = true;
				}
			}
			else
			{
				std::cout << "Ne postoji kategorija sa ' " << rbKat << " ' rednim brojem." << std::endl;
				getchar();
			}
		}

		
		while (ponovi)
		{
			system("CLS");
			grb();
			header();
			std::cout << "(Da izaberete opciju ukucajte redni broj zeljene opcije.)" << std::endl;
			std::cout << "(Da zatvorite aplikaciju ukucajte ' kraj '.)" << std::endl;
			std::cout << "(Povratak na prethodnu stranu ' 0 '.)" << std::endl;
			std::cout << "(Sortiranje dogadjaja ' s '.)" << std::endl;
			footer();
			header();
			std::cout << "PREGLED DOGADJAJA " << kategorije.getKategorija(atoi(rbKat)-1) << " KATEGORIJE." << std::endl;
			header();
			for (int i = 0; i < (int)izdvojeniDogajaji.size(); ++i)
			{
				std::cout << i + 1 << ". " << getNaziv(izdvojeniDogajaji[i]) << std::endl;
			}
			footer();

			
			krajCiklusa = true;
			while (krajCiklusa)
			{
				std::cout << "Unesite redni broj dogadjaja koji zelite pogledati:" << std::endl;
				std::cin >> temp;
				getchar();
				if (temp[0] == '0')
				{
					krajPrograma= true;
					prviKrajCiklusa = true;
					krajCiklusa = false;
					ponovi = false;
				}
				else if (temp[0] == 'k')
				{
					return false;
				}
				else if (temp[0] == 's')
				{
					krajCiklusa = false;
					ponovi = sortirajDogadjaje(izdvojeniDogajaji);
					krajPrograma = ponovi;
				}
				else
				{

					if (atoi(temp)-1 >= 0 && atoi(temp)-1 < (int)izdvojeniDogajaji.size())
					{
						krajCiklusa = false;
						ponovi = prikaziDogadjaj(izdvojeniDogajaji[atoi(temp)-1]);
						krajPrograma = ponovi;
					}
					else
					{
						std::cout << "Ne postoji dogadjaj sa ' " << temp << " ' rednim brojem." << std::endl;
						getchar();
					}

				}
			}
		}
	} while (krajPrograma);
	return false;
}

int ListaDogadjaja::getBrojDogadjaja()
{
	return nizDogadjaja.size();
}

void ListaDogadjaja::obrisiDogadjaj(int redniBroj)
{
	remove(convert(getDatum(nizDogadjaja[redniBroj]) + getNaziv(nizDogadjaja[redniBroj]) + "OdobreniKomentari.txt"));
	remove(convert(getDatum(nizDogadjaja[redniBroj]) + getNaziv(nizDogadjaja[redniBroj]) + "NeodobreniKomentari.txt"));
	remove(convert(getDatum(nizDogadjaja[redniBroj]) + getNaziv(nizDogadjaja[redniBroj]) + "TekstDogadjaja.txt"));

	nizDogadjaja.erase(nizDogadjaja.begin()+redniBroj);

	izmjena = true;
}

bool ListaDogadjaja::kreirajIliIzmjeniDogadjaj(std::string uslov, int redniBrojDogadjajaZaIzmjenu)
{
	izmjena = true;
	char temp[10];
	bool krajPrograma = true, krajCiklusa = true, naslovBool = false, kategorijaBool = false, opisBool = false, datumIVrijemeBool = false, ispravnostDatuma = true;
	std::string naslov, kategorija, opis, datumIVrijeme, infoKom,line;

	if (uslov == "izmjeni")
	{
		naslov = getNaziv(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]);
		kategorija = getKategorijaDogadjaja(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]);
		datumIVrijeme = getDatum(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]);
		infoKom = getInfoKom(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]);

		std::ifstream myfile(convert(getDatum(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) + getNaziv(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) + "TekstDogadjaja.txt"));
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				opis.append(line);
			}
			myfile.close();
		}
		else std::cout << "Neuspjesno otvaranje datoteke";
	}
	do
	{
		system("CLS");
		grb();
		header();
		std::cout << "(Da izaberete opciju ukucajte redni broj zeljene opcije.)" << std::endl;
		std::cout << "(Da zatvorite aplikaciju ukucajte ' kraj '.)" << std::endl;
		std::cout << "(Povratak na prethodnu stranu ' 0 '.)" << std::endl;
		footer();
		header();
		if (uslov == "izmjeni") std::cout << "IZMJENA DOGADJAJA." << std::endl;
		else if (uslov == "kreiraj") std::cout << "KREIRANJE DOGADJAJA." << std::endl;
		header();
		std::cout << "| 1. Naslov | 2. Kategorija      |" << std::endl;
		std::cout << "| 3. Opis   | 4. Datum i vrijeme |" << std::endl;;
		footer();
		krajCiklusa = true;
		while (krajCiklusa)
		{
			std::cout << "Unesite redni broj opcije iz menija:" << std::endl;
			std::cin >> temp;
			getchar();
			footer();
			if (temp[0] == '0')
			{
				return true;
			}
			else if (temp[0] == 'k')
			{
				return false;
			}
			else if (1 == atoi(temp))
			{
				naslovBool = true;
				krajCiklusa = false;
				if (uslov == "izmjeni")
				{
					std::cout << "Naslov je :" << getNaziv(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) << std::endl;
					std::cout << "Novi naslov je :" << std::endl;
				}
				else if (uslov == "kreiraj")
				{
					std::cout << "Naslov je :" << std::endl;
				}
				std::getline(std::cin, naslov);

			}
			else if (2 == atoi(temp))
			{
				kategorijaBool = true;
				int redniBroj;
				Kategorije kate;
				std::cout << kate;
				if (uslov == "izmjeni")
				{
					std::cout << "Stara kategorija je :" << getKategorijaDogadjaja(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) << std::endl;
					std::cout << "Izaberi novu kategoriju ili dodaj novu '0' " << std::endl;
				}
				else if (uslov == "kreiraj")
				{
					std::cout << "Izaberi kategoriju ili dodaj novu '0' " << std::endl;
				}
				std::cin >> redniBroj;
				getchar();
				if (redniBroj - 1 >= 0 && redniBroj - 1 <= kate.getBrojKategorija())
				{
					kategorija = kate.getKategorija(redniBroj - 1);
				}
				else if (redniBroj == 0)
				{
					std::cout << "Kategorija :" << std::endl;
					std::cin >> kategorija;
					getchar();
					kate.dodajKategoriju(kategorija);
				}
				else
				{
					std::cout << "Ne postoji kategorija sa ' " << redniBroj << " ' rednim brojem." << std::endl;
					getchar();
				}

				krajCiklusa = false;
			}
			else if (3 == atoi(temp))
			{
				opisBool = true;
				krajCiklusa = false;
				if (uslov == "izmjeni")
				{
					std::cout << "Stara opis je :" << std::endl << opis << std::endl;
					std::cout << "Novi opis: " << std::endl;
				}
				else if (uslov == "kreiraj")
				{
					std::cout << "Opis: " << std::endl;
				}
				std::getline(std::cin, opis);

			}
			else if (4 == atoi(temp))
			{
				if (uslov == "izmjeni") std::cout << "Stari datum i vrijeme su " << getDatum(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) << std::endl;
				do
				{
					if(!ispravnostDatuma)
						std::cout << "Greska. Datum nije u formatu dd.mm.gggg ss.mm" << std::endl;
					datumIVrijemeBool = true;
					krajCiklusa = false;
					std::cout << "Datum i vrijeme u formatu dd.mm.gggg ss.mm" << std::endl;
					std::getline(std::cin, datumIVrijeme);
					ispravnostDatuma = provjeriDatum(datumIVrijeme);
				} while (!ispravnostDatuma);

			}
			else
			{
				std::cout << "Ne postoji dogadjaj sa ' " << temp << " ' rednim brojem." << std::endl;
				getchar();
			}
			if ((uslov == "izmjeni") && (naslovBool || kategorijaBool || opisBool || datumIVrijemeBool))
			{

				rename(convert(getDatum(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) + getNaziv(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) + "OdobreniKomentari.txt"), convert(datumIVrijeme + naslov + "OdobreniKomentari.txt"));
				rename(convert(getDatum(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) + getNaziv(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) + "NeodobreniKomentari.txt"), convert(datumIVrijeme + naslov + "NeodobreniKomentari.txt"));
				rename(convert(getDatum(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) + getNaziv(nizDogadjaja[redniBrojDogadjajaZaIzmjenu]) + "TekstDogadjaja.txt"), convert(datumIVrijeme + naslov + "TekstDogadjaja.txt"));

				std::ofstream myfile(convert(datumIVrijeme + naslov + "TekstDogadjaja.txt"));
				if (myfile.is_open())
				{
					myfile << opis;
					myfile.close();
				}
				else std::cout << "Neuspjesno otvaranje datoteke";

				nizDogadjaja[redniBrojDogadjajaZaIzmjenu] = datumIVrijeme + naslov + "|" + kategorija + "|" + infoKom + "|";
				krajPrograma = false;
				std::cout << "Dogadjaj izmjenjen." << std::endl;
				getchar();

			}
			if ((uslov == "kreiraj") && (naslovBool && kategorijaBool && opisBool && datumIVrijemeBool))
			{
				std::ofstream myfile(convert(datumIVrijeme + naslov + "TekstDogadjaja.txt"));
				if (myfile.is_open())
				{
					myfile << opis;
					myfile.close();
				}
				std::ofstream myfile1(convert(datumIVrijeme + naslov + "OdobreniKomentari.txt"));
				if (myfile1.is_open())
				{
					myfile1.close();
				}
				std::ofstream myfile2(convert(datumIVrijeme + naslov + "NeodobreniKomentari.txt"));
				if (myfile2.is_open())
				{
					myfile2.close();
				}

				nizDogadjaja.push_back(datumIVrijeme + naslov + "|" + kategorija + "|" + "0" + "|");
				krajPrograma = false;
				std::cout << "Dogadjaj sacuvan." << std::endl;
				getchar();
			}

		}

	} while (krajPrograma);
	return true;
}
