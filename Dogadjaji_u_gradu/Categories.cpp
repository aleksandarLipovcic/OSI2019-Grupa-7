#include "Categories.h"

namespace OSI {

	void Categories::printCategories() {
		ifstream kategorije;
		kategorije.open("categories.txt");
		kategorije.seekg(0, kategorije.end);
		int length = kategorije.tellg();
		kategorije.seekg(0, kategorije.beg);

		int i = 1;
		char pomchar[30];
		string pomstring;

		cout << "Postojece kategorije su:\n";
		while (kategorije.tellg() < length) {
			kategorije.getline(pomchar, 30);
			pomstring = string(pomchar);
			cout << "\t" << i << "." << pomstring << "\n";
			i++;
			for (int j = 0; j < 30; j++) {
				pomchar[j] = 0;
			}
			pomstring.clear();
		}

		kategorije.close();
	}
	void Categories::addCategory()
	{
		//ovo je samo ako ne postoji categories.txt da napravi praznu
		fstream kategorije;
		kategorije.open("categories.txt", ios::app);
		kategorije.close();

		char categoryName[30];
		cout << "Unesite ime nove kategorije:";
		cin.getline(categoryName, 30);
		string category = string(categoryName);

		while (true) {
			if (checkIfCategoryExists(category) == false) {
				break;
			}
			cout << "Kategorija vec postoji,unesite drugo ime ili rijec 'QUIT' za izlazak iz funkcije:";
			for (int j = 0; j < 30; j++) {
				categoryName[j] = 0;
			}
			category.clear();
			cin.getline(categoryName, 30);
			category = string(categoryName);
			if (category.compare("QUIT") == 0) {
				return;
			}
		}

		kategorije.open("categories.txt", ios::app);
		kategorije << category << "\n";
		kategorije.close();

	}
	bool Categories::checkIfCategoryExists(string categoryName)
	{
		ifstream kategorije;
		kategorije.open("categories.txt");
		kategorije.seekg(0, kategorije.end);
		int length = kategorije.tellg();
		kategorije.seekg(0, kategorije.beg);

		char pomchar[30];
		string pomstring;
		while (kategorije.tellg() < length) {
			kategorije.getline(pomchar, 30);
			pomstring = string(pomchar);
			if (categoryName.compare(pomstring) == 0) {
				return true;
			}
			for (int j = 0; j < 30; j++) {
				pomchar[j] = 0;
			}
			pomstring.clear();
		}

		kategorije.close();
		return false;

	}
}
