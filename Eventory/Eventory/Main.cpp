#include"KorisnickiNalozi.h"
#include"Dogadjaji.h"
#include"Kviz.h"
#include"InformacijeOGradu.h"
#include<iostream>

bool pokreniSistem(int uslov);
void ispisiMeni(int uslov);

int main()
{
	srand((unsigned int)time(nullptr));
	char temp;
	bool krajPrograma = true, krajCiklusa = true;

	do
	{
		system("CLS");
		grb();
		header();
		std::cout << "(Da izaberete opciju utkucajte redni broj zeljene opcije.)" << std::endl;
		std::cout << "(Da zatvorite aplikaciju utkucajte ' kraj '.)" << std::endl;
		footer();
		header();
		std::cout << "Pristupi sistemu kao:\n| 1. Administrator | 2. Gost |" << std::endl;
		footer();

		krajCiklusa = true;
		while (krajCiklusa)
		{
			std::cin >> temp;
			getchar();

			switch (temp)
			{
			case '1':
			{
				std::string ime = ucitajKorisnickoIme();
				KorisnickiNalozi korisnik(ucitajLozinku(ime), ime);
				if (!korisnik.daliPostojiNalog())
				{
					system("CLS");
					grb();
					header();
					std::cout << "(Da izaberete opciju utkucajte redni broj zeljene opcije.)" << std::endl;
					footer();
					header();
					std::cout << "Ne postoji korisnicki nalog ' " << korisnik.getKorisnickoIme() << " ' ili je pogresna lozinka." << std::endl;
					std::cout << "| 1. Probaj ponovo | 2. Zatvori aplikaciju |" << std::endl;
					footer();

					while (krajCiklusa)
					{
						std::cin >> temp;
						getchar();
						if (temp == '1')
						{
							krajCiklusa = false;
						}
						else if (temp == '2')
						{
							krajPrograma = false;
							krajCiklusa = false;
						}
						else
						{
							std::cout << "Ne postoji opcija ' " << temp << " ' u meniju." << std::endl;
						}
					}
				}
				else
				{
					krajCiklusa = false;
					krajPrograma = pokreniSistem(1);
				}
			}
			break;
			case '2':
			{
				krajCiklusa = false;
				krajPrograma = pokreniSistem(0);
			}
			break;
			default:
			{
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
		}
	} while (krajPrograma);
}

bool pokreniSistem(int uslov)
{
	char temp;
	bool krajPrograma = true, krajCiklusa = true;
	Dogadjaji dogadjaji;
	if (uslov == 1)	dogadjaji.setAdminInfo(true);

	do
	{
		system("CLS");
		grb();
		header();
		std::cout << "(Da izaberete opciju utkucajte redni broj zeljene opcije.)" << std::endl;
		std::cout << "(Da zatvorite aplikaciju utkucajte ' kraj '.)" << std::endl;
		std::cout << "(Povratak na prehodnu stranu ' 0 '.)" << std::endl;
		footer();
		header();
		if (uslov == 1) std::cout << "PRIJAVLJENI STE KAO ADMINISTRATOR." << std::endl;
		else std::cout << "PRIJAVLJENI STE KAO GOST." << std::endl;
		footer();

		ispisiMeni(uslov);

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
				krajPrograma = dogadjaji.pregledDogadjaja();
			}
			break;
			case '2':
			{
				krajCiklusa = false;
				krajPrograma = dogadjaji.filtriranjeDogadjaja();
			}
			break;
			case '3':
			{
				system("CLS");
				grb();
				krajCiklusa = false;
				Kviz kviz;
				kviz.pokreniKviz();
				getchar();
			}
			break;
			case '4':
			{
				system("CLS");
				grb();
				krajCiklusa = false;
				InformacijeOGradu info;
				std::cout << info;
				getchar();
			}
			break;
			case '5':
				if (uslov)
				{
					krajCiklusa = false;
					krajPrograma = dogadjaji.kreiranjeDogadjaja();
				}
				else
				{
					std::cout << "Ne postoji opcija ' " << temp << " ' u meniju." << std::endl;
				}
				break;
			case '6':
				if (uslov)
				{
					krajCiklusa = false;
					krajPrograma = dogadjaji.brisanjeDogadjaja();
				}
				else
				{
					std::cout << "Ne postoji opcija ' " << temp << " ' u meniju." << std::endl;
				}
				break;
			case '7':
				if (uslov)
				{
					krajCiklusa = false;
					krajPrograma = dogadjaji.izmjenaDogadjaja();
				}
				else
				{
					std::cout << "Ne postoji opcija ' " << temp << " ' u meniju." << std::endl;
				}
				break;
			case '8':
				if (uslov)
				{
					krajCiklusa = false;
					krajPrograma = dogadjaji.odobravanjeKomentara();
				}
				else
				{
					std::cout << "Ne postoji opcija ' " << temp << " ' u meniju." << std::endl;
				}
				break;
			case '9':
				if (uslov)
				{
					krajCiklusa = false;
					krajPrograma = dogadjaji.izmjenaKategorija();
				}
				else
				{
					std::cout << "Ne postoji opcija ' " << temp << " ' u meniju." << std::endl;
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

void ispisiMeni(int uslov)
{
	header();
	std::cout << R"(
					 _____  _       ___  _   _ _   _ _____       ___  ___ _____ _   _ _____ 
					|  __ \| |     / _ \| | | | \ | |_   _|      |  \/  ||  ___| \ | |_   _|
					| |  \/| |    / /_\ \ | | |  \| | | |        | .  . || |__ |  \| | | |  
					| | __ | |    |  _  | | | | . ` | | |        | |\/| ||  __|| . ` | | |  
					| |_\ \| |____| | | \ \_/ / |\  |_| |_       | |  | || |___| |\  |_| |_ 
					 \____/\_____/\_| |_/\___/\_| \_/\___/       \_|  |_/\____/\_| \_/\___/ 				 
)" << std::endl;
	footer();
	header();

	if (uslov == 1)
	{
		std::cout << "| 1. Pregled dogadjaja   | 2. Filtriranje dogadjaja | 3. Igranje kviza o gradu | 4. Informacije o gradu   |" << std::endl;
		std::cout << "| 5. Kreiranje dogadjaja | 6. Brisanje dogadjaja    | 7. Izmjena dogadjaja     | 8. Odobravanje komentara |" << std::endl;
		std::cout << "| 9. Izmjena kategorija  |                          |                          |                          |" << std::endl;
	}
	else
	{
		std::cout << "| 1. Pregled dogadjaja | 2. Filtriranje dogadjaja | 3. Igranje kviza o gradu | 4. Informacije o gradu |" << std::endl;
	}
	footer();
}