#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

const float A = 0.618;//0<A<1 0.618033
const float k = 1.2;

struct Date
{
	size_t day;
	size_t month;
	size_t year;
	Date(size_t d, size_t m, size_t y) : day(d), month(m), year(y) {}
	Date() = default;
	bool operator ==(Date& other)
	{
		return ((this->day == other.day) && (this->month == other.month) && (this->year == other.year));
	}

	bool operator !=(Date& other)
	{
		return !(*this == other);
	}
};

struct Pole
{
	Date data;
	string FIO;
	string Discipline;
	size_t request;
	Pole() = default;
	Pole(Date did, string s, string Di, size_t r) :data(did), FIO(s), Discipline(Di), request(r) {}
	bool operator ==(Pole& other)
	{
		return ((this->FIO == other.FIO) && (this->data == other.data) && (this->Discipline == other.Discipline) && (this->request == other.request));
	}

	bool operator !=(Pole& other)
	{
		return !(*this == other);
	}

	void print()
	{
		cout << "|Data: " << data.day << "." << data.month << "." << data.year << " |FIO: " << FIO << " |discipline: " << Discipline << " |request number: " << request << "| hash1: ";
	}
};

class hash_table
{
private:
	vector <Pole> table;
	size_t size;// вводим сами через конструктор в int main +++++++++
	vector<int>status;
	size_t count = 0;//size_t+++

	int hashFunction(Pole& p  )//ключ ппоменять
	{
		int h = 0;
		string str = to_string(p.request) + p.FIO;
		for (char ch : str)
			h = h + ch;
		double hashObj = h * A - floor(h * A);
		return size * (hashObj);
	}

	int chashFunction(Pole&p, int count_coll)
	{
		int b = k;
		return (hashFunction(p) + count_coll * b) % size;
	}

	void reHashing(size_t size1)// чтобы удалялись ячёки у которых статус 2 +++++
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

	void fillFactor()// переделать в проценты +
	{
		float a = count * 100 / size;
		if (a > 75)
			reHashing(size * 2);
		else if (a < 25)
			reHashing(size / 2);
	}



	bool addCollision(Pole& p, int index,  int counttt)
	{
		while (status[index] != 0)
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

	bool delCollision( int reHash, int countt, Pole& p)
	{
		while (!(status[reHash] == 1 && table[reHash] == p))
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

public:

	float fillFactorr()
	{
		return count * 100 / size;
	}

	size_t getSize()
	{
		return size;
	}

	vector<Pole> getVect()
	{
		return this->table;
	}

	float getCount()
	{
		return count;
	}

	hash_table() {
		table = vector<Pole>(size);
		status = vector<int>(size);
		count = 0;
		size = 0;
	}

	hash_table(vector<Pole> v)
	{
		this->size = v.size();
		table = vector<Pole>(size);
		status = vector<int>(size);
		count = 0;
		for (auto& i : v)
		{
			add(i);
		}
	}
	hash_table(int size)
	{
		this->size = size;
		table = vector<Pole>(size);
		status = vector<int>(size);
		count = 0;
	}

	~hash_table() {};
	bool addCollision(Pole& p, int index, int counttt)
	{
		while (status[index] != 0)
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
		while (!(status[reHash] == 1 && table[reHash] == p))
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
	bool add(Pole& p, bool cof = true)
	{
		int findex = hashFunction(p);
		int index = findex; 

		if (status[findex] == 0)
		{
			status[findex] = 1;
			table[findex] = p;
			count++;
			if (cof)
				fillFactor();
			return true;
		}
		
		addCollision(p, index,  0);

		if (cof)
			fillFactor();
		return true;
	}

	bool del(Pole& p)
	{
		int h1 = hashFunction(p);
		int h2 = h1;
		if (status[h1] == 1 && table[h1] == p)
		{
			status[h1] = 2;
			count--;
			fillFactor();
			return true;
		}
		else
		{
			delCollision( h2, 0, p);
			fillFactor();
			return false;
		}

	}

	bool find(Pole& p)
	{
		int h1 = hashFunction(p);
		if (status[h1] == 1 && table[h1] == p)
		{
			return true;
		}
		else
		{
			return findCollision(p, 0);
		}
	}

	bool findCollision(Pole& p, int count)
	{
		int rehash = chashFunction(p, count);
		while (size > rehash && status[rehash] != 1 && table[rehash] != p)
		{
			count++;
			rehash = chashFunction(p, count);
			if (size > rehash && status[rehash] == 1 && table[rehash] == p)
			{
				return true;
			}

		}
		return false;
	}

	void print()// добавить значение первого хэша ++
	{

		for (int i = 0; i < size; i++)
		{
			if (status[i] == 1)
			{
				cout << "|i: " << i << " ";
				table[i].print();
				cout << hashFunction(table[i]) << endl;
				cout << endl;
			}
		}
	}
};

vector <Pole> readfile(const string& filename) {
	vector<Pole> lines;
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "NO OPEN" << endl;
		return lines;
	}
	int n = 0;
	int day, month, year;
	string fio, discipline, other;
	char d1('.'), d2('.');
	while (file >> day >> d1 >> month >> d2 >> year)
	{
		string surname, name, patronymic, subject;
		file >> surname >> name >> patronymic >> discipline;
		fio = surname + " " + name + " " + patronymic;
		getline(file, other);
		int request = stoi(other);
		Date d(day, month, year);
		lines.push_back(Pole(d, fio, discipline, request));
		n += 1;
	}

	file.close();
	return lines;
}

void writefile(vector <Pole>& arr, const string& file)
{
	ofstream out(file);
	for (int i = 0; i < arr.size(); i++) {
		out << i << " " << arr[i].data.day << "." << arr[i].data.month << "." << arr[i].data.year << " " << arr[i].FIO << " " << arr[i].Discipline << " " << arr[i].request << endl;
	}
	out.close();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	//vector <Pole> p = readfile("C://lin+bin.txt");
	hash_table t(150);
	//hash_table t(p);
	vector<Pole> tt = t.getVect();

	Date d = { 12,12,2004 };
	Pole p1 = { d,"Черников Андрей Олегович","Психология",17125 };
	Pole p9 = { d,"Черников Андрей Олегович","Психология",52 };
	Pole p10 = { d,"Ефремов Евг Леонидович","MAtlogic",100 };
	Pole p100 = { d,"Ефремов Евг Леонидович","MAtlogic",518 };
	Pole p10000 = { d,"Ефремов Евг Леонидович","MAtlogic",1111518 };
	Pole p10001 = { d,"Ефремов Евг Леонидович","MAtlogic",1111519 };
	Pole p10002 = { d,"Ефремов Евг Леонидович","MAtlogic",1111520 };
	Pole p10003 = { d,"Ефремов Евг Леонидович","MAtlogic",1111521 };
	Pole p10004 = { d,"Ефремов Евг Леонидович","MAtlogic",1111522 };
	Pole p10005 = { d,"Ефремов Евг Леонидович","MAtlogic",1111523 };
	Pole p10006 = { d,"Ефремов Евг Леонидович","MAtlogic",1111524 };
	Pole p10007 = { d,"Ефремов Евг Леонидович","MAtlogic",1111525 };
	Pole p10008 = { d,"Ефремов Евг Леонидович","MAtlogic",1111526 };
	Pole p10009 = { d,"Ефремов Евг Леонидович","MAtlogic",1111527 };
	Pole p15 = { d,"Ефремов Евг Леонидович","MAtlogic",111 };

	t.add(p10);
	t.add(p1);
	t.add(p9);
	t.add(p100);
	t.add(p10000);
	t.add(p10001);
	t.add(p10002);
	t.add(p10003);
	t.add(p10004);
	t.add(p10005);
	t.add(p10006);
	t.add(p10007);
	t.add(p10008);
	t.add(p10009);
	t.add(p15);
	cout<<t.find(p1)<<endl;
	cout << t.find(p10002) << endl;





	t.print();

	cout << t.fillFactorr() << endl;
	cout << t.getSize() << endl;
	cout << t.getCount() << endl;

	writefile(tt, "C://ht.txt");
}