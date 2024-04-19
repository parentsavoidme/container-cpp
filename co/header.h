#include <iostream>
#include <iterator>
#include <cstddef>
#include <concepts>
using namespace std;

template <typename T>
 
struct Node
{
    T data;
    Node<T>* next;
};


template <typename T,size_t N>
concept NoMoreThan = sizeof(T) <= N;

template <typename T, size_t N>
class MyList {

private:
    int count;
    Node<T>* head;
public:

    MyList() = default;//1

    ~MyList() //6
    {
        Node<T>* temp = head;
        Node<T>* temp1 = nullptr;
        if (temp != nullptr) {
            do {
                temp1 = temp;
                temp = temp->next;
                delete temp1;
            } while (temp != nullptr);
        }
        head = nullptr;
    }

    MyList(const MyList& other) : head(nullptr) {//2
        Node<T>* temp = other.head;
        while (temp != nullptr)
        {
            add(temp->data);
            temp = temp->next;
        }
    }

    MyList(MyList&& l) :head(nullptr)//3
    {
        *this = std::move(l);
    }

    MyList& operator =(MyList&& l)//5
    {
        if (this != &l)
        {
            this->free();
            this->head = l.head;
            l.free();
        }

    }

    bool empty()//17
    {
        return (head == nullptr);
    }

    size_t size()//16
    {
        int ss = 0;
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            temp = temp->next;
            ss++;
        }
        return ss;
    }

    size_t max_size()//15
    {
        return 32;
    }

    void swap(MyList& other)//13
    {
        Node<T>* temp = head;
        int c = this->count;
        this->count = other.count;
        other.count = c;
        head = other.head;
        other.head = temp;
    }

    void add(T Data)
    {
       if (count < N)
       {
            //Node* temp = new Node;
            Node<T>* temp = new Node<T>;
            temp->next = head;
            temp->data = Data;
            head = temp;
            count++;
       }
        //else
        //    cout << "list full"<<endl;
    }

    void fill(T Ddata)
    {
        for (int i = 0; i < N; i++)
        {
            add(Ddata);
        }
    }

    void del()
    {
        Node<T>* temp = head;
        if (temp == nullptr)
            return;
        else if (temp->next == nullptr)
        {
            this->free();
        }
        else
        {
            while (temp->next->next != nullptr)
                temp = temp->next;

            delete temp->next;
            temp->next = nullptr;
        }
        count--;
    }

    bool operator==(MyList& other)//11
    {
        Node<T>* temp1 = head;
        Node<T>* temp2 = other.head;
        while (temp1 != nullptr && temp2 != nullptr)
        {
            if (temp1->data != temp2->data)
                return false;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        return (temp1 == nullptr && temp2 == nullptr);
    }

    bool operator!=(MyList& other)//12
    {
        return !(*this == other);
    }

    MyList& operator=(MyList& other)//4
    {
        if (this == &other)
            return *this;
        while (head != nullptr)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        Node<T>* temp1 = other.head;
        while (temp1 != nullptr)
        {
            add(head, temp1->data);
            temp1 = temp1->next;
        }
        return *this;
    }

    void print() {
        Node<T>* temp = head;
        if (temp == nullptr) {
            cout << "list's empty" << endl;
            return;
        }
        do {
            cout << temp->data << endl;
            temp = temp->next;
        } while (temp != nullptr);
        cout << endl;
    }

    void free() {
        Node<T>* temp = head;
        Node<T>* temp1 = nullptr;
        if (temp != nullptr) {
            do {
                temp1 = temp;
                temp = temp->next;
                delete temp1;
            } while (temp != nullptr);
        }
        head = nullptr;
    }

    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Node<T>;
        using pointer = Node<T>*;
        using reference = Node<T>&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++()
        {
            m_ptr = m_ptr->next;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this; m_ptr = m_ptr->next; return tmp;
        }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
    };

    struct ConstIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const Node<T>;
        using pointer = const Node<T>*;
        using reference = const Node<T>&;

        ConstIterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        ConstIterator& operator++() { m_ptr=m_ptr->next; return *this; }
        ConstIterator operator++(int) { Iterator tmp = *this; m_ptr = m_ptr->next; return tmp; }
        friend bool operator== (const ConstIterator& a, const ConstIterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const ConstIterator& a, const ConstIterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
    };

    ConstIterator cbegin()//9
    {
        return ConstIterator(head);
    }

    ConstIterator cend()//10
    {
        return ConstIterator(nullptr);
    }


    Iterator begin()//7
    {
        return Iterator(head);
    }


    Iterator end()//8
    {
        return Iterator(nullptr);
    }

};


template<typename T, size_t N>
void swap(MyList<T, N>& l1, MyList<T, N>& l2) 
{
    l1.swap(l2);
}










