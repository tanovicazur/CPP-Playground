#pragma once
#include <iostream>

template <typename T>
class mojaLista {
public:
    mojaLista();
    mojaLista(const mojaLista&);
    mojaLista(mojaLista&&);
    mojaLista& operator= (const mojaLista&);
    mojaLista& operator= (mojaLista&&);
    ~mojaLista();

    void clear();
    bool empty();
    void push_back(const T&);
    void push_back(T&&);

    class iterator;
    iterator begin();
    iterator end();

    void add(T);
    template <typename U>
    iterator find(U predicate);
    void remove(iterator);

    friend std::ostream& operator<<(std::ostream& out, const mojaLista& lista) {
        for(auto temp=lista.first_; temp!=nullptr; temp=temp->next) {
            out << temp -> element << " ";
        }
        return out << std::endl;
    }

private:
    struct Node;
    Node* first_;
    Node* last_;
    size_t size_;
};

template <typename T>
struct mojaLista<T>::Node {
    T element;
    Node* next;

    Node(const T& e, Node* n = nullptr): element{e}, next{n} {};
    Node(T&& e, Node* n = nullptr): element{e}, next{n} {};
    ~Node() = default;
};

template <typename T>
mojaLista<T>::mojaLista(): first_{nullptr}, last_{nullptr}, size_{0} {};

template <typename T>
mojaLista<T>::mojaLista(const mojaLista& other): first_{nullptr}, last_{nullptr}, size_{0} {
    for(auto temp=other.first_; temp!=nullptr; temp=temp->next) {
        push_back(temp -> element);
    }
}

template <typename T>
mojaLista<T>::mojaLista(mojaLista&& other): first_{other.first_}, last_{other.last_}, size_{other.size_} {
    other.last_ = other.first_ = nullptr;
    other.size_ = 0;
}

template <typename T>
mojaLista<T>& mojaLista<T>::operator=(const mojaLista& other) {
    if(this != &other) {
        clear();
        for(auto temp=other.first_; temp!=nullptr; temp=temp->next) {
            push_back(temp -> element);
        }
    }
    return *this;
}

template <typename T>
mojaLista<T>& mojaLista<T>::operator=(mojaLista&& other) {
    if(this != &other) {
        clear();
        first_ = other.first_;
        last_ = other.last_;
        size_ = other.size_;
        other.first_ = other.last_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
mojaLista<T>::~mojaLista() {
    clear();
}

template <typename T>
void mojaLista<T>::clear() {
    while(first_ != nullptr) {
        auto temp = first_;
        first_ = first_ -> next;
        delete temp;
        --size_;
    }
    first_ = last_ = nullptr;
}

template <typename T>
bool mojaLista<T>::empty() {
    return size_ == 0;
}

template <typename T>
void mojaLista<T>::push_back(const T& element) {
    auto newNode = new Node{element};
    if(size_ == 0) {
        last_ = newNode;
        first_ = newNode;
    }
    else {
        last_ -> next = newNode;
        last_ = newNode;
    }
    ++size_;
}

template <typename T>
void mojaLista<T>::push_back(T&& element) {
    auto newNode = new Node{std::move(element)};
    if(size_ == 0) {
        last_ = first_ = newNode;
    }
    else {
        last_ -> next = newNode;
        last_ = newNode;
    }
    ++size_;
}

template <typename T>
void mojaLista<T>::add(T element) {
    auto newNode = new Node{element};
    if(size_ == 0) {
        first_ = last_ = newNode;
        ++size_;
    }
    else if(!(first_ -> element < element)) {
        newNode -> next = first_;
        first_ = newNode;
        ++size_;
    }
    else if(last_ -> element < element) {
        last_ -> next = newNode;
        last_ = newNode;
        ++size_;
    }
    else {
        auto temp1 = first_;
        auto temp2 = first_ -> next;
        while(temp2 != nullptr) {
            if(!(element < temp1->element) && !(temp2->element < element)) {
                temp1 -> next = newNode;
                newNode -> next = temp2;
                ++size_;
                break;
            }
            temp1 = temp1 -> next;
            temp2 = temp2 -> next;
        }
    }
}

template <typename T>
template <typename U>
typename mojaLista<T>::iterator mojaLista<T>::find(U predicate) {
    Node* itc = first_;
    Node* itp = nullptr;
    while(itc != nullptr) {
        if(predicate(itc -> element)) {
            return iterator{itp, itc};
        }
        itp = itc;
        itc = itc -> next;
    }
    return end();
}

template <typename T>
void mojaLista<T>::remove(iterator it) {
    if(it.currentNode_ == first_ && it.prevNode_ == nullptr) {
        if(size_ == 0) {
            return;
        }
        else if(size_ == 1) {
            delete first_;
            first_ = last_ = nullptr;
        }
        else {
           auto temp = first_;
           first_ = first_ -> next;
           delete temp;
        }
        --size_;
    }
    else if (it.currentNode_ == last_) {
        it.prevNode_ -> next = nullptr;
        last_ = it.prevNode_;
        delete it.currentNode_;
        --size_;
    }
    else {
        it.prevNode_ -> next = it.currentNode_ -> next;
        delete it.currentNode_;
        --size_;
    }
}

template <typename T>
class mojaLista<T>::iterator: public std::iterator<std::forward_iterator_tag, T> {
public:
    iterator(): prevNode_{nullptr}, currentNode_{nullptr} {};
    iterator(Node* prev, Node* current):
        prevNode_{prev}, currentNode_{current} {};

    iterator& operator++() {
        prevNode_ = currentNode_;
        currentNode_ = currentNode_ -> next;
        return *this;
    }
    iterator operator++(int) {
        auto temp = iterator(prevNode_, currentNode_);
        prevNode_ = currentNode_;
        currentNode_ = currentNode_ -> next;
        return temp;
    }

    bool operator==(const iterator& other) {
        return currentNode_ == other.currentNode_;
    }

    bool operator!=(const iterator& other) {
        return currentNode_ != other.currentNode_;
    }

    T& operator*() {
        return currentNode_ -> element;
    }
    T* operator->() {
        return &currentNode_ -> element;
    }

    Node* prevNode_;
    Node* currentNode_;
};

template <typename T>
typename mojaLista<T>::iterator mojaLista<T>::begin() {
    return iterator{nullptr, first_};
}

template <typename T>
typename mojaLista<T>::iterator mojaLista<T>::end() {
    return iterator{last_, nullptr};
}
