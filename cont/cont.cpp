#include <iostream>
#include <iterator>
#include <concepts>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

struct Iterator
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Node;
    using pointer = Node*;
    using reference = Node&;

    Iterator(pointer ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }
    Iterator& operator++()//
    {
        m_ptr = m_ptr->next;
        return *this;
    }
    Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
    friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
    friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

private:
    pointer m_ptr;
};

template<typename T>
concept Positivchik = requires(T value)
{
    { value > 0 };
};

template <typename T, size_t N>
class MyList {

private:

public:
    Node* head;

    T begin()
    {
        return head;
    }
    T end()
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            temp = temp->next;
        }
        return temp;
    }

    MyList() = default;

    ~MyList() {}

    MyList(const MyList& other) : head(nullptr) {
        Node* temp = other.head;
        while (temp != nullptr)
        {
            add(temp->data);
            temp = temp->next;
        }
    }

    bool empty()
    {
        return (head == nullptr);
    }

    size_t size()
    {
        int s = 0;
        Node* temp = head;
        while (temp != nullptr)
        {
            temp = temp->next;
            s++;
        }
        return s;
    }

    size_t max_size()//
    {
        return 32;
    }

    void swap(MyList& other)//
    {
        Node* temp = head;
        head = other.head;
        other.head = temp;
    }

    void add(T Data) requires Positivchik<T>
    {
        Node* temp = new Node;
        temp->next = nullptr;
        temp->data = Data;
        if (head == nullptr)
            head = temp;
        else
        {
            temp->next = head;
        }
    }

    void del() 
    {
        Node* temp = head;
        if (temp == nullptr)
            return;
        else
        {
            do
            {
                temp = temp->next;
            } while (temp->next != nullptr);
        }
        delete temp;
    }

        bool operator==(MyList & other)//
        {
            Node* temp1 = head;
            Node* temp2 = other.head;
            while (temp1 != nullptr && temp2 != nullptr)
            {
                if (temp1->data != temp2->data)
                    return false;
                temp1 = temp1->next;
                temp2 = temp2->next;
            }

            return (temp1 == nullptr && temp2 == nullptr);
        }

        bool operator!=(MyList & other)
        {
            return !(*this == other);
        }

        MyList& operator=(MyList & other)
        {
            if (this == &other)
                return *this;
            while (head != nullptr)
            {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            Node* temp1 = other.head;
            while (temp1 != nullptr)
            {
                back(head, temp1->data);
                temp1 = temp1->next;
            }
            return *this;
        }

        void print() {//
            Node* temp = head;
            if (temp == nullptr) {
                cout << "list's empty" << endl;
                return;
            }
            do {
                cout << temp->data << endl;
                temp = temp->next;
            } while (temp != head);
            cout << endl;
        }

        void fill(T value) requires Positivchik<T>//xz chto s nim
        {
            Node* temp = head;
            //int i = 0;
            do
            {
                temp->data = value;
                temp = temp->next;
               // i++;
            } while (temp->next != nullptr);
        }

        struct Iterator
        {
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

            Iterator(pointer ptr) : m_ptr(ptr) {}

            reference operator*() const { return *m_ptr; }
            pointer operator->() { return m_ptr; }
            Iterator& operator++()
            {
                m_ptr = m_ptr->next;
                return *this;
            }
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
            friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

        private:
            pointer m_ptr;
        };
};

 
template<typename T, size_t N>
void swap(MyList<T,N>l1, MyList<T, N>l2)
{
    Node* temp1 = l1.head;
    Node* temp2 = l2.head;
    while (temp1 != nullptr && temp2 != nullptr)
    {
        int temp = temp1->data;
        temp1->data = temp2->data;
        temp2->data = temp;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
}

int main()
{
    MyList<int, 5> mylist;
    MyList<int, 5> mylist2(mylist);
   // mylist.fill(52);
    mylist.add(52);
    mylist.add(52);
    mylist2.add(33);
    swap(mylist, mylist2);
    mylist2.print();
    mylist.print();
    return mylist.empty();
}




//void print(Node*& head);
//void free(Node*& head);
//void poisk(Node*& head, int data);
//void razn(Node* head1, Node* head2, Node*& head3);
//void delnext(Node*& head, int data);

/*void free(Node*& head) {
    Node* temp = head;
    Node* del = nullptr;
    if (temp != nullptr) {
        do {
            del = temp;
            temp = temp->next;
            delete del;
        } while (temp != head);
    }
    head = nullptr;
}


void poisk(Node*& head, int data) {
    Node* temp = head;
    bool f = false;
    if (temp == nullptr) {
        cout << "лист пуст" << endl;
        return;
    }
    do {
        if (temp->data == data) {
            cout << "значение " << data << " найдено в списке, адрес =  " << temp << endl;
            f = true;
        }
        temp = temp->next;
    } while (temp != head);
    if (f == false) {
        cout << "значения " << data << " нет в списке" << endl;
    }
}

void razn(Node* head1, Node* head2, Node*& head3) {
    Node* temp1 = head1;
    Node* temp2 = head2;
    if ((temp1 == nullptr) && (head2 == nullptr)) {
        cout << "списки пусты" << endl;
        return;
    }
    if (temp1 == nullptr) {
        cout << "1-ый список пуст" << endl;
        return;
    }
    if (head2 == nullptr) {
        cout << "2-ой список пуст" << endl;
        return;
    }
    do {
        bool found = false;
        if (temp2 != nullptr) {
            do {
                if (temp1->data == temp2->data) {
                    found = true;
                }
                temp2 = temp2->next;
            } while (temp2 != head2);
        }
        if (!found) {
            back(head3, temp1->data);
        }
        temp1 = temp1->next;
    } while (temp1 != head1);
    if (head3 == nullptr) {
        cout << "список: " << endl;
        return;
    }

}
} */