#pragma once
#include <algorithm>
#include <iostream>
#include <stddef.h>

namespace Types {

template <typename T>
struct Node{
Node<T>* next=nullptr;
Node<T>* previous=nullptr;
T data;
Node(const T& element){
next=nullptr;
previous=nullptr;
data=element;
}
};

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
  bool empty(){return head_==nullptr;}
  friend std::ostream& operator<<(std::ostream& out,const Dequeue& deq){
  out<<"[";
  Node<T>* tmpNode=deq.head_;
  while(tmpNode!=nullptr){
  out<<tmpNode->data<<" ";
  tmpNode=tmpNode->next;
  }
  out<<"]";
  return out;
  }  
  private:
  Node<T>* head_=nullptr;
  Node<T>* tail_=nullptr;
  size_t size_=0;
  void copyDequeue(const Dequeue&);
  void dealoc();
};

//slozenost O(n)
//potrebno je proci kroz cijelu listu i pozvati delete n puta
template <typename T>
void Dequeue<T>::dealoc(){
Node<T>* tmpNode=head_;
while(tmpNode!=nullptr){
head_=head_->next;
delete tmpNode;
tmpNode=head_;
}
}

//slozenost O(1)
//samo manipulisanje pointerom tail_ i kreiranje novog objekta na heapu
//s obzirom da imamo pristup uvijek na tail_, nema problema
template <typename T>
template <typename U>
Dequeue<T>& Dequeue<T>::push_back(U&& element){
Node<T>* newNode=new Node<T>{std::forward<U>(element)};
if(empty()){
head_=tail_=newNode;
}

else{
tail_->next=newNode;
newNode->previous=tail_;
tail_=newNode;
}

++size_;
return *this;
}

//slozenost O(n)
//jer je potrebno proci kroz cijelu listu i pushati svaki cvor
//u lijevi objekat
template <typename T>
void Dequeue<T>::copyDequeue(const Dequeue& other){
Node<T>* tmpNode=other.head_;
while(tmpNode!=nullptr){
push_back(tmpNode->data);
tmpNode=tmpNode->next;
}
}

//O(1)
//samo dodjela vrijednosti
template <typename T>
Dequeue<T>::Dequeue(){
  head_=tail_=nullptr;
  size_=0;
}

//Slozenost O(n)
//objasnjeno ranije
template <typename T>
Dequeue<T>::Dequeue(const Dequeue& other){
copyDequeue(other);
}

//Slozenost O(1)
//samo dodjele vrijednosti
template <typename T>
Dequeue<T>::Dequeue(Dequeue&& other){
head_=other.head_;
tail_=other.tail_;
size_=other.size_;
other.head_=other.tail_=nullptr;
other.size_=0;
}

//Slozenost o(2*n)=O(n)
//metod koji dealocira je O(n) (prolazi kroz cijelu listu i poziva delete 
//na svaki cvor)
//metod koji kopira je O(n) objasnjeno ranije
template <typename T>
Dequeue<T>& Dequeue<T>::operator=(const Dequeue& other){
if(this!=&other){
dealoc();
copyDequeue(other);
}
return *this;
}

//Slozenost O(n)
//mozemo implementirati na ovaj nacin jer ono sto stavimo na other objekat
//ce se svakako dealocirati jer taj objekat je privremeni
//i na njemu ce se pozvat destruktor koji ce proci od other.head_ do other.tail_
//pa zbog toga O(n)?
template <typename T>
Dequeue<T>& Dequeue<T>::operator=(Dequeue&& other){
std::swap(head_,other.head_);
std::swap(tail_,other.tail_);
std::swap(size_,other.size_);
}

//slozenost O(n)
template <typename T>
Dequeue<T>::~Dequeue(){
dealoc();
}

//slozenost O(1)
//manipulisanje pointerima
//uvijek imamo head_ i samo uradimo par dodjela vrijednosti
template <typename T>
template <typename U>
Dequeue<T>& Dequeue<T>::push_front(U&& element){
Node<T>* newNode=new Node<T>{std::forward<U>(element)};
if(empty()){
head_=tail_=newNode;
}
else{
  head_->previous=newNode;
  newNode->next=head_;
  head_=newNode;
}
++size_;
return *this;
}

//Slozenost O(1) 
//imamo head_ samo manipulisanje pointerima i dodjele vrijednosti
template <typename T>
T Dequeue<T>::pop_front(){
if (empty())
  throw std::out_of_range("Prazan red.");
T ret=head_->data;
if(head_==tail_){
delete head_;
head_->next=tail_->next=head_->previous=tail_->previous=nullptr;
}
else{
Node<T>* tmpNode=head_;
head_=head_->next;
head_->previous=nullptr;
delete tmpNode;
}
--size_;
return ret;
}

//Slozenost O(1)
//imamo tail_
//samo manipulisanje pointerima i dodjele vrijednosti
template <typename T>
T Dequeue<T>::pop_back(){
if (empty())
  throw std::out_of_range("Prazan red.");
T ret=tail_->data;
if(head_==tail_){
delete head_;
head_->next=tail_->next=head_->previous=tail_->previous=nullptr;
}
else{
Node<T>* tmpNode=tail_;
tail_=tail_->previous;
tail_->next=nullptr;
delete tmpNode;
}
--size_;
return ret;
}

//Slozenost O(1)
//samo vracanje vrijednosti
template <typename T>  
T& Dequeue<T>::front(){
return head_->data;
}

//Slozenost O(1)
//samo vracanje vrijednosti
template <typename T>
T& Dequeue<T>::back(){
return tail_->data;
}
}//Types  
