#include <iostream>
#include <concepts>
#include <vector>
#include <string>
#include <Windows.h>
#include "header.h"

using namespace std;

class Reader;

struct Author
{
    string fio;
    string country;
    Author(string f, string c) : fio(f), country(c) {}
};

class Book
{

public:
    string name;
    Author writer;
    int year;
    int number;
    enum genre { Драма, Детектив, Поэзия, Роман, Повесть, Рассказ, Сказка, Басня };
    genre Bookgenre;

    Book(string name, Author writer, int year, int nu, genre bookgenre) : name(name), writer(writer), year(year), number(nu), Bookgenre(bookgenre) {}

    bool operator==(const Book& other) const
    {
        return name == other.name && writer.fio == other.writer.fio && year == other.year && Bookgenre == other.Bookgenre;
    }

    bool operator!=(const Book& other) const
    {
        return !(*this == other);
    }
};

class People
{
public:
    string fio;
    int age;
    virtual void giveBook(Book book)
    {
    }
    virtual void takeBook(Book book)
    {
    }

    People(string f, int n) : fio(f), age(n) {}
};

class Librarian : public People
{
public:
    Librarian(string f, int n) : People(f, n) {}

    void takeBook(Book book) override
    {
        cout << "Librarian " << fio << " received book " << book.name << endl;
    }

    void giveBook(Book book) override
    {
        cout << "Librarian " << fio << " gave book " << book.name << endl;
    }
};

class Library
{
public:
    string name;
    string address;
    vector<Book> books;
    vector<Reader> readers;
    Librarian librarian;
    Library(string name, string address, Librarian librarian) : name(name), address(address), librarian(librarian) {}

    void addBook(Book book)
    {
        books.push_back(book);
        cout << "book " << book.name << " was added in library" << endl;
    }

    void dellBook(Book book)
    {
        books.erase(remove(books.begin(), books.end(), book), books.end());
        cout << "book " << book.name << " was taken from library" << endl;
    }

    void available(Book book)
    {
        if (countBook(books, book) > 0)
            cout << book.name << " available (" << countBook(books, book) << ")" << endl;
        else
            cout << book.name << " not available" << endl;
    }

    Library& operator--()
    {
        SYSTEMTIME st;
        GetLocalTime(&st);
        for (auto it = books.begin(); it != books.end();)
        {
            if (st.wYear - it->year > 5)
            {
                cout << "Списывается книга " << it->name << ", posted in " << it->year << endl;
                it = books.erase(it);
            }
            else
            {
                ++it;
            }
        }
        return *this;
    }

private:
    int countBook(vector<Book> arr, Book book)
    {
        return count(arr.begin(), arr.end(), book);
    }
};

class Reader : public People
{
public:
    vector<Book> borrowedBooks;
    Librarian* librarian;
    Library* library;
    int number;
    MyList<int, 5> mylist;
    Reader(string f, int n, Librarian* lib, Library* libb, int num, MyList<int, 5> mylist1) : People(f, n), librarian(lib), library(libb), number(num), mylist(mylist1) {}

    void takeBook(Book book) override
    {
        librarian->giveBook(book);
        library->dellBook(book);
        borrowedBooks.push_back(book);
        mylist.add(number);
        cout << "reader " << fio << "took book " << book.name << endl;
    }

    void giveBook(Book book) override
    {
        librarian->takeBook(book);
        library->addBook(book);
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), book), borrowedBooks.end());
        mylist.del();
        cout << "reader " << fio << " gave back book" << book.name << endl;
    }
};

int main()
{
    MyList <int, 5> list1;
    list1.add(2);
    list1.add(3);
    list1.add(50);
    MyList<int, 5>list2 = list1;
    list2.add(70);
    list2.add(70);
    list2.add(70);
    list2.add(70);
    list1.add(9);
    list1.swap(list2);
    swap(list1, list2);
    list1.print();
    list2.print();
   // list3.print();
    return list2.empty() != list1.empty();
}
