#pragma once
#include "hash_table.h"
#include "interface.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>

using namespace std;

struct Date
{
    size_t day;
    size_t month;
    size_t year;
    Date(size_t d, size_t m, size_t y) : day(d), month(m), year(y) {}
    Date() = default;
    bool operator ==(const Date& other) const
    {
        return ((this->day == other.day) && (this->month == other.month) && (this->year == other.year));
    }

    bool operator !=(const Date& other) const
    {
        return !(*this == other);
    }
};

struct Pole
{
    unsigned long long code;
    string product;
    unsigned long long  INN;
    Date data;
    Pole() = default;
    Pole(unsigned long long c, string p, unsigned long long in, Date did) : code(c), product(p), INN(in), data(did) {}
    bool operator ==(Pole& other)
    {
        return ((this->code == other.code) && (this->data == other.data) && (this->product == other.product));
    }

    bool operator !=(Pole& other)
    {
        return !(*this == other);
    }

    void print()
    {
        cout << "|Code: " << code << " |Product: " << product << "|INN: " << INN << "|Data: " << data.day << "." << data.month << "." << data.year << "| hash1: ";
    }

};

class LinkedList 
{
private:
    struct Node
    {
        unsigned long long data;
        Node* next = nullptr;
        Node(unsigned long long d) : data(d), next(nullptr) {}
    };
    Node* head = nullptr;
public:

    LinkedList() :head(nullptr) {}

    bool contains(unsigned long long INN) 
    {
        if (head == nullptr)
            return false;
        Node* temp = head;
        do 
        {
            if (temp->data == INN)
                return true;
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    int count() {
        int count = 0;
        if (head == nullptr)
            return count;
        else 
        {
            Node* temp = head;
            do
            {
                count += 1;
                temp = temp->next;
            } while (temp != head);
        }
        return count;
    }

    void print() 
    {
        Node* temp = head;
        if (temp == nullptr) 
        {
            cout << "list empty" << endl;
            return;
        }
        cout << "list: " << endl;
        do 
        {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    void add(unsigned long long INN) 
    {
        Node* node = new Node(INN);
        if (head == nullptr) {
            head = node;
            head->next = head;
        }
        else 
        {
            Node* temp = head;
            while (temp->next != head) 
            {
                temp = temp->next;
            }
            temp->next = node;
            node->next = head;
        }
    }

    void del(unsigned long long INN)
    {
        if (head == nullptr)
            return;

        Node* temp = head;
        do {
            if (temp->next == head && head->data == INN)
            {
                Node* del = head;
                temp->next = del->next;
                head = temp->next;
                delete del;
                return;
            }
            else if (temp->next->data == INN)
            {
                Node* del = temp->next;
                temp->next = del->next;
                delete del;
                return;
            }
            temp = temp->next;
        } while (temp != head);
    }
};


class tree {
private:
    struct TreeNode
    {
        int balance;
        Pole key;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        LinkedList* list = nullptr;
        TreeNode() : list(new LinkedList()) {} 
    };
    TreeNode* root = nullptr;

    void balanceL(TreeNode*& root, bool& h) 
    {
        TreeNode* temp1 = new TreeNode;
        TreeNode* temp2 = new TreeNode;
        if (root->balance == -1) 
            root->balance = 0;
        else if (root->balance == 0) 
        {
            root->balance = 1;
            h = false;
        }
        else 
        {
            temp1 = root->right;
            if (temp1->balance >= 0) 
            {// LL
                root->right = temp1->left;
                temp1->left = root;
                if (temp1->balance == 0) 
                {
                    root->balance = 1;
                    temp1->balance = -1;
                    h = false;
                }
                else 
                {
                    root->balance = 0;
                    temp1->balance = 0;
                }
                root = temp1;
            }
            else 
            { //2RL
                temp2 = temp1->left;
                temp1->left = temp2->right;
                temp2->right = temp1;
                root->right = temp2->left;
                temp2->left = root;
                if (temp2->balance == 1) 
                    root->balance = -1;
                else
                    root->balance = 0;
                if (temp2->balance == -1)
                    temp1->balance = 1;
                else 
                    temp1->balance = 0;
                root = temp2;
                temp2->balance = 0;
            }
        }
    }

    void balanceR(TreeNode*& root, bool& h)
    {
        TreeNode* temp1 = new TreeNode;
        TreeNode* temp2 = new TreeNode;
        if (root->balance == 1)
            root->balance = 0;
        else if (root->balance == 0) 
        {
            root->balance = -1;
            h = false;
        }
        else 
        {
            temp1 = root->left;
            if (temp1->balance <= 0)
            {//RR
                root->left = temp1->right;
                temp1->right = root;
                if (temp1->balance == 0) {
                    root->balance = -1;
                    temp1->balance = 1;
                    h = false;
                }
                else {
                    root->balance = 0;
                    temp1->balance = 0;
                }
                root = temp1;
            }
            else
            { //2LR
                temp2 = temp1->right;
                temp1->right = temp2->left;
                temp2->left = temp1;
                root->left = temp2->right;
                temp2->right = root;
                if (temp2->balance == -1)
                    root->balance = 1;
                else
                    root->balance = 0;

                if (temp2->balance == 1)
                    temp1->balance = -1;
                else
                    temp1->balance = 0;
                root = temp2;
                temp2->balance = 0;
            }
        }
    }

    void delIfChildren(TreeNode*& root, TreeNode*& q, bool& h)
    {
        if (root->right != nullptr) 
        {
            delIfChildren(root->right, q, h);
            if (h == true) 
            {
                balanceR(root, h);
            }
        }
        else
        {
            q->key = root->key;
            q->list = root->list;
            q = root;
            root = root->left;
            h = true;
        }
    }

    void clear(TreeNode*& root) 
    {
        if (root == nullptr) 
            return;
        clear(root->left);
        clear(root->right);
        root = nullptr;
        delete root;
        cout << "root eliminated";
    }

    void symmetric(TreeNode* p, ofstream& file)
    {
        if (p != nullptr)
        {
            symmetric(p->left, file);
            file << p->key.code << " " << p->key.product << " " << p->key.INN << p->key.data.day << "." << p->key.data.month << "." << p->key.data.year << endl;
            symmetric(p->right, file);
        }
    }

    bool search(TreeNode* p, Pole d)
    {
        if (p != nullptr)
        {
            if (p->key.product == d.product)
                return 1;

            if (p->key.product > d.product)
                return search(p->left, d);

            if (p->key.product < d.product)
                return search(p->right, d);

        }
        else
            return 0;
    }

    void add(TreeNode*& root, Pole data, unsigned long long INN, bool& h) 
    {
        TreeNode* temp1 = new TreeNode;
        TreeNode* temp2 = new TreeNode;
        if (root == nullptr) 
        {
            root = new TreeNode;
            root->key = data;
            root->balance = 0;
            root->list->add(INN);
            h = true;
        }
        else if (root->key.product < data.product)
        {
            add(root->left, data, INN, h);
            if (h == true) 
            {
                if (root->balance == 1)
                {
                    root->balance = 0;
                    h = false;
                }
                else if (root->balance == 0) 
                    root->balance = -1;
                else 
                {
                    temp1 = root->left;
                    if (temp1->balance == -1) 
                    {//LL
                        root->left = temp1->right;
                        temp1->right = root;
                        root->balance = 0;
                        root = temp1;
                    }
                    else 
                    {
                        temp2 = temp1->right;//2LR
                        temp1->right = temp2->left;
                        temp2->left = temp1;
                        root->left = temp2->right;
                        temp2->right = root;

                        if (temp2->balance == -1)
                            root->balance = 1;
                        else
                            root->balance = 0;
                        if (temp2->balance == +1)
                            temp1->balance = -1;
                        else 
                            temp1->balance = 0;
                        root = temp2;
                    }
                    root->balance = 0;
                    h = false;
                }
            }
        }
        else if (root->key.product > data.product)
        {
            add(root->right, data, INN, h);
            if (h == true) 
            {
                if (root->balance == -1) 
                {
                    root->balance = 0;
                    h = false;
                }
                else if (root->balance == 0)
                    root->balance = 1;
                else 
                {
                    temp1 = root->right;
                    if (temp1->balance == 1)
                    {//RR
                        root->right = temp1->left;
                        temp1->left = root;
                        root->balance = 0;
                        root = temp1;
                    }
                    else 
                    {//2RL
                        temp2 = temp1->left;
                        temp1->left = temp2->right;
                        temp2->right = temp1;
                        root->right = temp2->left;
                        temp2->left = root;

                        if (temp2->balance == 1) 
                        {
                            root->balance = -1;
                        }
                        else 
                        {
                            root->balance = 0;
                        }
                        if (temp2->balance == -1) 
                        {
                            temp1->balance = 1;
                        }
                        else 
                        {
                            temp1->balance = 0;
                        }
                        root = temp2;
                    }
                    root->balance = 0;
                    h = false;
                }
            }

        }
        else {
            root->list->add(data.INN);//ИНН если одинаковые в дереве
            h = false;
        }

    }

    void print(TreeNode* p, int k)
    {
        if (p == nullptr) return;
        else
        {
            print(p->right, k + 5);
            for (int i = 1; i <= k; i++)
            {
                cout << " ";
            }
            cout << p->key.code << " " << p->key.product << " " << p->key.INN << " " << p->key.data.day << "." << p->key.data.month << "." << p->key.data.year << endl;
            print(p->left, k + 5);
        }
    }

    void del(TreeNode*& root, Pole x, bool& h, unsigned long long  INN)
    {
        TreeNode* q = new TreeNode;
        if (root == nullptr) {
            return;
        }
        else if (root->key.product > x.product) 
        {
            del(root->left, x, h, INN);
            if (h == true) 
            {
                balanceL(root, h);
            }
        }
        else if (root->key.product < x.product)
        {
            del(root->right, x, h, INN);
            if (h == true)
            {
                balanceR(root, h);
            }
        }
        else {
            if (root->list->contains(INN) == true)
            {
                if (root->list->count() == 1) 
                {
                    q = root;
                    if (q->right == nullptr) 
                    {
                        root = q->left;
                        h = true;
                    }
                    else if (q->left == nullptr) 
                    {
                        root = q->right;
                        h = true;
                    }
                    else {
                        delIfChildren(q->left, q, h);
                        if (h == true)
                        {
                            balanceL(root, h);
                        }
                    }
                }

                else {
                    root->list->del(INN);
                    h = false;
                    return;
                }
            }
            else {
                cout << "no str in list";
                h = false;
                return;
            }
        }
    }

    void printAllLists(TreeNode* root)
    {
        if (root == nullptr) 
            return;
        root->list->print();
        printAllLists(root->left);
        printAllLists(root->right);
    }

public:

    ~tree()
    {
        clear(root);
    }

    bool add(Pole& pole)
    {
        bool h = true;
        add(root, pole, pole.INN, h);
        return true;
    }

    bool del(Pole& pole)
    {
        bool h = true;
        del(root, pole, h, pole.INN);
        return true;
    }

    bool symmetric(ofstream& file)
    {
        symmetric(root, file);
        return true;
    }

    bool search(Pole& pole)
    {
        search(root, pole);
        return true;
    }

    bool print()
    {
        print(root, 0);
        return true;
    }

    bool printAllLists()
    {
        printAllLists(root);
        return true;
    }
};