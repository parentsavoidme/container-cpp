//#include <concepts>

template <typename T>
concept Positivchik = requires(T value) 
{
    { value > 0 };// номер в очереди>0
};

template <typename T, size_t N>
class Queue {// для любителей почитать
public:
    T data[N];
    int frontIndex;
    int backIndex;
    int count;

    Queue() = default;
 
    Queue(const Queue& other) : frontIndex(other.frontIndex), backIndex(other.backIndex), count(other.count) {
        for (int i = 0; i < N; ++i) 
        {
            data[i] = other.data[i];
        }
    }

    ~Queue() {  }


    Queue& operator=(const Queue& other) 
    {
        if (this != &other) {
            frontIndex = other.frontIndex;
            backIndex = other.backIndex;
            count = other.count;
            for (int i = 0; i < N; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    int size()
    {
        return count;
    }

    bool operator==(const Queue& other)
    {
      if (count != other.count)
            return false;
        for (int i = 0; i < N; i++)
        {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    bool operator!=(const Queue& other)
    {
        return !(*this == other);
    }

    bool Empty()  {
        return count == 0;
    }

    bool Fully()
    {
        return count == N;
    }


    int max_size()
    {
        return 20;
    }

    void swap(Queue& other)
    {
        int temp1 = other.count;
        other.count = count;
        count = temp1;
        int temp2 = other.frontIndex;
        other.frontIndex = frontIndex;
        frontIndex = temp2;
        int temp3 = other.backIndex;
        other.backIndex = backIndex;
        backIndex = temp3;
        for (int i = 0; i < N; i++)
        {
            auto a = data[i];
            data[i] = other.data[i];
            other.data[i] = a;
        }        
    }

    void push(T value) requires Positivchik<T> {
        if (Fully())
        {
            std::cout << "no space"<<"\n";
            return;
        }
        data[backIndex] = value;
        ++backIndex;
        ++count;
      
    }

    void pop() {
        if (Empty())
        {
            std::cout << "no readers"<<"\n";
            return;
        }
        ++frontIndex;
        --count;
    }

    T begin()  {
        return data[frontIndex];
    }

    T end() {
        int lastIndex = (backIndex - 1 + N) % N;
        return data[lastIndex];
    }

    void fill(const T& value)
    {
        for (int i = 0; i < N; i++)
            data[i] = value;
    }

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        T* current;

        Iterator(T* ptr) : current(ptr) {}

        Iterator& operator++() {
            ++current;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.current == b.current;
        }

        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return !(a == b);
        }

        reference operator*() {
            return *current;
        }

        pointer operator->() {
            return current;
        }
    };

    using iterator = Iterator;
    using const_iterator = Iterator;

    const_iterator begin() const {
        return const_iterator(data + frontIndex);
    }

    const_iterator end() const {
        return const_iterator(data + backIndex);
    }

};

template<typename T, size_t N>

void swap(Queue<T, N>& q1, Queue<T, N>& q2) {
    int temp1 = q1.count;
    q1.count = q2.count;
    q2.count = temp1;
    int temp2 = q1.frontIndex;
    q1.frontIndex = q2.frontIndex;
    q2.frontIndex = temp2;
    int temp3 = q1.backIndex;
    q1.backIndex = q2.backIndex;
    q2.backIndex = temp3;
    for (int i = 0; i < N; i++) {
        auto a = q1.data[i];
        q1.data[i] = q2.data[i];
        q2.data[i] = a;
    }
}

int main()
{
    Queue<int, 5>q1 = {};
    q1.push(5);
    q1.push(7);
    Queue<int, 5>q2(q1);
    std::cout << q1.begin() << std::endl;
    std::cout << q1.end() << std::endl;
    return q2.begin();
}
