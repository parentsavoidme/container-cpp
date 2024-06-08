#include "interface.h"
#include "hash_table.h"// ключ: Артикул /  Наименование товapa / ИНН поставщика / Дата
#include "tree1.h" // Хэш- 1 + 4 /// Искать по 1,4,2
#include <iostream>// дерево строится по наименованию если они одинаковые то 
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russiаn");
	Date d = { 10,11,2022 };
	unsigned long long code1 = 124;
	unsigned long long code2 = 125125;
	unsigned long long code3 = 86745315;
	string name1 = "milk";
	string name2 = "juice";
	string name3 = "bread";
	string name4 = "cheese";
	unsigned long long inn = 2222222222222;



	Pole p1 = { code1,name1,inn,d };
	Pole p2 = { code2,name2,inn,d };
	Pole p3 = { code3,name3,inn,d };
	Pole p4 = { code1,name3,inn,d };

	tree t;
	bool h = true;

	t.add(p1);
	t.add(p2);
	t.add(p3);
	t.add(p4);


	t.print();
	t.printAllLists();
	return 0;

}
