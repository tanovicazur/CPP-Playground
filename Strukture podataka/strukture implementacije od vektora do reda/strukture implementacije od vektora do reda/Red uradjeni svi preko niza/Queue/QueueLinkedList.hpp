#pragma once
#include <iostream>
#include <list>

namespace Types{

template <typename T>
struct Node{
T data;
Node<T>* next=nullptr;

Node(const T& element){
data=element;
next=nullptr;
}
Node(){}
};

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
    T& front();
    T& back();
    size_t size()const{return size_;}
    bool empty()const{return head_==nullptr;}
    Queue& swap(Queue&);
 
  private:
   Node<T>* head_=nullptr;
    Node<T>* tail_=nullptr;
    size_t size_=0;
 //   std::list lista;
    void dealoc();
    void copyQueue(const Queue&);
   
};

template <typename T>
void Queue<T>::dealoc(){
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
  template <typename U>
  Queue<T>& Queue<T>::push(U&& element){
   Node<T>* newNode=new Node<T>(std::forward<U>(element));
  if(empty()){
  head_=tail_=newNode;
  }
  else{
  tail_->next=newNode;
  tail_=newNode;
  }
  //lista.push_front(element);
    ++size_;
  return *this;
  }
   
  template <typename T>
  void Queue<T>::copyQueue(const Queue& other){
  Node<T>* tmpNode=other.head_;
  while(tmpNode!=nullptr){
  push(tmpNode->data);
  tmpNode=tmpNode->next;
  }
  }

  template<typename T>
  Queue<T>::Queue(){
  head_=nullptr;
  tail_=nullptr;
  size_=0;
    }
  
  template<typename T>  
  Queue<T>::Queue(const Queue& other){
  copyQueue(other);    
  }
  
  template<typename T>  
  Queue<T>& Queue<T>::operator=(const Queue& other){
  if(this!=&other){
  dealoc();
  copyQueue(other);
  }
  return *this;
  }
  
  template<typename T>  
  Queue<T>::Queue(Queue&& other){
  head_=other.head_;
  tail_=other.tail_;
  size_=other.size_;
  other.head_=nullptr;
  other.tail_=nullptr;
  size_=0;
  }
  

  //moze li ovdje swap
  template<typename T>  
  Queue<T>& Queue<T>::operator=(Queue&& other){
  dealoc();
  head_=other.head_;
  tail_=other.tail_;
  size_=other.size_;
  other.head_=nullptr;
  other.tail_=nullptr;
  size_=0; 
  // std::swap(head_,other.head_);
  // std::swap(tail_,other.tail_);
  // std::swap(size_,other.size_);
  return *this;
  }
  
  template<typename T>  
  Queue<T>::~Queue(){
  dealoc();
  }
  
  template<typename T>
  T Queue<T>::pop(){
  if(empty())
    throw std::logic_error("Prazan red");
  T ret=head_->data;
  head_=head_->next;
  return ret;
  }

  template <typename T>
  T& Queue<T>::front(){
  if(empty())
    throw std::logic_error("Prazan red");
  return tail_->data;
  }

  template <typename T>
  T& Queue<T>::back(){
  if(empty())
    throw std::logic_error("Prazan red");
  return head_->data;
  }
     
  template <typename T>
  Queue<T>& Queue<T>::swap(Queue& other){
    std::swap(head_,other.head_);
    std::swap(tail_,other.tail_);
    std::swap(size_,other.size_);
    return *this;
  }
 


}//Types
