#include "Nalog.h"

namespace OSI {
	Nalog::Nalog()
	{
		password = string();
		username = string();

		//prilikom prvog pokretanja da napravi datoteku LoginInfo.txt ako ne postoji
		fstream korisnici;
		korisnici.open("LoginInfo.txt", ios::app);
		korisnici.close();
	}
	Nalog::Nalog(const Nalog& other)
	{
		copy(other);
	}
	Nalog::Nalog(Nalog&& other)
	{
		move(std::move(other));
	}
	Nalog::~Nalog()
	{
		del();
	}

	Nalog& Nalog::operator=(const Nalog& other)
	{
		if (this == &other)
			return*this;
		del();
		copy(other);
		return *this;
	}
	Nalog& Nalog::operator=(Nalog&& other)
	{
		if (this == &other)
			return*this;
		del();
		move(std::move(other));
		return *this;
	}

	string Nalog::getUsername()
	{
		return this->username;
	}
	void Nalog::setUsername(string username)
	{
		this->username = username;
	}
	string Nalog::getPassword()
	{
		return this->password;
	}
	void Nalog::setPassword(string password)
	{
		this->password = password;
	}

	void Nalog::copy(const Nalog& other)
	{
		password = string(other.password);
		username = string(other.username);
	}
	void Nalog::move(Nalog&& other)
	{
		password = string(other.password);
		username = string(other.username);
		other.del();
	}
	void Nalog::del()
	{
		this->username.clear();
		this->password.clear();
	}
	//vraca true ako je unesen validan i korektan username
	bool Nalog::enterUsername()
	{
		//validno znaci da koristi samo slova,brojeve i znak razmaka
		//korektno znaci da je jedinstveno 
		bool isValid = true, isCorrect = true;
		//pomocne promenljive
		char c;
		int br = 0;
		char pomUser[30];
		string pomstring;
		//unosenje zeljenog korisnickog imena u pomocni string
		cout << "Unesite Username (Mora biti jedinstven i moze samo sadrzati slova,brojeve i znak razmaka. Max 30 karaktera.)\n";
		cin.getline(pomUser, 30);
		pomstring = string(pomUser);
		while (br < pomstring.length()) {
			c = pomstring[br];
			if (isValid == true) {
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 32) {
					isValid = true;
				}
				else {
					isValid = false;
				}
			}
			br++;
		}
		//ako je zeljeno ime validno bice izabrano i stavljeno parametar 'username'
		if (isValid) {
			setUsername(pomstring);
		}
		//otvaranje datoteke i pamcenje duzine
		ifstream korisnici;
		korisnici.open("LoginInfo.txt");
		korisnici.seekg(0, korisnici.end);
		int length = korisnici.tellg();
		korisnici.seekg(0, korisnici.beg);
		//ako je zeljeni username validan provjerava se korektnost
		char pomchar[61];
		pomstring.clear();
		if (isValid) {
			while (korisnici.tellg() < length) {
				korisnici.getline(pomchar, 61);
				pomstring = string(pomchar);
				size_t lokacija = pomstring.find("$");
				pomstring.erase(lokacija, pomstring.size());
				if (pomstring.compare(username) == 0) {
					isCorrect = false;
					break;
				}
				for (int i = 0; i < 61; i++) {
					pomchar[i] = 0;
				}
			}
		}
		//zatvaranje datoteke, ispis odgovarajuce poruke i 
		//vracanje bool vrednosti da li je uspjesno izabran username ili ne
		korisnici.close();
		if (isValid && isCorrect) {
			return true;
		}
		if (!isValid) {
			cout << "Username nije validan!\n";
			return false;
		}
		cout << "Username vec postoji!\n";
		return false;
	}
	//vraca true ako je unesen validan pasvord koji je odgovarajuce duzine
	bool Nalog::enterPassword()
	{
		//pomocne promenljive,tooBig znaci da je pasword predugacak
		char c;
		bool isValid = true, tooBig = false;
		int br = 0;
		//unosenje zeljenog pasvorda i provjera da li je zadovoljava uslove validnosti i velicine
		cout << "Unesite Password (Moze samo sadrzati slova,brojeve i znak razmaka. Max 30 karaktera i nema brisanja.)\n";
		c = _getch();
		while (c != 13 && br < 30) {
			if (isValid == true) {
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 32) {
					isValid = true;
					password.push_back(c);
					cout << '*';
				}
				else {
					isValid = false;
				}
			}
			if (br == 29) {
				tooBig = true;
			}
			c = _getch();
			br++;
		}
		//ispis odgovarajuce poruke i vracanje bool vrijednosti
		//da li je uspjesno unesen pasvord
		if (tooBig) {
			cout << "\nPassword predugacak!\n";
		}
		if (!isValid) {
			cout << "\nPassword nije validan!\n";
		}
		if (tooBig) {
			isValid = false;
		}
		return isValid;
	}
	//isto sve kao i enterUsername samo sto ne provjerava korektnost vec samo validnost
	bool Nalog::checkUsername()
	{
		char c;
		bool isValid = true;
		char pomUser[30];
		string pomstring;
		int br = 0;
		cout << "Unesite vas Username:";
		cin.getline(pomUser, 30);
		pomstring = string(pomUser);
		while (br < pomstring.length()) {
			c = pomstring[br];
			if (isValid == true) {
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 32) {
					isValid = true;
				}
				else {
					isValid = false;
				}
			}
			br++;
		}
		if (isValid) {
			setUsername(pomstring);
		}
		if (!isValid) {
			cout << "Username nije validan!\n";
		}
		return isValid;
	}
	//isto sve kao i enterPassword ali ne provjerava duzinu pasvorda
	bool Nalog::checkPassword()
	{
		char c;
		bool isValid = true;
		cout << "Unesite vas Password:";
		c = _getch();
		while (c != 13) {
			if (isValid == true) {
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 32) {
					isValid = true;
					password.push_back(c);
					cout << '*';
				}
				else {
					isValid = false;
				}
			}
			c = _getch();
		}
		cout << "\n";
		if (!isValid) {
			cout << "Password nije validan!\n";
		}
		return isValid;
	}
	//ukoliko je sve uneseno kako treba setuje username i password parametar 
	//tekuceg objekta i upisuje u datoteku 'LoginInfo.txt' informacije o korisniku
	//u formatu Username$Password\n na kraj datoteke.
	//u suprotnom nista od gore navedenog nije izvrseno
	void Nalog::createAcc()
	{
		//pomocne promenljive
		int br = 3;
		bool isValid = true;
		//ponavljanje unosenje zeljenog korisnickog imena maksimalno 3 puta
		cout << "Unosenje za username ili password rijec 'QUIT' ce zavrsiti izvrsavanje trenutne radnje.\n";
		username.clear();
		while (br > 0) {
			isValid = enterUsername();
			if (username.compare("QUIT") == 0) {
				username.clear();
				cout << "Nasilan izlazak!\n";
				return;
			}
			if (!isValid) {
				username.clear();
				br--;
				if (br != 0) {
					cout << "Imate jos " << br << " pokusaja!\n";
				}
			}
			else {
				break;
			}
		}
		if (!isValid) {
			cout << "Moras poceti ispocetka.\n";
			return;
		}
		//ponavljanje unosenja zeljenog pasvorda maksimalno 3 puta
		br = 3;
		password.clear();
		while (br > 0) {
			isValid = enterPassword();
			if (password.compare("QUIT") == 0) {
				username.clear();
				password.clear();
				cout << "Nasilan izlazak!\n";
				return;
			}
			if (!isValid) {
				password.clear();
				br--;
				if (br != 0) {
					cout << "Imate jos " << br << " pokusaja!\n";
				}
			}
			else {
				break;
			}
		}
		if (!isValid) {
			cout << "Moras poceti ispocetka.\n";
			return;
		}
		//otvaranje datoteke,pisanje u nju i zatvaranje
		fstream korisnici;
		korisnici.open("LoginInfo.txt", ios::app);
		korisnici << username << "$" << password << "\n";
		korisnici.close();
	}
	//ukoliko je sve uneseno kako treba setuje username i password parametar
	//tekuceg objekta i vraca true, koje oznacava usjesan Login
	//u suprotnom vraca false
	bool Nalog::loging()
	{
		//pomocne promjenljive
		bool isValid = true, isCorrect = false;
		char pomchar[61], tempUchar[30], tempPchar[30];
		string pomstring, tempUstring, tempPstring;
		int br = 3;
		//ponavljanje unosenja odgovarajuceg korisnickog imena maksimalno 3 puta
		cout << "Unosenje za username ili password rijec 'QUIT' ce zavrsiti izvrsavanje trenutne radnje.\n";
		username.clear();
		while (br > 0) {
			isValid = checkUsername();
			if (username.compare("QUIT") == 0) {
				username.clear();
				cout << "Nasilan izlazak!\n";
				return false;
			}
			if (!isValid) {
				username.clear();
				br--;
				if (br != 0) {
					cout << "Imate jos " << br << " pokusaja!\n";
				}
			}
			else {
				break;
			}
		}
		if (br == 0) {
			cout << "Pogresio si Username 3 puta! Moras pocet ispocetka!\n";
			return false;
		}
		//otvaranje datoteke i odredjivanje duzine
		ifstream korisnici;
		korisnici.open("LoginInfo.txt");
		korisnici.seekg(0, korisnici.end);
		int length = korisnici.tellg();
		korisnici.seekg(0, korisnici.beg);
		//'resetovanje' pomocnih nizova
		for (int i = 0; i < 30; i++) {
			pomchar[i] = 0;
			tempUchar[i] = 0;
			tempPchar[i] = 0;
		}
		for (int i = 30; i < 61; i++) {
			pomchar[i] = 0;
		}
		//prolazak kroz sve korisnike dok se ne nadje onaj sa 
		//istim korisnickim imenom ili dok se ne dodje do kraja datoteke
		while (korisnici.tellg() < length) {
			korisnici.getline(pomchar, 61);
			pomstring = string(pomchar);
			size_t lokacija = pomstring.find("$");
			pomstring.copy(tempUchar, lokacija, 0);
			pomstring.copy(tempPchar, pomstring.length() - lokacija - 1, lokacija + 1);
			tempUstring = string(tempUchar);
			tempPstring = string(tempPchar);
			if (tempUstring.compare(username) == 0) {
				isCorrect = true;
				break;
			}
			else {
				for (int i = 0; i < 30; i++) {
					pomchar[i] = 0;
					tempUchar[i] = 0;
					tempPchar[i] = 0;
				}
				for (int i = 30; i < 61; i++) {
					pomchar[i] = 0;
				}
			}
		}
		korisnici.close();
		//ako je pronadjeno odgovarajuce korisnicko ime, unosi i provjerava se pasvord maksimalno 3 puta
		if (isCorrect) {
			br = 3;
			while (br > 0) {
				password.clear();
				isValid = checkPassword();
				if (password.compare("QUIT") == 0) {
					username.clear();
					password.clear();
					cout << "Nasilan izlazak!\n";
					return false;
				}
				if (isValid) {
					if (tempPstring.compare(password) == 0) {
						return true;
					}
				}
				br--;
				if (br != 0) {
					cout << "Imate jos " << br << " pokusaja!\n";
				}
			}
			if (br == 0) {
				cout << "Pogresio si Password 3 puta! Moras pocet ispocetka!\n";
				return false;
			}
		}
		else {
			cout << "Ne postoji korisnik sa tim korisnickim imenom!\n";
		}

		return false;
	}
}