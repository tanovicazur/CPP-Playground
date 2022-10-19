#pragma once

#include <iostream>
#include <functional>
#include <stdexcept>

template <typename T>
class Heap{
    public:
    Heap();
    Heap(const Heap&);
    Heap(Heap&&);
    Heap& operator=(const Heap&);
    Heap& operator=(Heap&&);
    friend std::ostream& operator<<(std::ostream& out, Heap& heap){
        auto lambda = [&out, &heap](int pos){
            out << heap.heap_[pos] << " ";
        };
        heap.inorder(lambda, 0);
        out << std::endl;
        return out;
    }
    T& min();
    T& max();
    template <typename U>
    Heap& insert(U&&);
    Heap& removeMin();
    Heap& removeMax();
    ~Heap();


    private:
    int parent(int) const;
    int leftChild(int) const;
    int rightChild(int) const;
    void balanseDown(int);
    void balanseUp(int);
    void reallocate();
    int minIndex();
    template <typename Lambda>
    void inorder(Lambda, int);
    size_t cap_;
    size_t size_;
    T* heap_;
};

template <typename T>
Heap<T>::Heap() : cap_{15}, size_{0}, heap_{new T[cap_]}{}

template <typename T>
Heap<T>::Heap(const Heap& other) : cap_{other.cap_}, size_{other.size_}, heap_{new T[cap_]}{
    std::copy(other.heap_, other.heap_ + size_, heap_);
}

template <typename T>
Heap<T>::Heap(Heap&& other){
    cap_ = other.cap_;
    size_ = other.size_;
    heap_ = other.heap_;
    other.heap_ = nullptr;
}

template <typename T>
Heap<T>& Heap<T>::operator=(const Heap& other){
    if(this == &other) return *this;
    delete [] heap_;
    cap_ = other.cap_;
    size_ = other.size_;
    heap_ = new T[cap_];
    std::copy(other.heap_, other.heap_ + size_, heap_);
    return *this;
}

template <typename T>
Heap<T>& Heap<T>::operator=(Heap&& other){
    delete [] heap_;
    cap_ = other.cap_;
    size_ = other.size_;
    heap_ = other.heap_;
    other.heap_ = nullptr;
    return *this;
}

template <typename T>
int Heap<T>::parent(int index) const{
    return (index - 1) / 2;
}

template <typename T>
int Heap<T>::leftChild(int index) const{
    return 2 * index + 1;
}

template <typename T>
int Heap<T>::rightChild(int index) const{
    return 2 * index + 2;
}

template <typename T>
template <typename Lambda>
void Heap<T>::inorder(Lambda lambda, int pos){
    if(pos >= size_) return;
    inorder(lambda, leftChild(pos));
    lambda(pos);
    inorder(lambda, rightChild(pos));
}



template <typename T>
void Heap<T>::balanseDown(int index){
    if(index < size_){
        int left = leftChild(index);
        int right = rightChild(index);
        if(left < size_ && right < size_ && (heap_[index] < heap_[left] || heap_[index] < heap_[right])){
            int indexOfBigger = heap_[left] < heap_[right] ? right : left;
            std::swap(heap_[index], heap_[indexOfBigger]);
            balanseDown(index);
        }else if (left < size_ && right >= size_ &&
            heap_[index] < heap_[left]) {
            std::swap(heap_[index], heap_[left]);
            balanseDown(index);
        }else if (left >= size_ && right < size_ &&
            heap_[index] < heap_[right]) {
            std::swap(heap_[index], heap_[right]);
            balanseDown(index);
        }
    }
}

template <typename T>
void Heap<T>::balanseUp(int index){
    while(index > 0 && heap_[parent(index)] < heap_[index]){
        std::swap(heap_[parent(index)], heap_[index]);
        index = parent(index);
    }
}

template <typename T>
template <typename U>
Heap<T>& Heap<T>::insert(U&& element){
    if(size_ == cap_) reallocate();
    heap_[size_++] = std::forward<U>(element);
    if(size_ > 1) balanseUp(size_ - 1);
    return *this;
}

template <typename T>
Heap<T>& Heap<T>::removeMin(){
    if(size_ == 0) return *this;
    int mIndex = minIndex();
    std::swap(heap_[mIndex], heap_[size_ - 1]);
    balanseDown(mIndex);
    size_--;
    print();
    return *this;
}

template <typename T>
Heap<T>& Heap<T>::removeMax(){
    if(size_ == 0) return *this;
    std::swap(heap_[0], heap_[size_ - 1]);
    balanseDown(0);
    size_--;
    return *this;
}

template <typename T>
void Heap<T>::reallocate(){
    cap_ *= 2;
    T* temp = heap_;
    heap_ = new T[cap_];
    std::copy(temp, temp + size_, heap_);
    delete [] temp;
}

template <typename T>
T& Heap<T>::min(){
    int minIndex = 0;
    auto lambda = [this, &minIndex](int index){
        if(heap_[index] < heap_[minIndex])
            minIndex = index;
    };
    inorder(lambda, 0);
    return heap_[minIndex];
}

template <typename T>
int Heap<T>::minIndex(){
    int minIndex = 0;
    auto lambda = [this, &minIndex](int index){
        if(heap_[index] < heap_[minIndex])
            minIndex = index;
    };
    inorder(lambda, 0);
    return minIndex;
}

template <typename T>
T& Heap<T>::max(){
    int maxIndex = 0;
    auto lambda = [this, &maxIndex](int index){
        if(heap_[index] > heap_[maxIndex])
            maxIndex = index;
    };
    inorder(lambda, 0);
    return heap_[maxIndex];
}

template <typename T>
Heap<T>::~Heap() { delete [] heap_; };



