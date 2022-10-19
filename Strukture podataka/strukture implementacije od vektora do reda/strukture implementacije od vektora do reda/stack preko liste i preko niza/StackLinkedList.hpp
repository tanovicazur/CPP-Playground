#pragma once

#include <iostream>

namespace Types{
  template <typename T>
  struct Node{
  T data;
  Node* next=nullptr;
  Node(const T& element){
  data=element;
  next=nullptr;
  }
  Node(){  }
  };

  template <typename T>
  class StackLinkedList{
    public:
      StackLinkedList();
      StackLinkedList(const StackLinkedList&);
      StackLinkedList& operator=(const StackLinkedList&);
      StackLinkedList(StackLinkedList&&);
      StackLinkedList& operator=(StackLinkedList&&);
      ~StackLinkedList();
     // StackLinkedList& push(T);
      // StackLinkedList& push(T);
       template <typename U>
       StackLinkedList& push(U&&);
      T pop();
      T& top();
      size_t size(){return size_;}
      bool empty(){
        std::cout << "prazan" << std::endl;
        return head_==nullptr;}
      bool operator==(const StackLinkedList&);
      bool operator!=(const StackLinkedList&);
    private:
      Node<T>* head_=nullptr;
      Node<T>* tail_=nullptr;
      size_t size_=0;
      void copyList(const StackLinkedList&);
      void dealoc();
  };

template <typename T>
void StackLinkedList<T>::dealoc(){
Node<T>* tmpNode=head_;
while(tmpNode!=nullptr){
head_=head_->next;
delete tmpNode;
tmpNode=head_;
}
head_=tail_=nullptr;
size_=0;
}

template<typename T>
void StackLinkedList<T>::copyList(const StackLinkedList& other){
Node<T>* tmp=other.head_;
while(tmp!=nullptr){
push(tmp->data);
tmp=tmp->next;
}
}

//preko kopije
// template <typename T>
// StackLinkedList<T>& StackLinkedList<T>::push(T element){
// Node<T>* newNode=new Node<T>(element);
// if(head_==nullptr){
// head_=tail_=newNode;
// ++size_;
// return *this;
// }
//
// tail_->next=newNode;
// tail_=newNode;
// ++size_;
// return *this;
// }



//preko std::forward
template <typename T>
template <typename U>
StackLinkedList<T>& StackLinkedList<T>::push(U&& element){
Node<T>* newNode=new Node<T>(std::forward<U>(element));
  //Node<T>* newNode=new Node<T>(element)
  //Node<T>* newNode=new Node<T>;
//newNode->data=std::forward(element);
if(head_==nullptr){
head_=tail_=newNode;
++size_;
return *this;
}

tail_->next=newNode;
tail_=newNode;
++size_;
return *this;
}

template <typename T>
StackLinkedList<T>::StackLinkedList():
head_{nullptr},tail_{nullptr},size_{0}{}

template <typename T>
StackLinkedList<T>::StackLinkedList(const StackLinkedList& other){
copyList(other);
}
template <typename T>
StackLinkedList<T>& StackLinkedList<T>::operator=(const StackLinkedList& other){
if(this!=&other){
dealoc();
copyList(other);
}
return *this;
}

template <typename T>
StackLinkedList<T>::StackLinkedList(StackLinkedList&& other){
head_=other.head_;
tail_=other.tail_;
size_=other.size_;
other.head_=other.tail_=nullptr;
other.size_=0;
}

template <typename T>
StackLinkedList<T>& StackLinkedList<T>::operator=(StackLinkedList&& other){
head_=other.head_;
tail_=other.tail_;
size_=other.size_;
other.head_=other.tail_=nullptr;
other.size_=0;
return *this;
}

template <typename T>
StackLinkedList<T>::~StackLinkedList(){
dealoc();
}

template <typename T>
T StackLinkedList<T>::pop(){
T ret=tail_->data;
Node<T>* tmpNode=head_;
if(head_==tail_){
std::cout << "Brisemo prvi element koji je unesen." << std::endl;
delete tmpNode;
head_=tail_=nullptr;
--size_;
return ret;
}
while(tmpNode->next!=tail_){
tmpNode=tmpNode->next;
}
delete tail_;
tail_=tmpNode;
--size_;
return ret;
}

template <typename T>
T& StackLinkedList<T>::top(){
return tail_->data;
}

template <typename T>
bool StackLinkedList<T>::operator==(const StackLinkedList& other){
if(size_!=other.size_)
  return false;
Node<T>* tmpNode=head_;
Node<T>* tmpNodeOther=other.head_;
while(tmpNode!=nullptr){
if(tmpNode->data!=tmpNodeOther->data)
  return false;
tmpNode=tmpNode->next;
tmpNodeOther=tmpNodeOther->next;
}
return true;
}

template <typename T>
bool StackLinkedList<T>::operator!=(const StackLinkedList& other){
return !(this==&other);
}
   

};//Types
