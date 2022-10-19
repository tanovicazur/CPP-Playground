#pragma once
#include <initializer_list>

template <typename T>
    class mojaLista {
    public:
        mojaLista();
        mojaLista(const std::initializer_list<T>& init_list);
        mojaLista(const mojaLista& other);
        mojaLista(mojaLista&& other);
        mojaLista& operator=(const mojaLista& other);
        mojaLista& operator=(mojaLista&& other);
        ~mojaLista();

        void clear();
        size_t size() const;
        bool empty() const;

        template <typename U>
        void push_back(U&& element);
        template <typename U>
        void push_front(U&& element);
        void pop_back();
        void pop_front();
        T& front();
        T& back();

        bool operator==(const mojaLista& other) const;
        bool operator!=(const mojaLista& other) const;

        class iterator;
        template <typename U>
        void insert(iterator position, U&& element);
        iterator erase(iterator position);
        template <typename U>
        iterator find (U&& element);
        iterator begin();
        iterator end();

    private:
        struct Node;
        Node* first_;
        Node* last_;
        size_t size_;
};

template <typename T>
struct mojaLista<T>::Node {
    T element;
    Node* prev;
    Node* next;

    Node(const T& e, Node* p = nullptr, Node* n = nullptr): element{e}, prev{p}, next{n} {};
    Node(T&& e, Node* p = nullptr, Node* n = nullptr): element{e}, prev{p}, next{n} {};
};

template <typename T>
mojaLista<T>::mojaLista(): first_{nullptr}, last_{nullptr}, size_{0} {};
template <typename T>
mojaLista<T>::mojaLista(const std::initializer_list<T>& init_list): first_{nullptr}, last_{nullptr}, size_{0} {
    for(auto it=init_list.begin(); it!=init_list.end(); ++it) {
        push_back(*it);
    }
    size_ = init_list.size();
}
template <typename T>
mojaLista<T>::mojaLista(const mojaLista& other): first_{nullptr}, last_{nullptr}, size_{0} {
    if(!other.empty()) {
        for(auto temp=other.first_; temp!=nullptr; temp=temp->next) {
            push_back(temp -> element);
        }
    }
}
template <typename T>
mojaLista<T>::mojaLista(mojaLista&& other): first_{other.first_}, last_{other.last_}, size_{other.size_} {
    other.first_ = other.last_ = nullptr;
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
    clear();
    first_ = other.first_;
    last_ = other.last_;
    size_ = other.size_;
    other.first_ = other.last_ = nullptr;
    other.size_ = 0;
    return *this;
}
template <typename T>
mojaLista<T>::~mojaLista() {
    clear();
}

template <typename T>
void mojaLista<T>::clear() {
    if(!empty()) {
        while(first_ != nullptr) {
            auto temp = first_;
            first_ = first_ -> next;
            delete temp;
            --size_;
        }
        last_ = nullptr;
    }
}
template <typename T>
size_t mojaLista<T>::size() const {
    return size_;
}
template <typename T>
bool mojaLista<T>::empty() const {
    return size_ == 0;
}

template <typename T>
template <typename U>
void mojaLista<T>::push_back(U&& element) {
    auto newNode = new Node{std::forward<U>(element)};
    if(empty()) {
        first_ = last_ = newNode;
    }
    else {
        newNode -> prev = last_;
        last_ -> next = newNode;
        last_ = newNode;
    }
    ++size_;
}
template <typename T>
template <typename U>
void mojaLista<T>::push_front(U&& element) {
    auto newNode = new Node{std::forward<U>(element)};
    if(empty()) {
        first_ = last_ = newNode;
    }
    else {
        newNode -> next = first_;
        first_ -> prev = newNode;
        first_ = newNode;
    }
    ++size_;
}
template <typename T>
void mojaLista<T>::pop_back() {
    if(!empty()) {
        auto temp = last_;
        last_ = last_ -> prev;
        last_ -> next = nullptr;
        delete temp;
        --size_;
    }
}
template <typename T>
void mojaLista<T>::pop_front() {
    if(!empty()) {
        auto temp = first_;
        first_ = first_ -> next;
        first_ -> prev = nullptr;
        delete temp;
        --size_;
    }
}
template <typename T>
T& mojaLista<T>::front() {
    return first_ -> element;
}
template <typename T>
T& mojaLista<T>::back() {
    return last_ -> element;
}

template <typename T>
bool mojaLista<T>::operator==(const mojaLista& other) const {
    if(size_ != other.size_) {
        return false;
    }
    auto temp1 = first_;
    auto temp2 = other.first_;
    while(temp1 != nullptr) {
        if(temp1 -> element != temp2 -> element) {
            return false;
        }
        temp1 = temp1 -> next;
        temp2 = temp2 -> next;
    }
    return true;
}
template <typename T>
bool mojaLista<T>::operator!=(const mojaLista& other) const {
    if(size_ != other.size_) {
        return true;
    }
    auto temp1 = first_;
    auto temp2 = other.first_;
    while(temp1 != nullptr) {
        if(temp1 -> element != temp2 -> element) {
            return true;
        }
        temp1 = temp1 -> next;
        temp2 = temp2 -> next;
    }
    return false;
}

template <typename T>
class mojaLista<T>::iterator: public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    iterator(): prevNode_{nullptr}, currentNode_{nullptr} {};
    iterator(Node* prev, Node* current): prevNode_{prev}, currentNode_{current} {};

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
    iterator& operator--() {
        currentNode_ = prevNode_;
        prevNode_ = prevNode_ -> prev;
        return *this;
    }
    iterator operator--(int) {
        auto temp = iterator(prevNode_, currentNode_);
        currentNode_ = prevNode_;
        prevNode_ = prevNode_ -> prev;
        return temp;
    }

    bool operator==(const iterator& other) const {
        return currentNode_ == other.currentNode_;
    }

    bool operator!=(const iterator& other) const {
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

template <typename T>
typename mojaLista<T>::iterator mojaLista<T>::erase(iterator position) {
    if (position == begin()) {
        pop_front();
        return begin();
    }
    else if (position.currentNode_ == last_) {
        pop_back();
        return end();
    }
    else {
        auto nodeToErase = position.currentNode_;
        position.prevNode_ -> next = position.currentNode_ -> next;
        position.currentNode_ = position.currentNode_ -> next;
        position.currentNode_ -> prev = position.prevNode_;
        delete nodeToErase;
        return position;
    }
}

template <typename T>
template <typename U>
void mojaLista<T>::insert(iterator position, U&& element) {
    if(position == begin()) {
        push_front(std::forward<U>(element));
    }
    else if(position == end()) {
        push_back(std::forward<U>(element));
    }
    else {
        auto newNode = new Node{std::forward<U>(element)};
        newNode -> next = position.currentNode_;
        newNode -> prev = position.prevNode_;
        position.currentNode_ -> prev = newNode;
        position.prevNode_ -> next = newNode;
    }
}

template <typename T>
template <typename U>
typename mojaLista<T>::iterator mojaLista<T>::find (U&& element) {
    Node* itc = first_;
    Node* itp = nullptr;
    while(itc != nullptr) {
        if(itc -> element == std::forward<U>(element)) {
            return iterator{itp, itc};
        }
        itp = itc;
        itc = itc -> next;
    }
    return end();
}
