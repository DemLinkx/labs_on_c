#include <iostream>
template<typename T>
class CircularList;

template<typename T>
class Node{
friend class CircularList<T>;
public:
Node(const T& data, Node* pred = NULL, Node* next = NULL);
private:
T data = T();
Node* pred = NULL;
Node* next = NULL;
};

template<typename T>
Node<T>::Node(const T& data, Node* pred, Node* next){
this->data = data;
this->pred = pred;
this->next = next;
}

template<typename T>
class CircularList{
public:
CircularList();
CircularList(CircularList<T>&& other) noexcept;
CircularList(const CircularList<T>& other);
CircularList<T>& operator=(const CircularList<T>& other);
CircularList<T>& operator=(CircularList<T>&& other);
~CircularList() noexcept;
void insert_after(T data);
void insert_before(T data);
void remove_current();
void move_next();
void move_prev();
void clean() noexcept;
size_t get_len() const {return this->len;}
bool is_empty() const {return !bool(this->len);}
T& current() {return this->now->data;}
private:
size_t len = 0;
Node<T>* now = NULL;
};

template<typename T>
CircularList<T>& CircularList<T>::operator=(CircularList<T>&& other){
if (this != &other){
this->clean();
this->len = other.len;
this->now = other.now;
other.len = 0;
other.now = NULL;
}
return *this;
}

template<typename T>
CircularList<T>& CircularList<T>::operator=(const CircularList<T>& other){
if(this != &other){
this->clean();
if (other.len == 0) return *this;
auto start = other.now;
for (size_t i = 0; i < other.len; i++){
this->insert_after(start->data);
start = start->next;
}
}
return *this;
}

template<typename T>
CircularList<T>::CircularList(CircularList<T>&& other) noexcept{
this->len = other.len;
this->now = other.now;
other.len = 0;
other.now = NULL;
}

template<typename T>
CircularList<T>::CircularList(const CircularList<T>& other){
this->len = 0;
this->now = NULL;
if (other.len == 0) return;
auto start = other.now;
for (size_t i = 0; i < other.len; i++){
this->insert_after(start->data);
start = start->next;
}
}

template<typename T>
void CircularList<T>::insert_after(T data){
if (this->len == 0){
Node<T>* nd = new Node(data, NULL, NULL);
nd->pred = nd;
nd->next = nd;
this->now = nd;
this->len = 1;
} else {
Node<T>* nd = new Node(data, this->now, this->now->next);
nd->next->pred = nd;
this->now->next = nd;
this->now = nd;
this->len++;
}
}

template<typename T>
void CircularList<T>::insert_before(T data){
if (this->len == 0){
Node<T>* nd = new Node(data, NULL, NULL);
nd->pred = nd;
nd->next = nd;
this->now = nd;
this->len = 1;
} else {
Node<T>* nd = new Node(data, this->now->pred, this->now);
nd->pred->next = nd;
this->now->pred = nd;
this->now = nd;
this->len++;
}
}

template<typename T>
void CircularList<T>::remove_current(){
if (this->len == 0){
std::cout << "list is empty";
return;
}
Node<T>* dltnd = this->now;
if (this->len == 1){
this->now = NULL;
this->len = 0;
delete dltnd;
} else {
dltnd->pred->next = dltnd->next;
dltnd->next->pred = dltnd->pred;
this->now = dltnd->next;
this->len--;
delete dltnd;
}
}

template<typename T>
void CircularList<T>::move_next(){
if (this->len > 0){
this->now = this->now->next;
}
}

template<typename T>
void CircularList<T>::move_prev(){
if (this->len > 0){
this->now = this->now->pred;
}
}

template<typename T>
void CircularList<T>::clean() noexcept{
if (this->len == 0){
return;
}
while (this->len != 0){
this->remove_current();
}
}

template<typename T>
CircularList<T>::~CircularList() noexcept{
this->clean();
}

int main(){
    ;
}