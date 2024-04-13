#include <iostream>
#include <iterator>
#include <concepts>
using namespace std;

struct Node
{
    int data;
    Node* next;
};


template<Node* value>
concept Positive = value->data > 0;

template <typename T, size_t N>
class MyList {

private:

    Node* head;
public:

    MyList() = default;//1

    ~MyList() //6
    {
        Node* temp = head;
        Node* temp1 = nullptr;
        if (temp != nullptr) {
            do {
                temp1 = temp;
                temp = temp->next;
                delete temp1;
            } while (temp != nullptr);
        }
        head = nullptr;
    }

    const MyList cbegin()//9
    {
        return head;
    }
    
    const MyList cend()//10
    {
        Node* temp = head;
        while (temp->next!=nullptr)
            temp = temp->next;
        return temp;
    }


    MyList begin()//7
    {
        return head;
    }
    

    MyList end()//8
    {
        Node* temp = head;
        while (temp->next!=nullptr)
            temp = temp->next;
        return temp;
    }


    MyList(const MyList& other) : head(nullptr) {//2
        Node* temp = other.head;
        while (temp != nullptr)
        {
            add(temp->data);
            temp = temp->next;
        }
    }

    MyList(MyList&& l):head(nullptr)//3
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
        Node* temp = head;
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
        Node* temp = head;
        head = other.head;
        other.head = temp;
    }

    void add(T Data) 
    {
        Node* temp = new Node;
        temp->next = head;
        temp->data = Data;
        head = temp;
    }

    void fill(T Ddata)
    {
        for (int i = 0; i < N; i++)
        {
            add(Ddata);
        }
    }

    void del()//
    {
        Node* temp = head;
        if (temp == nullptr)
            return;
        while (temp->next != nullptr);
        {
            temp = temp->next;
        }
        Node* del = temp->next;
        temp->next = del->next;
        delete del;
    }

    bool operator==(MyList& other)//11
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

    void print() {
        Node* temp = head;
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
        Node* temp = head;
        Node* temp1 = nullptr;
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
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

        Iterator() = default;
        ~Iterator() = default;
        Iterator(const Iterator&) = default;
        Iterator& operator=(const Iterator&) = default;
        Iterator operator+ (difference_type goga)
        {
            return Iterator(m_ptr + goga);
        }

        Iterator operator- (difference_type goga)
        {
            return Iterator(m_ptr - goga);
        }
        reference operator[](difference_type goga) 
        { 
            auto boba = *this;
            boba += goga;
            return boba;
        }
        Iterator& operator+=(difference_type gogga)
        {
            return *this += gogga;
        }

        Iterator& operator-=(difference_type goga)
        {
            return *this += -goga;
        }
            
      //  difference_type operator-(const Iterator& lhs, const Iterator& rhs)
      // {
      //      return rhs - lhs;
      // }

        difference_type operator-(const Iterator& other)
        {
            return m_ptr - other.m_ptr;
        }


    private:
        pointer m_ptr;
    };

    struct ConstIterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        ConstIterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        ConstIterator& operator++() { m_ptr++; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const ConstIterator& a, const ConstIterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const ConstIterator& a, const ConstIterator& b) { return a.m_ptr != b.m_ptr; };

        ConstIterator() = default;
        ~ConstIterator() = default;
        ConstIterator(const ConstIterator&) = default;
        ConstIterator& operator=(const ConstIterator&) = default;
        ConstIterator operator+ (difference_type goga)
        {
            return ConstIterator(m_ptr + goga);
        }

        ConstIterator operator- (difference_type goga)
        {
            return ConstIterator(m_ptr - goga);
        }
        reference operator[](difference_type goga)
        {
            auto boba = *this;
            boba += goga;
            return boba;
        }
        ConstIterator& operator+=(difference_type gogga)
        {
            return *this += gogga;
        }

        ConstIterator& operator-=(difference_type goga)
        {
            return *this += -goga;
        }

        //  difference_type operator-(const Iterator& lhs, const Iterator& rhs)
        // {
        //      return rhs - lhs;
        // }

        difference_type operator-(const ConstIterator& other)
        {
            return m_ptr - other.m_ptr;
        }


    private:
        pointer m_ptr;
    };

};


template<typename T, size_t N>
void swap(MyList<T, N>l1, MyList<T, N>l2)//14
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
    MyList <int, 5> list1;
    MyList <int, 5>list2;
    list1.add(2);
    list1.add(3);
    list2.fill(52);
    list2.print();
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
