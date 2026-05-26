#ifndef CIRCULAR_LIST_HPP
#define CIRCULAR_LIST_HPP

#include <iostream>
#include <cstddef>
#include <utility>

template<typename T>
class CircularList {
public:
    CircularList();
    CircularList(const CircularList& other);
    CircularList(CircularList&& other) noexcept;
    CircularList& operator=(const CircularList& other);
    CircularList& operator=(CircularList&& other) noexcept;
    ~CircularList() noexcept;

    void insert_after(const T& data);
    void insert_before(const T& data);
    void remove_current();
    void move_next();
    void move_prev();
    void clear() noexcept;
    
    size_t size() const { return len; }
    bool empty() const { return len == 0; }
    T& current() { return now->data; }
    const T& current() const { return now->data; }
    void print() const;

private:
    struct Node {
        T data;
        Node* pred;
        Node* next;
        Node(const T& d, Node* p = nullptr, Node* n = nullptr) 
            : data(d), pred(p), next(n) {}
    };
    size_t len = 0;
    Node* now = nullptr;
};

// === Реализация (обязательно в заголовке для шаблонов) ===

template<typename T>
CircularList<T>::CircularList() : len(0), now(nullptr) {}

template<typename T>
CircularList<T>::~CircularList() noexcept { clear(); }

template<typename T>
void CircularList<T>::clear() noexcept {
    while (len > 0) remove_current();
}

template<typename T>
void CircularList<T>::insert_after(const T& data) {
    if (len == 0) {
        now = new Node(data);
        now->pred = now;
        now->next = now;
    } else {
        Node* nd = new Node(data, now, now->next);
        nd->next->pred = nd;
        now->next = nd;
        now = nd;
    }
    ++len;
}

template<typename T>
void CircularList<T>::insert_before(const T& data) {
    if (len == 0) {
        now = new Node(data);
        now->pred = now;
        now->next = now;
    } else {
        Node* nd = new Node(data, now->pred, now);
        nd->pred->next = nd;
        now->pred = nd;
        now = nd;
    }
    ++len;
}

template<typename T>
void CircularList<T>::remove_current() {
    if (len == 0) {
        std::cout << "List is empty\n";
        return;
    }
    Node* tmp = now;
    if (len == 1) {
        now = nullptr;
    } else {
        tmp->pred->next = tmp->next;
        tmp->next->pred = tmp->pred;
        now = tmp->next;
    }
    --len;
    delete tmp;
}

template<typename T>
void CircularList<T>::move_next() {
    if (len > 0) now = now->next;
}

template<typename T>
void CircularList<T>::move_prev() {
    if (len > 0) now = now->pred;
}

template<typename T>
CircularList<T>::CircularList(const CircularList& other) : len(0), now(nullptr) {
    if (other.len == 0) return;
    Node* cur = other.now;
    for (size_t i = 0; i < other.len; ++i) {
        insert_after(cur->data);
        cur = cur->next;
    }
}

template<typename T>
CircularList<T>::CircularList(CircularList&& other) noexcept 
    : len(other.len), now(other.now) {
    other.len = 0;
    other.now = nullptr;
}

template<typename T>
CircularList<T>& CircularList<T>::operator=(const CircularList& other) {
    if (this != &other) {
        clear();
        if (other.len > 0) {
            Node* cur = other.now;
            for (size_t i = 0; i < other.len; ++i) {
                insert_after(cur->data);
                cur = cur->next;
            }
        }
    }
    return *this;
}

template<typename T>
CircularList<T>& CircularList<T>::operator=(CircularList&& other) noexcept {
    if (this != &other) {
        clear();
        len = other.len;
        now = other.now;
        other.len = 0;
        other.now = nullptr;
    }
    return *this;
}

template<typename T>
void CircularList<T>::print() const {
    if (len == 0) {
        std::cout << "(empty)\n";
        return;
    }
    Node* cur = now;
    for (size_t i = 0; i < len; ++i) {
        std::cout << (i == 0 ? "[CUR] " : "      ") << cur->data << "\n";
        cur = cur->next;
    }
}

#endif