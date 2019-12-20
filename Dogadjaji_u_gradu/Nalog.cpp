#include "Nalog.h"

namespace OSI {
	Nalog::Nalog()
	{
		password = string();
		username = string();
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

	bool Nalog::enterUsername()
	{
		char c;
		int br = 0;
		bool isValid = true, isCorrect = true;
		char pomchar[100]; //ovaj broj ce se promjenit i vjerovatno dodat ogranicenje da nemoze username biti duzi od 31 karaktera
		string pomstring;
		cout << "Unesite Username (Mora biti jedinstven i moze samo sadrzati slova,brojeve i znak razmaka.)\n";
		cin >> pomstring;
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
		ifstream korisnici;
		korisnici.open("LoginInfo.txt");
		korisnici.seekg(0, korisnici.end);
		int length = korisnici.tellg();
		korisnici.seekg(0, korisnici.beg);
		if (isValid) {
			while (korisnici.tellg() < length) {
				korisnici.getline(pomchar, 100);
				pomstring = string(pomchar);
				size_t lokacija = pomstring.find("$");
				pomstring.erase(lokacija, pomstring.size());
				if (pomstring.compare(username) == 0) {
					isCorrect = false;
					break;
				}
				for (int i = 0; i < 100; i++) {
					pomchar[i] = 0;
				}
			}
		}
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
	bool Nalog::enterPassword()
	{
		char c;
		bool isValid = true;
		cout << "Unesite Password (Moze samo sadrzati slova,brojeve i znak razmaka.)\n";
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
		if (!isValid) {
			cout << "Username nije validan!\n";
		}
		return isValid;
	}
	bool Nalog::checkUsername()
	{
		char c;
		bool isValid = true;
		string pomstring;
		int br = 0;
		cout << "Unesite vas Username:";
		cin >> pomstring;
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
	void Nalog::napraviNalog()
	{
		bool isValid = true;
		username.clear();
		while (true) {
			isValid = enterUsername();
			if (!isValid) {
				username.clear();
			}
			else {
				break;
			}
		}
		isValid = true;
		password.clear();
		while (true) {
			isValid = enterPassword();
			if (!isValid) {
				password.clear();
			}
			else {
				break;
			}
		}
		fstream korisnici;
		korisnici.open("LoginInfo.txt", ios::app);
		korisnici << username << "$" << password << "\n";
		korisnici.close();
	}
	bool Nalog::ulogujSe()
	{
		bool isValid = true, isCorrect = false;
		char pomchar[100], tempUchar[100], tempPchar[100]; //ovaj broj ce se promjenit i vjerovatno dodat ogranicenje da nemoze username biti duzi od 31 karaktera
		string pomstring, tempUstring, tempPstring;
		int br = 3;
		username.clear();
		while (br > 0) { //unosenje username maksimalno 3 puta
			isValid = checkUsername();
			if (!isValid) {
				username.clear();
			}
			else {
				break;
			}
			br--;
		}
		if (br == 0) {
			cout << "Pogresio si Username 3 puta! Moras pocet ispocetka!\n";
			return false;
		}
		ifstream korisnici;
		korisnici.open("LoginInfo.txt");
		korisnici.seekg(0, korisnici.end);
		int length = korisnici.tellg();
		korisnici.seekg(0, korisnici.beg);
		for (int i = 0; i < 100; i++) {
			pomchar[i] = 0;
			tempUchar[i] = 0;
			tempPchar[i] = 0;
		}
		while (korisnici.tellg() < length) {	//prolazi kroz sve korisnike 
			korisnici.getline(pomchar, 100);
			pomstring = string(pomchar);
			size_t lokacija = pomstring.find("$");
			pomstring.copy(tempUchar, lokacija, 0);
			pomstring.copy(tempPchar, pomstring.length() - lokacija - 1, lokacija + 1);
			tempUchar[lokacija] = '\0';
			tempPchar[pomstring.length() - lokacija - 1] = '\0';
			tempUstring = string(tempUchar);
			tempPstring = string(tempPchar);
			if (tempUstring.compare(username) == 0) {	//provjerava dal posoji taj username
				isCorrect = true;
				break;
			}
			else {
				for (int i = 0; i < 100; i++) {
					pomchar[i] = 0;
					tempUchar[i] = 0;
					tempPchar[i] = 0;
				}
			}
		}
		korisnici.close();
		if (isCorrect) {	//ako postoji taj username prelazi se na kucanje passworda
			br = 3;
			while (br > 0) {
				password.clear();
				isValid = checkPassword();
				if (isValid) {
					if (tempPstring.compare(password) == 0) {
						return true;
					}
				}
				br--;
			}
			if (br == 0) {
				cout << "Pogresio si Password 3 puta! Moras pocet ispocetka!\n";
				return false;
			}
		}
		return false;
	}
}