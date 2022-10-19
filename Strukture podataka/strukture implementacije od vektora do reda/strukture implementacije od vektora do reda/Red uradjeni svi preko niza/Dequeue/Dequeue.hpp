#pragma once
#include <algorithm>
#include <iostream>
#include <stddef.h>

namespace Types {
template <typename T>
class Dequeue {
  public:
  Dequeue();
  Dequeue(const Dequeue&);
  Dequeue(Dequeue&&);
  Dequeue& operator=(const Dequeue&);
  Dequeue& operator=(Dequeue&&);
  ~Dequeue();
  template <typename U>
  Dequeue& push_front(U&&);
  template <typename U>
  Dequeue& push_back(U&&);
  // Pop an element from the begin
  T pop_front();
  // Pop an element from the end
  T pop_back();
  T& front();
  T& back();
  size_t size() const{return size_;}
  size_t capacity() const{return capacity_;}
  bool empty() const{return size_==0;}
  bool full() const{return back_==capacity_;}
  void clear(){dealoc();}
  friend std::ostream& operator<<(std::ostream& os, const Dequeue& dequeue) {
    os << "[";
    for (auto i = dequeue.front_; i <= dequeue.back_; ++i) {
      os << dequeue.arr_[i] << " ";
    }
    os << "]" << std::endl;
    return os;
  }

  private:
  void realloc();
  void copyDequeue(const Dequeue&);
  void dealoc();
  size_t capacity_;
  size_t size_;
  T* arr_;
  size_t back_{0};
  size_t front_{0};
};

//slozenost O(n)
//zbog kopiranja i alociranja prostora za n objekata
template <typename T>
void Dequeue<T>::realloc(){
T* tmp=arr_;
arr_=new T[capacity_*2];
capacity_*=2;
std::copy(tmp+front_,tmp+back_+1,arr_);
front_=0;
back_=size_-1;
delete []tmp;
}

//Slozenost O(n)
//zbog alociranja i kopiranja n objekata na heapu
template <typename T>
void Dequeue<T>::copyDequeue(const Dequeue& other){
  back_=other.back_;
  front_=other.front_;
  size_=other.size_;
  capacity_=other.capacity_;
  T* arr_=new T[capacity_];
  std::copy(other.arr_+front_,other.arr_+back_,arr_+front_);
}

//slozenost O(n)
//zbog brisanja n objekata sa heapa
template <typename T>
void Dequeue<T>::dealoc(){
delete []arr_;
}

//slozenost O(n)
//alociranje prostora za n objekata na heapu
template <typename T>
Dequeue<T>::Dequeue(){
size_=front_=back_=0;
capacity_=10;
arr_=new T[capacity_];
}

//slozenost O(n)
//kopiranje n elemenata
template <typename T>
Dequeue<T>::Dequeue(const Dequeue& other){
copyDequeue(other);
}

//slozenost O(1)
//samo dodjele vrijednosti
template <typename T>
Dequeue<T>::Dequeue(Dequeue&& other){
  back_=other.back_;
  front_=other.front_;
  size_=other.size_;
  capacity_=other.capacity_;
  arr_=other.arr_;
  other.arr_=nullptr;
}

//Slozenost O(n)
//dealociranje te kopiranje 
template <typename T>
Dequeue<T>& Dequeue<T>::operator=(const Dequeue& other){
if(this!=&other){
dealoc();
copyDequeue(other);
}
return *this;
}

//Slozenost O(n)
//zbog destrukcije objekta other
template <typename T>
Dequeue<T>& Dequeue<T>::operator=(Dequeue&& other){
  back_=other.back_;
  front_=other.front_;
  size_=other.size_;
  capacity_=other.capacity_;
  std::swap(arr_,other.arr_);
}

//Slozenost O(n)
template <typename T>
Dequeue<T>::~Dequeue(){
dealoc();
}
 
//Slozenost O(1)
//osim kada je kapacitet pun i kad je potrebno izvrsiti realociranje
template <typename T>
template <typename U>
Dequeue<T>& Dequeue<T>::push_front(U&& element){

if(full()){
realloc();
}

if(empty()){
back_=front_;
arr_[front_]=std::forward<U>(element);
++size_;
return *this;
}

if(front_==0 && !empty()){
for(auto i=back_+1;i>front_;--i){
arr_[i]=arr_[i-1];
}
++back_;
arr_[front_]=std::forward<U>(element);
++size_;
return *this;
}
else{
--front_;
arr_[front_]=std::forward<U>(element);
++size_;
return *this;
}
}

//slozenost O(1)
//osim kad je pun i kad je potrebna realokacija
template <typename T>
template <typename U>
Dequeue<T>& Dequeue<T>::push_back(U&& element){
if(full())
  realloc();

if(empty()){
back_=front_;
arr_[front_]=std::forward<U>(element);
++size_;
return *this;
}

++back_;
arr_[back_]=std::forward<U>(element);
++size_;
return *this;
}

//Slozenost O(1)
//samo dodjele i vracanje vrijednosti
template <typename T>  
T Dequeue<T>::pop_front(){
if(empty())
   throw std::logic_error{"Prazan red."};
int ret=std::move(arr_[front_]);
  ++front_;
  --size_;
  return ret;
}
//Slozenost O(1)
//samo dodjele i vracanje vrijednosti
template <typename T>
T Dequeue<T>::pop_back(){
  if(empty())
    throw std::logic_error{"Prazan red."};
  int ret=std::move(arr_[back_]);
  
 if(back_!=0)
   --back_;
 --size_;
 return ret;
}

//Slozenost O(1)
//samo dodjele i vracanje vr
template <typename T>
T& Dequeue<T>::front(){
  if(empty())
    throw std::logic_error{"Prazan red."};
return arr_[front_];
}

//Slozenost O(1)
//samo dodjele i vracanje vr
template <typename T>
T& Dequeue<T>::back(){
  if(empty())
    throw std::logic_error{"Prazan red."};
return arr_[front_];
}


}//Types
