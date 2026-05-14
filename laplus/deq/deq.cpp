#include <iostream>

// Deq: Head (front) - - - Tail (back)
// Node: [<-pred -- data -- next->]

template<typename T>
class Deq;

template<typename T>
class Node{
    friend class Deq<T>; 
    public:
        Node(const T& data, Node* pred = NULL, Node* next = NULL); 
            // ии сказал что конструктора по умолчанию 
            // не хватит и надо свой писать,
            // но я не совсем понимаю почему, типо это просто дурной тон, или прям ошибка?
            // но при этом если осатвить конструктор по умолчанию, 
            // то все скомпилируется нормально
    private:
        T data = T(); // типо для int будет 0, для double 0.0, для string = '' итд
        Node* pred = NULL;
        Node* next = NULL;
        
};


template<typename T>
Node<T>::Node(const T& data, Node* pred, Node* next){ 

    // хотелось два раза указать значения по умолчанию, 
    // ибо сигнатуры должны совпадать, но по идее если разрешить параметры по умолчанию и там и там,
    // то может быть двойное определение и будет плохо

    this->data = data;
    this->pred = pred;
    this->next = next;
}

template<typename T>
class Deq{
    public:
        Deq();
        Deq(Deq<T>&& other) noexcept; // обязательно ли писать noexcept 
        Deq(const Deq<T>& other);  // что будет если я не сделаю ссылку константной? 
        Deq<T>& operator=(const Deq<T>& other);
        Deq<T>& operator=(Deq<T>&& other); // возвращаем всегда Lvalue 
        ~Deq() noexcept; // без noexcept типо медленнее ?

        void push_back(T data);
        void push_front(T data);
        void pop_back();
        void pop_front();
        void clean() noexcept;
        size_t get_len() const {return this->len;};
        bool is_empty() const {return !bool(this->len);};

    private:
        size_t len = 0;
        Node<T>* head = NULL; // Нужно ли заменить на nullptr? Типо это более безопасно?
        Node<T>* tail = NULL;
};

template<typename T>
Deq<T>& Deq<T>::operator=(Deq<T>&& other){ // Lvalue(Rvalue)
    if (this != &other){
        this->clean(); // ???
        this->len = other.len;
        this->head = other.head;
        this->tail = other.tail;
        other.len = 0;
        other.head = NULL;
        other.tail = NULL;
    }
    return *this;
}

template<typename T>
Deq<T>& Deq<T>::operator=(const Deq<T>& other){  // Lvalue(Lvalue)
    if(this != &other){
        this->clean();
        auto start = other.head; // Node<T>*
        for (int i = 0; i < other.len; i++){
            this->push_back(start->data);
            start = start->next; 
        }
    }
    return *this;
}

template<typename T>
Deq<T>::Deq(Deq<T>&& other) noexcept{ // лутаемся
    this->len = other.len;
    this->head = other.head;
    this->tail = other.tail;
    other.len = 0;
    other.head = NULL;
    other.tail = NULL;
}

template<typename T>
Deq<T>::Deq(const Deq<T>& other){
    this->len = 0;
    this->head = NULL;
    this->tail = NULL;
    auto start = other.head; // Node<T>*
        for (int i = 0; i < other.len; i++){
            this->push_back(start->data);
            start = start->next; 
    }
}


template<typename T>
void Deq<T>::push_back(T data){
    Node<T>* nd = new Node(data, this->tail, NULL); // вроде не нужно проверять bad alloc?

    if(this->len == 0){
        this->tail = nd;
        this->head = nd;
        this->len++;
    }
    else{
        this->tail->next = nd;
        this->tail = nd;
        this->len++;
    }
}

template<typename T>
void Deq<T>::push_front(T data){
    Node<T>* nd = new Node(data, NULL, this->head);
    
    if (this->len == 0){
        this->head = nd;
        this->tail = nd;
        this->len++;
    } else{
        this->head->pred = nd;
        this->head = nd;
        this->len++;
    }
}

template<typename T>
void Deq<T>::pop_front(){
    if (this->len == 0){
        std::cout<<"list is empty";
        return;
    }else{
        Node<T>* dltnd = this->head;
        this->len--; // чтобы не писать два раза -- для последнего узла и для какого-то

        if (this->len == 0){
            this->head = NULL;
            this->tail = NULL;
            delete dltnd;

        }else{
            this->head = dltnd->next;
            dltnd->next->pred = NULL;
            delete dltnd;

        }
    }
    ;
}

//(head)[NULL, ...,  next->] - [<-pred, ..., next->] - ... - [<-pred, ..., next->] - [<-pred, ..., NULL](tail)

template<typename T>
void Deq<T>::pop_back(){

    if (this->len == 0){
        std::cout<<"list is empty";
        return;
    }else{
        Node<T>* dltnd = this->tail;
        this->len--; // чтобы не писать два раза -- для последнего узла и для какого-то

        if (this->len == 0){
            this->head = NULL;
            this->tail = NULL;
            delete dltnd;

        }else{
            this->tail = dltnd->pred;
            dltnd->pred->next = NULL;

            delete dltnd;
        }
    }
    ;
}

template<typename T>
void Deq<T>::clean() noexcept{
    if (this->len == 0){
        std::cout<<"list is empty";
        return;
    }
    while (this->len != 0){
        this->pop_back();
    }
}


template<typename T>
Deq<T>::~Deq() noexcept{
    this->clean();
}
