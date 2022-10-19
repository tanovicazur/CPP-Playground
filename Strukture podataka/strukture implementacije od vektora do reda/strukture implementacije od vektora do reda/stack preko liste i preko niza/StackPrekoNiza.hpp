#pragma once

#include <iostream>
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

namespace Types{
template <typename T>
class Stack{
  public:
    Stack();
    Stack(const Stack&);
    Stack& operator=(const Stack&);
    Stack(Stack&&);
    Stack& operator=(Stack&&);
    ~Stack();
    T pop();
    T& top();
    template <typename U>
    Stack<T>& push(U&&);
    size_t size(){return size_;}
    size_t capacity(){return capacity_;}
    bool empty(){return size_==0;}
    bool full(){return size_==capacity_;}
    bool operator==(const Stack&)const;
    bool operator!=(const Stack&)const;
    T& firstElement();
    void ispisStackaOdPrvogDodanog();
    void ispisStackaOdZadnjeDodanog();
  private:
    size_t size_;
    size_t capacity_;
    T* arr_;
    void copySizeAndCapacity(const Stack&);
    void realoc();
};

//slozenost O(1)
//samo rezervisanje prostora za 10 elemenata na heapu
template <typename T>
Stack<T>::Stack(){
size_=0;
capacity_=10;
arr_=new T[capacity_];
}

//Slozenost O(1)
//pomocni metod sa 2 dodjele vrijednosti napisan jer se koristi u pravilu sestorke
template <typename T>
void Stack<T>::copySizeAndCapacity(const Stack& other){
  size_=other.size_;
  capacity_=other.capacity_;
}

//Slozenost O(2*n)
//radi se dva puta kopiranje i spremanje elemenata na heap
//pa zbog toga je potrebno 2*n da se izvrsi
template <typename T>
void Stack<T>::realoc(){
T* tmp=new T[size_];
std::copy(arr_,arr_+size_,tmp);
delete []arr_;
capacity_=capacity_*2;
arr_=new T[capacity_];
std::copy(tmp,tmp+size_,arr_);
delete []tmp;
}

//Slozenost O(n)
//vrsi se kopiranje n elemenata na heap
template <typename T>
Stack<T>::Stack(const Stack& other){
  copySizeAndCapacity(other);
  arr_=new T[capacity_];
  std::copy(other.arr_,other.arr_+size_,arr_);
}

//Slozenost O(n)
//vrsi se kopiranje n elemenata na heap
//osim ako je isti objekat dodjeljen istom objektu, tada je O(1)
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other){
if(this!=&other){
  delete [] arr_;
  copySizeAndCapacity(other);
  arr_=new T[capacity_];
  std::copy(other.arr_,other.arr_+size_,arr_);
}
return *this;
}

//Slozenost O(1)
//samo dodjela vrijednosti?
template <typename T>
Stack<T>::Stack(Stack&& other){
  copySizeAndCapacity(other);
  arr_=other.arr_;
  other.arr_=nullptr;
}

//Slozenost O(1)
//samo dodjela vrijednosti i brisanje elemenata s heap
template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other){
delete []arr_;
copySizeAndCapacity(other);
arr_=other.arr_;
other.arr_=nullptr;
return *this;
}

//Slozenost O(1)
template <typename T>
Stack<T>::~Stack(){
delete []arr_;
}

//Slozenost O(1)
//smanjivanje vrijednosti size_ i dohvacanje vrijednosti s operatorom []
template <typename T>
T Stack<T>::pop(){
  if(empty()) throw std::out_of_range("The stack is empty.");
return arr_[--size_];
}

//Slozenost O(1)
//smanjivanje vrijednosti size_ i dohvacanje vrijednosti s operatorom []
template <typename T>
T& Stack<T>::top(){
if(empty()) throw std::out_of_range("The stack is empty.");
return arr_[size_-1];
}

//Slozenost O(1)
//samo dodjela vrijednost i indeksiranje, te povecanje size_
//za slucaj kad je full(), radi se realoc koji je 2*n, ali posto
//se on rijetko poziva opet je O(1)
template <typename T>
template <typename U>
Stack<T>& Stack<T>::push(U&& element){
if(full())
  realoc();
arr_[size_]=std::forward<U>(element);
++size_;
return *this;
}

//Slozenost O(n)
//jer je potrebno proci kroz cijelu listu
//i vjerovatno zbog toga ovaj operator nije implementiran u standardnoj biblioteci
template <typename T>
bool Stack<T>::operator==(const Stack& other)const{
  if(size_!=other.size_)
    return false;
  for(auto i=0u;i<size_;++i){
    if(arr_[i]!=other.arr_[i])
      return false;
  }
  return true;
}

//Slozenost O(n)
//jer je potrebno proci kroz cijelu listu
//i vjerovatno zbog toga ovaj operator nije implementiran u standardnoj biblioteci
template <typename T>
bool Stack<T>::operator!=(const Stack& other)const{
return !(*this==other);
}

template <typename T>
T& Stack<T>::firstElement(){
return arr_[0];
}

template <typename T>
void Stack<T>::ispisStackaOdPrvogDodanog(){
for(auto i=0u;i<size();++i){
std::cout << arr_[i] << std::endl;
}
}

template <typename T>
void Stack<T>::ispisStackaOdZadnjeDodanog(){
for(auto i=size();i>0;--i){
 std::cout << arr_[i-1] << std::endl;
}
}

}//Types


