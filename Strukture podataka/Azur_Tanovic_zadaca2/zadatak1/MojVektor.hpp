#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T> 
class MojVector {
public:
  MojVector() : size_{0}, capacity_{1}, arr_{new T[capacity_]}{};
  MojVector(const std::initializer_list<T> &l) : capacity_{l.size()}, size_{capacity_}, arr_{new T[capacity_]} {
    std::copy(l.begin(), l.end(), arr_);
  };
  MojVector(const MojVector &other) : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]}{
    std::copy(other.arr_, other.arr_ + other.size_, arr_);
  };
  MojVector &operator=(const MojVector &other){
    if(this != &other){
      delete[] arr_;
      capacity_ = other.capacity_;
      size_ = other.size_;
      arr_ = new T[capacity_];
      std::copy(other.arr_, other.arr_ + size_, arr_);
    }
      return *this;
  };
  MojVector(MojVector &&other) : capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_}{
    other.arr_ = nullptr;
    other.capacity_ = other.size_ = 0;
  };
  MojVector &operator=(MojVector &&other){
    if(this != &other){
      delete[] arr_;
      capacity_ = other.capacity_;
      size_ = other.size_;
      arr_ = other.arr_;
      other.arr_ = nullptr;
      other.capacity_ = other.size_ = 0;
    }
    return *this;
  };
  ~MojVector(){ delete[] arr_, capacity_ = 0, size_ = 0;};

  MojVector &push_back(T elem) {
    if(size_ == capacity_){
      reallocate();
    }
    arr_[size_++] = elem;
    return *this;
  };
  T &at(size_t index) const{
    if(index >= size_) throw std::out_of_range("Out of range");
    return arr_[index];
  };
  T &operator[](size_t index) const{
    return arr_[index];
  };
  void clear(){
    size_ = 0;
    capacity_ = 0;
    delete[] arr_;
  };

  size_t size() const{
    return size_;
  };
  bool empty() const{
    return size_ == 0;
  };
  const T &back() const{
    if(empty()) throw std::out_of_range("Array is empty.");
    return arr_[size_-1]; 
  };
  const T &front() const{
    if(empty()) throw std::out_of_range("Array is empty.");
    return arr_[0];
  };
  T &back(){
    if(empty()) throw std::out_of_range("Array is empty.");
    return arr_[size_-1]; 
  };
  T &front(){
    if(empty()) throw std::out_of_range("Array is empty.");
    return arr_[0];
  };

  void reallocate() {
    T* temp = new T[capacity_];
    capacity_ *= 2;
    std::copy(arr_, arr_ + size_, temp);
    delete[] arr_;
    arr_ = new T[capacity_];
    std::copy(temp, temp + size_, arr_);
    delete[] temp;
  }

  void resize(size_t newSize) {
    size_t tempSize;
    if(newSize < size_) tempSize = newSize;
    else tempSize = size_;
    T* temp = new T[tempSize];
    std::copy(arr_, arr_ + tempSize, temp);
    delete[] arr_;
    arr_ = new T[newSize];
    std::copy(temp, temp + tempSize, arr_);
    delete[] temp;
    for(int i=size_; i<newSize; i++){
      arr_[i] = T{};
    }
    capacity_ = size_ = newSize;
  };

  MojVector &pop_back(){
    if(empty()) throw std::out_of_range("Array is empty.");
    size_--;
    return *this;
  };
  size_t capacity() const {
    return capacity_;
  };
  bool operator==(const MojVector & other) const {
    if(size_!=other.size_) return false;
    for(int i = 0; i < size_; i++){
      if(arr_[i]!=other.arr_[i]) return false;
    }
    return true;
  };

  bool operator!=(const MojVector &other) const {
    if(size_ != other.size_) return true;
    for(int i = 0; i < size_; i++){
      if(arr_[i] != other.arr_[i]) return true;
    }
    return false;
  };

  class Iterator;
  Iterator begin() const {
    return Iterator{arr_};
  };
  Iterator end() const {
    return Iterator{arr_ + size_};
  };
  Iterator find(const T &element) const {
    auto it = begin();
    while(it != end()){
      if(*it == element) return it;
      it++;
    }
    return end();
  };
  MojVector &insert(Iterator pos, T element){
    if(size_ == capacity_) reallocate();
    for(auto it = end(); it != pos; it--){
      *it = *(it-1);
    }
    *pos = element;
    size_++;
    if(size_ == capacity_) reallocate();
    return *this;
  };
  Iterator erase(Iterator pos) {
    for(auto it = pos; it != end(); it++){
      *it = *(it+1);
    }
    size_--;
    return pos;
  };
  Iterator erase(Iterator beginIt, Iterator endIt) {
    size_t razlika = endIt - beginIt;
    for(auto it = beginIt; it != end(); ++it){
        *it = *(it+razlika);
    }
    size_ -= razlika;
    return beginIt;
  };

private:
  size_t capacity_;
  size_t size_;
  T *arr_;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const MojVector<T> &vec){
  for (size_t i = 0; i < vec.size(); i++){
    out << vec[i] << " ";
  }
  return out;
};

template <typename T>
class MojVector<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
public:
  Iterator(T *ptr) : ptr_{ptr}{};
  T &operator*() const {
    return *ptr_;
  };
  T *operator->() const {
    return ptr_;
  };
  Iterator &operator++() {
    ptr_++;
    return *this;
  };
  Iterator operator++(int){
    auto temp = *this;
    ptr_++;
    return temp;
  };
  Iterator &operator--(){
    ptr_--;
    return *this;
  };
  Iterator operator--(int) {
    auto temp = *this;
    ptr_--;
    return *this;
  };
  Iterator operator+(size_t index) {
    return MojVector<T>::Iterator{ptr_ + index};
  };
  Iterator operator-(size_t index){
    return MojVector<T>::Iterator{ptr_ - index};
  };
  size_t operator-(Iterator other){
    return ptr_ - other.ptr_;
  };

  bool operator==(const Iterator &it) const{
    return ptr_ == it.ptr_;
  };
  bool operator!=(const Iterator &it) const{
    return ptr_ != it.ptr_;
  };
  bool operator<(const Iterator &it) const {
    return ptr_ < it.ptr_;
  };

  ~Iterator(){
    ptr_ = nullptr;
  };

private:
  T *ptr_;
};
