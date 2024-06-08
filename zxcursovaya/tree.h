//#pragma once
//#include "hash_table.h"
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <regex>
//#include <sstream>
//
//using namespace std;
//
//struct Node 
//{
//    unsigned long long data;
//    Node* next = nullptr;
//};
//
//void dellist(Node*& head, unsigned long long INN) {
//    Node* temp = head;
//    do {
//        if (temp->next == head && head->data == INN) {
//            Node* del = head;
//            temp->next = del->next;
//            head = temp->next;
//            delete del;
//            return;
//        }
//
//        else if (temp->next->data == INN) {
//            Node* del = temp->next;
//            temp->next = del->next;
//            delete del;
//            return;
//        }
//        temp = temp->next;
//    } while (temp != head);
//
//}
//
//bool contains(Node* head, unsigned long long INN) {
//    if (head == nullptr) {
//        return false;
//    }
//
//    Node* temp = head;
//    do {
//        if (temp->data == INN) {
//            return true;
//        }
//        temp = temp->next;
//    } while (temp != head);
//    return false;
//}
//
//int count(Node*& head) {
//    int count = 0;
//    if (head == nullptr) {
//        return count;
//    }
//    else {
//        Node* temp = head;
//        do {
//            count += 1;
//            temp = temp->next;
//        } while (temp != head);
//    }
//    return count;
//}
//
//void print(Node*& head) {
//    Node* temp = head;
//    if (temp == nullptr) {
//        cout << "list empty" << endl;
//        return;
//    }
//    cout << "uchiha madara: " << endl;
//    do {
//        cout << temp->data << " ";
//        temp = temp->next;
//    } while (temp != head);
//    cout << endl;
//}
//
//void back(Node*& head, unsigned long long INN) {
//    Node* node = new Node;
//    node->data = INN;
//    if (head == nullptr) {
//        head = node;
//        head->next = head;
//    }
//    else {
//        Node* temp = head;
//        while (temp->next != head) {
//            temp = temp->next;
//        }
//        temp->next = node;
//        node->next = head;
//    }
//}
//
//struct Date
//{
//    size_t day;
//    size_t month;
//    size_t year;
//    Date(size_t d, size_t m, size_t y) : day(d), month(m), year(y) {}
//    Date() = default;
//    bool operator ==(const Date& other) const
//    {
//        return ((this->day == other.day) && (this->month == other.month) && (this->year == other.year));
//    }
//
//    bool operator !=(const Date& other) const
//    {
//        return !(*this == other);
//    }
//};
//
//struct Pole
//{
//    unsigned long long code;
//    string product;
//    unsigned long long  INN;
//    Date data;
//    Pole() = default;
//    Pole(unsigned long long c, string p, unsigned long long in, Date did) : code(c), product(p), INN(in), data(did) {}
//    bool operator ==(Pole& other)
//    {
//        return ((this->code == other.code) && (this->data == other.data) && (this->product == other.product));
//    }
//
//    bool operator !=(Pole& other)
//    {
//        return !(*this == other);
//    }
//
//    void print()
//    {
//        cout << "|Code: " << code << " |Product: " << product << "|INN: " << INN << "|Data: " << data.day << "." << data.month << "." << data.year << "| hash1: ";
//    }
//
//};
//
//class tree
//{
//private:
//    int balance;
//    Pole key;
//    Node* list;
//    tree* right;
//    tree* left;
//    tree* root1;
//    tree() = default;
//    tree(int b, Pole k, Node* lis, tree* r, tree* l,tree*& r1) :balance(b), key(k), right(r), left(l),root1(r1) {}
//    ~tree() = default;
//    //~tree();
//
//    void balanceL(tree*& root, bool& h) {
//        tree* temp1 = new tree;
//        tree* temp2 = new tree;
//        if (root->balance == -1) {
//            root->balance = 0;
//        }
//        else if (root->balance == 0) {
//            root->balance = 1;
//            h = false;
//        }
//        else {
//            temp1 = root->right;
//            if (temp1->balance >= 0) {// LL
//                root->right = temp1->left;
//                temp1->left = root;
//
//                if (temp1->balance == 0) {
//                    root->balance = 1;
//                    temp1->balance = -1;
//                    h = false;
//                }
//                else {
//                    root->balance = 0;
//                    temp1->balance = 0;
//                }
//                root = temp1;
//            }
//            else { //2RL
//                temp2 = temp1->left;
//                temp1->left = temp2->right;
//                temp2->right = temp1;
//                root->right = temp2->left;
//                temp2->left = root;
//                if (temp2->balance == 1) {
//                    root->balance = -1;
//                }
//                else {
//                    root->balance = 0;
//                }
//                if (temp2->balance == -1) {
//                    temp1->balance = 1;
//                }
//                else {
//                    temp1->balance = 0;
//                }
//                root = temp2;
//                temp2->balance = 0;
//            }
//        }
//    }
//
//    void balanceR(tree*& root, bool& h)
//    {
//        tree* temp1 = new tree;
//        tree* temp2 = new tree;
//        if (root->balance == 1) {
//            root->balance = 0;
//        }
//        else if (root->balance == 0) {
//            root->balance = -1;
//            h = false;
//        }
//        else {
//            temp1 = root->left;
//            if (temp1->balance <= 0) {//RR
//                root->left = temp1->right;
//                temp1->right = root;
//                if (temp1->balance == 0) {
//                    root->balance = -1;
//                    temp1->balance = 1;
//                    h = false;
//                }
//                else {
//                    root->balance = 0;
//                    temp1->balance = 0;
//                }
//                root = temp1;
//            }
//            else { //2LR
//                temp2 = temp1->right;
//                temp1->right = temp2->left;
//                temp2->left = temp1;
//                root->left = temp2->right;
//                temp2->right = root;
//                if (temp2->balance == -1) {
//                    root->balance = 1;
//                }
//                else {
//                    root->balance = 0;
//                }
//                if (temp2->balance == 1) {
//                    temp1->balance = -1;
//                }
//                else {
//                    temp1->balance = 0;
//                }
//                root = temp2;
//                temp2->balance = 0;
//            }
//        }
//    }
//
//    void delIfChildren(tree*& root, tree*& q, bool& h) {
//        if (root->right != nullptr) {
//            delIfChildren(root->right, q, h);
//            if (h == true) {
//                balanceR(root, h);
//            }
//        }
//        else {
//            q->key = root->key;
//            q->list = root->list;
//            q = root;
//            root = root->left;
//            h = true;
//        }
//    }
//    void symmetric(tree* p, ofstream& file) {
//        if (p != nullptr) {
//            symmetric(p->left, file);
//            file << p->key.code << " " << p->key.product << " " << p->key.INN << p->key.data.day << "." << p->key.data.month << "." << p->key.data.year << endl;
//            symmetric(p->right, file);
//        }
//    }
//
//    void draw(tree* p, int k) {
//        if (p == nullptr) return;
//        else {
//            draw(p->right, k + 5);
//            for (int i = 1; i <= k; i++) {
//                cout << " ";
//            }
//            cout << p->key.code << " " << p->key.product << " " << p->key.INN << " " << p->key.data.day << "." << p->key.data.month << "." << p->key.data.year << endl;
//            draw(p->left, k + 5);
//        }
//    }
//
//    void clear(tree*& root) // деструктор
//    {
//        if (root == nullptr) {
//            return;
//        }
//        clear(root->left);
//        clear(root->right);
//        root = nullptr;
//        delete root;
//    }
//
//    bool search(tree* p, Pole d) {
//        if (p != NULL)
//        {
//            if (p->key.product == d.product)
//                return 1;
//
//            if (p->key.product > d.product)
//                return search(p->left, d);
//
//            if (p->key.product < d.product)
//                return search(p->right, d);
//
//        }
//        else
//            return 0;
//    }
//
//    void add(tree*& root, Pole data, unsigned long long INN, bool& h) {
//        tree* temp1 = new tree;
//        tree* temp2 = new tree;
//        if (root == nullptr) {
//            root = new tree;
//            root->key = data;
//            root->balance = 0;
//            back(root->list, INN);
//            h = true;
//        }
//        else if (root->key.product < data.product)
//        {
//            add(root->left, data, INN, h);
//            if (h == true) {
//                if (root->balance == 1) {
//                    root->balance = 0;
//                    h = false;
//                }
//                else if (root->balance == 0) {
//                    root->balance = -1;
//                }
//                else {
//                    temp1 = root->left;
//                    if (temp1->balance == -1) {//LL
//                        root->left = temp1->right;
//                        temp1->right = root;
//                        root->balance = 0;
//                        root = temp1;
//                    }
//                    else {
//                        temp2 = temp1->right;//2LR
//                        temp1->right = temp2->left;
//                        temp2->left = temp1;
//                        root->left = temp2->right;
//                        temp2->right = root;
//
//                        if (temp2->balance == -1) {
//                            root->balance = 1;
//                        }
//                        else {
//                            root->balance = 0;
//                        }
//                        if (temp2->balance == +1) {
//                            temp1->balance = -1;
//                        }
//                        else {
//                            temp1->balance = 0;
//                        }
//                        root = temp2;
//                    }
//                    root->balance = 0;
//                    h = false;
//                }
//            }
//        }
//        else if (root->key.product > data.product)
//        {
//            add(root->right, data, INN, h);
//            if (h == true) {
//                if (root->balance == -1) {
//                    root->balance = 0;
//                    h = false;
//                }
//                else if (root->balance == 0) {
//                    root->balance = 1;
//                }
//                else {
//                    temp1 = root->right;
//                    if (temp1->balance == 1) {//RR
//                        root->right = temp1->left;
//                        temp1->left = root;
//                        root->balance = 0;
//                        root = temp1;
//                    }
//                    else {//2RL
//                        temp2 = temp1->left;
//                        temp1->left = temp2->right;
//                        temp2->right = temp1;
//                        root->right = temp2->left;
//                        temp2->left = root;
//
//                        if (temp2->balance == 1) {
//                            root->balance = -1;
//                        }
//                        else {
//                            root->balance = 0;
//                        }
//                        if (temp2->balance == -1) {
//                            temp1->balance = 1;
//                        }
//                        else {
//                            temp1->balance = 0;
//                        }
//                        root = temp2;
//                    }
//                    root->balance = 0;
//                    h = false;
//                }
//            }
//
//        }
//        else {
//            back(root->list, data.INN);//ИНН если одинаковые в дереве
//            h = false;
//        }
//
//    }
//
//    void deleteLeft(tree*& root, Pole x, bool& h, int number) {
//        tree* q = new tree;
//        if (root == nullptr) {
//            return;
//        }
//        else if (root->key.product > x.product) {
//            deleteLeft(root->left, x, h, number);
//            if (h == true) {
//                balanceL(root, h);
//            }
//        }
//        else if (root->key.product < x.product) {
//            deleteLeft(root->right, x, h, number);
//            if (h == true) {
//                balanceR(root, h);
//            }
//        }
//        else {
//            if (contains(root->list, number) == true)
//            {
//                if (count(root->list) == 1) {
//                    q = root;
//                    if (q->right == nullptr) {
//                        root = q->left;
//                        h = true;
//                    }
//                    else if (q->left == nullptr) {
//                        root = q->right;
//                        h = true;
//                    }
//                    else {
//                        delIfChildren(q->left, q, h);
//                        if (h == true) {
//                            balanceL(root, h);
//                        }
//                    }
//                }
//
//                else {
//                    dellist(root->list, number);
//                    h = false;
//                    return;
//                }
//            }
//            else {
//                cout << "номера строки нет в списке";
//                h = false;
//                return;
//            }
//        }
//    }
//
//    void printAllLists(tree* root)
//    {
//        if (root == nullptr) {
//            return;
//        }
//        print(root->list);
//        printAllLists(root->left);
//        printAllLists(root->right);
//    }
// 
//
//public:
//    void add1(Pole& p )
//
//    {
//        bool h = true;
//        add(root1, p, p.INN, h);
//    }
//  
//    void draw1()
//    {
//        draw(root1, 1);
//    }
//};