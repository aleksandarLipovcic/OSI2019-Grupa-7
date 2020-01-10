#include "Dogadjaji.h"

Dogadjaji::Dogadjaji()
{
	ListaDogadjaja();
}

Dogadjaji::~Dogadjaji()
{
}

bool Dogadjaji::pregledDogadjaja()
{
	char temp;
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
		std::cout << "PREGLED DOGADJAJA." << std::endl;
		header();
		std::cout << "| 1. Pregled danasnjih dogadjaja            | 2. Pregled buducih dogadjaja |" << std::endl;
		std::cout << "| 3. Pregled dogadjaja odredjene kategorije | 4. Pregled proslih dogadjaja |" << std::endl;;
		footer();

		krajCiklusa = true;

		while (krajCiklusa)
		{
			std::cin >> temp;
			getchar();
			switch (temp)
			{
			case '0':
			{
				return true;
			}
			break;
			case '1':
			{
				krajCiklusa = false;
				krajPrograma = lista.pregledZeljenihDogadjaja(0);
			}
			break;
			case '2':
			{
				krajCiklusa = false;
				krajPrograma = lista.pregledZeljenihDogadjaja(1);
			}
			break;
			case '3':
			{
				krajCiklusa = false;
				krajPrograma = lista.pregledDogadjajaOdredjeneKategorije();
			}
			break;
			case '4':
			{
				krajCiklusa = false;
				krajPrograma = lista.pregledZeljenihDogadjaja(2);
			}
			break;
			default:
				if (temp == 'k')
				{
					return false;
				}
				else
				{
					std::cout << "Ne postoji opcija ' " << temp << " ' u meniju." << std::endl;
				}
			}
		}
	} while (krajPrograma);
	return false;
}

bool Dogadjaji::filtriranjeDogadjaja()
{
	return sablon("filtriranje");
}

bool Dogadjaji::kreiranjeDogadjaja()
{
	return lista.kreirajIliIzmjeniDogadjaj("kreiraj",0);
}

bool Dogadjaji::brisanjeDogadjaja()
{
	return sablon("brisanje");
}

bool Dogadjaji::izmjenaDogadjaja()
{
	return sablon("izmjena");
}

bool Dogadjaji::odobravanjeKomentara()
{
	return sablon("odobravanje");
}

bool Dogadjaji::izmjenaKategorija()
{
	char temp;
	bool krajPrograma = true, krajCiklusa = true;
	Kategorije kategorije;

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
		std::cout << "IZMJENA KATEGORIJA.'"<<std::endl;
		std::cout << "| 1. Dodaj kategoriju | 2.Obrisi kategoriju |"<<std::endl;
		header();
		std::cout << kategorije;
		footer();

		krajCiklusa = true;
		while (krajCiklusa)
		{
			std::cin >> temp;
			getchar();
			switch (temp)
			{
			case '0':
			{
				return true;
			}
			break;
			case '1':
			{
				krajCiklusa = false;
				std::string line;
				std::cout << "Nova kategorija je: ";
				std::cin >> line;
				getchar();
				kategorije.dodajKategoriju(line);
			}
			break;
			case '2':
			{
				krajCiklusa = false;
				std::cout << "Unesite redni broj kategorije koju zelite obrisati: ";
				int redniBroj;
				std::cin >> redniBroj;
				getchar();
				if (redniBroj-1 >= 0 && redniBroj-1 <= kategorije.getBrojKategorija())
				{
					kategorije.obrisiKategoriju(redniBroj-1);
				}
				else
				{
					std::cout << "Ne postoji kategorija sa ' " << redniBroj<< " ' rednim brojem." << std::endl;
					getchar();
				}
			}
			break;
			default:
				if (temp == 'k')
				{
					krajCiklusa = false;
					krajPrograma = false;
				}
				else
				{
					std::cout << "Ne postoji opcija ' " << temp << " ' u meniju." << std::endl;
				}
			}
		}
	} while (krajPrograma);
	kategorije.~Kategorije();
	return false;
}

bool Dogadjaji::sablon(std::string uslov)
{

	char temp[10];
	bool krajPrograma = true, krajCiklusa = true;
	
	std::string string;

	do
	{
		std::vector<std::string> izdvojeniDogajaji;
		system("CLS");
		grb();
		header();
		std::cout << "(Da izaberete opciju ukucajte redni broj zeljene opcije.)" << std::endl;
		std::cout << "(Da zatvorite aplikaciju ukucajte ' kraj '.)" << std::endl;
		std::cout << "(Povratak na prethodnu stranu ' 0 '.)" << std::endl;
		footer();
		header();
		if (uslov == "brisanje")
		{
			std::cout << "BRISANJE DOGADJAJA." << std::endl;
			header();
			std::cout << lista;
			if (lista.getBrojDogadjaja() == 0)
			{
				std::cout << "NEMA DOGADJAJA." << std::endl;
				header();
				getchar();
				return true;
			}

		}
		else if (uslov == "izmjena")
		{
			std::cout << "IZMJENA DOGADJAJA." << std::endl;
			header();
			std::cout << lista;
			if (lista.getBrojDogadjaja() == 0)
			{
				std::cout << "NEMA DOGADJAJA." << std::endl;
				header();
				getchar();
				return true;
			}

		}
		else if (uslov == "odobravanje")
		{
			lista.izdvojiSaNeodobrenimKomentarima(izdvojeniDogajaji);
			std::cout << "PREGLED DOGADJAJA SA NEODOBRENIM KOMENTARIMA." << std::endl;
			header();
			for (int i = 0; i < (int)izdvojeniDogajaji.size(); ++i)
			{
				std::string temp;
				temp.append(izdvojeniDogajaji[i], 16, izdvojeniDogajaji[i].find_first_of("|") - 16);
				std::cout << i + 1 << ". " << temp<< std::endl;
			}
			if ((int)izdvojeniDogajaji.size() == 0)
			{
				std::cout << "NEMA DOGADJAJA SA NEODOBRENIM KOMENTARIMA." << std::endl;
				header();
				getchar();
				return true;
			}

		}
		else if (uslov == "filtriranje")
		{
			std::cout << "FILTRIRANJE DOGADJAJA." << std::endl;
			header();
			std::cout << "| 1. Filtriraj po nazivu | 2. Filtriraj po datumu |" << std::endl;

		}
		footer();

		krajCiklusa = true;
		while (krajCiklusa)
		{
			if (uslov == "brisanje") std::cout << "Unesite redni broj dogadjaja koji zelite obrisati:" << std::endl;
			else if (uslov == "izmjena") std::cout << "Unesite redni broj dogadjaja koji zelite izmjeniti:" << std::endl;
			else if (uslov == "odobravanje")std::cout << "Unesite redni broj dogadjaja cije komentare zelite pogledati: " << std::endl;

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
			else if (atoi(temp) == 1 && uslov == "filtriranje" )
			{
				std::cout << "Unesite naziv dogadjaja: " << std::endl;
				std::getline(std::cin, string);
				krajCiklusa = false;
				krajPrograma = lista.pregledDogadjajaPo(string,"naziv");
			}
			else if (atoi(temp) == 2 && uslov == "filtriranje" )
			{
				do
				{
					std::cout << "Unesite interval datuma u formatu (dd.mm.gggg dd.mm.gggg) " << std::endl;
					std::getline(std::cin, string);
				} while (!((int)string.size() == 21));
				
				krajCiklusa = false;
				krajPrograma = lista.pregledDogadjajaPo(string,"datum");
			}
			else
			{

				if (!(uslov == "filtriranje") && (atoi(temp) - 1 >= 0 && atoi(temp) - 1 < lista.getBrojDogadjaja()))
				{
					krajCiklusa = false;
					if (uslov == "brisanje")
					{
						lista.obrisiDogadjaj(atoi(temp) - 1);
						std::cout << "Dogajaj je obrisan.";
						getchar();
					}
					else if (uslov == "izmjena")
					{
						lista.kreirajIliIzmjeniDogadjaj("izmjeni",atoi(temp) - 1);
					}
					else if (uslov == "odobravanje")
					{
						lista.prikaziNeodobreneKomentare(izdvojeniDogajaji[atoi(temp) - 1]);
					}
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

void Dogadjaji::setAdminInfo(bool uslov)
{
	lista.setAdminInfo(uslov);
}
