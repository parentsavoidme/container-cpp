#pragma once 
#include "interface.h"
#include "tree1.h"
#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

const float A = 0.618;//0<A<1 0.618033
const float k = 1.2;

struct Date;
struct Pole;

class hash_table
{
private:
	vector <Pole> table;
	size_t size;
	vector<int>status;
	size_t count = 0;
	size_t begin_size;

	int hashFunction(Pole& p)
	{
		int h = p.code + p.data.day + p.data.month + p.data.year;
		double hashObj = h * A - floor(h * A);
		return size * (hashObj);
	}

	int chashFunction(Pole& p, int count_coll)
	{
		int b = k;
		return (hashFunction(p) + count_coll * b) % size;
	}

	void reHashing(size_t size1)
	{
		vector<Pole> otable = table;
		vector<Pole> ntable(size1);
		vector<int> ostatus = status;
		vector<int> nstatus(size1, 0);
		table = ntable;
		status = nstatus;
		size = size1;
		count = 0;

		for (int x = 0; x < otable.size(); x++)
		{
			if (ostatus[x] == 1)
			{
				add(otable[x], false);
			}
		}
	}

	void fillFactor()
	{
		float a = count * 100 / size;
		if (a > 75)
			reHashing(size * 2);
		else if (a < 25 && size / 2 >= begin_size)
			reHashing(size / 2);
	}



	bool addCollision(Pole& p, int index, int counttt)
	{
		while (status[index] == 1)
		{
			if (status[index] == 1 && table[index] == p)
				return false;
			counttt++;
			index = chashFunction(p, counttt);
		}
		status[index] = 1;
		table[index] = p;
		count++;
		return true;
	}

	bool delCollision(int reHash, int countt, Pole& p)
	{
		while (!(status[reHash] == 1 && table[reHash].product == p.product)) // 1+4 2
		{
			if (countt > size)
			{
				return false;
			}
			countt++;
			reHash = chashFunction(p, countt);
		}
		status[reHash] = 2;
		count--;
	}

	bool searchCollision(Pole& p, int ccount)//
	{
		int rehash = chashFunction(p, ccount);
		while (size > rehash && status[rehash] != 0 && table[rehash].product != p.product)// 1+4 2
		{
			ccount++;
			rehash = chashFunction(p, ccount);
			if (size > rehash && status[rehash] == 1 && table[rehash] == p)
			{
				cout << "|Количество шагов: " << ccount + 1 << " |Номер строки: " << rehash << endl;
				return true;
			}
		}
		cout << "Элемента нет в таблице" << endl;
		return false;
	}

public:

	void fillFactorr()
	{
		cout << "|Fill factor: " << count * 100 / size << " |Elements count: " << count << " |Table's size: " << size << endl;
	}

	size_t getSize()
	{
		return size;
	}

	vector<Pole> getVect()
	{
		return this->table;
	}

	size_t getCount()
	{
		return count;
	}

	hash_table() {
		table = vector<Pole>(size);
		status = vector<int>(size);
		count = 0;
		size = 1;
		begin_size = size;
	}

	hash_table(vector<Pole> v)
	{
		this->size = v.size();
		this->begin_size = v.size();
		table = vector<Pole>(size);
		status = vector<int>(size);
		count = 0;
		for (auto& i : v)
		{
			add(i);
		}
	}
	hash_table(size_t size)
	{
		this->size = (size == 0) ? 1 : size;
		begin_size = this->size;
		table = vector<Pole>(this->size);
		status = vector<int>(this->size);
		count = 0;
	}

	~hash_table() {};

	bool add(Pole& p, bool cof = true)
	{

		int findex = hashFunction(p);
		int index = findex;

		if (status[findex] != 1)
		{
			status[findex] = 1;
			table[findex] = p;
			count++;
			if (cof)
				fillFactor();
			return true;
		}

		addCollision(p, index, 0);
		if (cof)
			fillFactor();

		return true;
	}

	bool del(Pole& p) 
	{
		int h1 = hashFunction(p);
		int h2 = h1;
		if (status[h1] == 1 && table[h1].product == p.product)// удаление 1+4 2
		{
			status[h1] = 2;
			count--;
			fillFactor();
			return true;
		}
		else
		{
			delCollision(h2, 0, p);
			fillFactor();
			return false;
		}

	}

	bool search(Pole& p)
	{
		int h1 = hashFunction(p);
		if (status[h1] == 1 && (table[h1].product == p.product)) // поиск 1+4 2
		{
			cout << " |Количество шагов: 1 " << "|Номер строки: " << h1 << endl;
			return true;
		}
		else
		{
			return searchCollision(p, 0);
		}
	}

	bool print()
	{

		for (int i = 0; i < size; i++)
		{
			if (status[i] != 0)
			{
				cout << " | Status: " << status[i];
				cout << " |i: " << i << " ";
				table[i].print();
				cout << hashFunction(table[i]) << endl;
			}
			else
			{
				cout << " | Status: " << status[i] << endl;
			}
			cout << endl;
		}
		return true;
	}

	void writefile( const string& file)
	{
		ofstream out(file);
		for (int i = 0; i < table.size(); i++) {
			out << i << " " << table[i].code << " " << table[i].product << " " << table[i].INN << " " << table[i].data.day << "." << table[i].data.month << "." << table[i].data.year;
		}
		out.close();
	}

};
