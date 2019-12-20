#include "Nalog.h"

Nalog::Nalog()
{
	password = string();
	username = string();
}
Nalog::Nalog(const Nalog&other)
{
	copy(other);
}
Nalog::Nalog(Nalog&&other)
{
	move(std::move(other));
}
Nalog::~Nalog()
{
	del();
}

Nalog& Nalog::operator=(const Nalog&other)
{
	if (this == &other)
		return*this;
	del();
	copy(other);
	return *this;
}
Nalog& Nalog::operator=(Nalog&&other)
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
void Nalog::move(Nalog&&other)
{
	password = string(other.password);
	username = string(other.username);
	other.del();
}

void Nalog::del()
{
	this->username = nullptr;
	this->password = nullptr;
}

bool Nalog::enterUsername()
{
	char c;
	bool isValid=true, isCorrect=true;
	fstream korisnici;
	char pomchar[100]; //ovaj broj ce se promjenit i vjerovatno dodat ogranicenje da nemoze username biti duzi od 31 karaktera
	string pomstring;
	korisnici.open("LoginInfo.txt");
	cout << "Unesite Username (Mora biti jedinstven i moze samo sadrzati slova,brojeve i znak razmaka.)\n";
	c = _getch();
	while (c != 10) {
		if (isValid == true) {
			if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 32) {
				isValid = true;
			}
			else {
				isValid = false;
			}
		}
		username.push_back(c);
		cout << c;
		c = _getch();
	}
	if (isValid) {
		korisnici.getline(pomchar, 100);
		pomstring = string(pomchar);
		while (!pomstring._Equal(nullptr)) {
			size_t lokacija = pomstring.find("$");
			pomstring.erase(lokacija, pomstring.size());
			if (pomstring._Equal(this->username)) {
				isCorrect = false;
				break;
			}
			for (int i = 0; i < 100; i++) {
				pomchar[i]=0;
			}
			korisnici.getline(pomchar, 100);
			pomstring.clear();
			pomstring = string(pomchar);
		}
	}
	if (isValid && isCorrect) {
		korisnici.seekg(ios_base::end);
		korisnici << this->username << "$";
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
	fstream korisnici;
	korisnici.open("LoginInfo.txt");
	cout << "Unesite Password (Moze samo sadrzati slova,brojeve i znak razmaka.)\n";
	c = _getch();
	while (c != 10) {
		if (isValid == true) {
			if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 32) {
				isValid = true;
			}
			else {
				isValid = false;
			}
		}
		username.push_back(c);
		cout << '*';
		c = _getch();
	}
	if (isValid) {
		korisnici.seekg(ios_base::end);
		korisnici << this->password << "\n";
	}
	korisnici.close();
	return isValid;
}
bool Nalog::checkUsername()
{
	char c;
	bool isValid = true;
	fstream korisnici;
	korisnici.open("LoginInfo.txt");
	cout << "Unesite vas Username:";
	c = _getch();
	while (c != 10) {
		if (isValid == true) {
			if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 32) {
				isValid = true;
			}
			else {
				isValid = false;
			}
		}
		username.push_back(c);
		cout << c;
		c = _getch();
	}
	korisnici.close();
	if (!isValid) {
		cout << "Username nije validan!\n";
	}
	return isValid;
}
bool Nalog::checkPassword()
{
	char c;
	bool isValid = true;
	fstream korisnici;
	korisnici.open("LoginInfo.txt");
	cout << "Unesite vas Password:";
	c = _getch();
	while (c != 10) {
		if (isValid == true) {
			if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 32) {
				isValid = true;
			}
			else {
				isValid = false;
			}
		}
		username.push_back(c);
		cout << '*';
		c = _getch();
	}
	korisnici.close();
	if (!isValid) {
		cout << "Password nije validan!\n";
	}
	return isValid;
	korisnici.close();
	if (isValid) {
		korisnici.seekg(ios_base::end);
		korisnici << "Password:" << this->password << "\n";
		return true;
	}
	return false;
}
void Nalog::napraviNalog()
{
	bool isValid = true;
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
	while (true) {
		isValid = enterPassword();
		if (!isValid) {
			password.clear();
		}
		else {
			break;
		}
	}
}
bool Nalog::ulogujSe()
{
	bool isValid = true,isCorrect=false;
	fstream korisnici;
	korisnici.open("LoginInfo.txt");
	char pomchar[100],tempUchar[100],tempPchar[100]; //ovaj broj ce se promjenit i vjerovatno dodat ogranicenje da nemoze username biti duzi od 31 karaktera
	string pomstring,tempUstring,tempPstring;
	int br = 3;
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
	korisnici.getline(pomchar, 100);
	pomstring = string(pomchar);
	while (!pomstring._Equal(nullptr)) {	//prolazi kroz sve korisnike 
		size_t lokacija = pomstring.find("$");
		pomstring.copy(tempUchar, lokacija - 1, 0);
		pomstring.copy(tempPchar, pomstring.size() - lokacija, lokacija + 1);
		tempUstring = string(tempUchar);
		tempPstring = string(tempPchar);
		if (tempUstring._Equal(this->username)) {	//provjerava dal posoji taj username
			isCorrect = true;
			break;
		}
		else {
			for (int i = 0; i < 100; i++) {
				pomchar[i] = 0;
				tempUchar[i] = 0;
				tempPchar[i] = 0;
			}
			pomstring.clear();
			tempUstring.clear();
			tempPstring.clear();
			korisnici.getline(pomchar, 100);
			pomstring = string(pomchar);
		}
	}
	if (isCorrect) {	//ako postoji taj username prelazi se na kucanje passworda
		br = 3;
		while (br > 0) {
			isValid = checkPassword();
			if (!isValid) {
				password.clear();
			}
			else {
				if (password._Equal(tempPstring)) {
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
