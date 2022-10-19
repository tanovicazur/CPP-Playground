#pragma once

#include <iostream>

namespace Types{
template <typename T>
class Queue{
  public:
    Queue();
    Queue(const Queue&);
    Queue& operator=(const Queue&);
    Queue(Queue&&);
    Queue& operator=(Queue&&);
    ~Queue();
    template <typename U>
    Queue& push(U&&);
    T pop();
    T& front(){return arr_[front_];}
    T& back(){return arr_[back_];}
    size_t size()const{return size_;}
    size_t capacity()const{return capacity_;}
    bool full()const{return back_==capacity_;}
    bool empty()const{return size_==0;}
    Queue& swap(Queue&);
    // void ispis(){
  // for(int i=front_;i<back_+1;++i)
  //   std::cout << arr_[i] << std::endl;
  // }
  private:
    void copyQueue(const Queue&);
    void dealocQueue();
    size_t capacity_;
    size_t size_=0;
    size_t front_=0;
    size_t back_=0;
    T* arr_;
};

//Slozenost O(n)
//zbog brisanja n objekata na heapu
template <typename T>
void Queue<T>::dealocQueue(){
delete []arr_;
capacity_=size_=front_=back_=0;
}

//Slozenost O(n)
//zbog kopiranja i alociranja n objekata na heapu
template <typename T>
void Queue<T>::copyQueue(const Queue& other){
  capacity_=other.capacity_;
  size_=other.size_;
  front_=other.front_;
  back_=other.back_;
  arr_=new T[other.capacity_];
  std::copy(other.arr_+other.front_,other.arr_+back_+1,arr_);
}

//Slozenost O(n)
//zbog alociranja n objekata na heapu
template <typename T>
Queue<T>::Queue(){
capacity_=10;
size_=0;
front_=0;
back_=0;
arr_=new T[capacity_];
}

//Slozenost O(n)
//objasnjeno ranije
template <typename T>
Queue<T>::Queue(const Queue& other){
copyQueue(other);
}

//Slozenost O(n)
//dealociranje plus kopiranje n objekata na heapu
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other){
if(this!=&other){
dealocQueue();
copyQueue(other);
}
return *this;
}

//Slozenost O(1)
//samo dodjele vrijednosti
//na kraju se brise objekat other
//ali on pokazuje na nullptr
//pa to je O(1)
template <typename T>
Queue<T>::Queue(Queue&& other){
size_=other.size_;
capacity_=other.capacity_;
front_=other.front_;
back_=other.back_;
//arr_=new T[capacity_]; NE TREBA JER UZME ADRESU OD other.arr_
arr_=other.arr_;
other.arr_=nullptr;
}

//slozenost O(n)
//zbog destrukcije objekta other
template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other){
  size_=other.size_;
  front_=other.front_;
  back_=other.back_;
  capacity_=other.capacity_;
  std::swap(arr_,other.arr_);
  return *this;
}

//slozenost O(n)
//zbog destrukcije n objekata sa heapa
template<typename T>
Queue<T>::~Queue(){
  dealocQueue();
}

//slozenost O(1)
//osim kad je potrebno uraditi realocciranje (tj KAD JE KAPACITET PUN)
template <typename T>
template <typename U>
Queue<T>& Queue<T>::push(U&& element){
if(full()){
T* tmp=arr_;
capacity_=capacity_*2;
arr_=new T[capacity_];
std::copy(tmp+front_,tmp+back_+1,arr_);
delete [] tmp;
front_=0;
back_=size_-1;
}
if(empty()){
arr_[front_]=std::forward<U>(element);
back_=front_;
++size_;
return *this;
}
arr_[back_+1]=std::forward<U>(element);
++size_;
++back_;

return *this;
}

//Slozenost O(1)
//samo dodjele i vracanje vrijednosti
template <typename T>
T Queue<T>::pop(){
  if(empty())
    throw std::logic_error("Prazan red.");
  --size_;
//  std::cout << "izbacujem"<<arr_[front_] << std::endl;
  return std::move(arr_[front_++]);
}

//Slozenost O(1)
//samo dodjele vrijednosti
template <typename T>
Queue<T>& Queue<T>::swap(Queue& other){
  std::swap(front_,other.front_);
 std::swap(back_,other.back_);
 std::swap(size_,other.size_);
 std::swap(capacity_,other.capacity_);
  std::swap(arr_,other.arr_);
}
}//Types
