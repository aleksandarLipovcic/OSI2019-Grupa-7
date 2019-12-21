#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace OSI {

	class Categories
	{
	public:
		void printCategories();
		void addCategory();
		bool checkIfCategoryExists(string);
	};

}