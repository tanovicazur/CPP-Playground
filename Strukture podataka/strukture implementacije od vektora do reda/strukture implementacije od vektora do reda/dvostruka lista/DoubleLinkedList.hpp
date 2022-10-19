#pragma once

#include <iostream>
#include <exception>
template <typename T>
struct Node{
T data;
Node<T>* next;
Node<T>* previous;
Node(const T& element):data{element},next{nullptr},previous{nullptr}{}
};

template <typename T>
class mojaLista{
  public:
    class Iterator;
    mojaLista();
    ~mojaLista();
    mojaLista(const mojaLista&);
    mojaLista& operator=(const mojaLista&);
    mojaLista(mojaLista&&);
    mojaLista& operator=(mojaLista&&);
    mojaLista(const std::initializer_list<T>&);
    size_t size()const{return size_;}
    bool empty(){return size_==0;}
    mojaLista& push_back(const T&);
    mojaLista& pop_back();
    mojaLista& push_front(const T&);
    mojaLista& pop_front();
    Iterator begin()const; 
    Iterator end()const;
    T& front()const{
    return head_->data;
    }
    T& back()const{
    return tail_->data;
    }
    mojaLista& insert(Iterator pos,const T& element);
    Iterator erase(Iterator pos);
    bool operator==(const mojaLista& other)const;
    bool operator!=(const mojaLista& other)const;
  
    std::ostream& print(std::ostream& out)
  {
    auto temp=head_;
    while(temp!=nullptr)
    {
      out<<temp->data<<" ";
      temp=temp->next;
    }
    out<<std::endl;
    return out;
  }

    void append(const mojaLista& other){
    Node<T>* tmpNode=other.head_;
    tail_->next=tmpNode;
    //std::cout << tail_->data << std::endl;
    while(tmpNode!=nullptr){
       //std::cout << tail_->data << std::endl;
    //   std::cout << "o"<<tmpNode->data << std::endl;
     tail_=tail_->next; 
    tmpNode=tmpNode->next;
    ++size_;
    }
    }

    void append(mojaLista&& other){
     Node<T>* tmpNode=other.head_;
    tail_->next=tmpNode;
    //std::cout << tail_->data << std::endl;
    while(tmpNode!=nullptr){
       //std::cout << tail_->data << std::endl;
    //   std::cout << "o"<<tmpNode->data << std::endl;
     tail_=tail_->next; 
    tmpNode=tmpNode->next;
    ++size_;
    }

    other.head_=other.tail_=nullptr;
    }

    void swap(){
    Node<T>* headNext=head_->next;
    Node<T>* tailPrev=tail_->previous;
    
    headNext->previous=tail_;
    tail_->previous=nullptr;
    tail_->next=headNext;

    head_->previous=tailPrev;
    tailPrev->next=head_;
    head_->next=nullptr;

    Node<T>* tmpNode=head_;
    head_=tail_;
    tail_=tmpNode;
    }
    friend std::ostream& operator<<(std::ostream& out,const mojaLista& lista){
    Node<T>* tmpNode=lista.tail_;
   while(tmpNode!=nullptr){
    out<<tmpNode->data<<", ";
    tmpNode=tmpNode->previous;
    }
    out<<std::endl;
    return out;
    }
  private:
    size_t size_=0;
    Node<T>* head_=nullptr;
    Node<T>* tail_=nullptr;
    void dealoc();
    void copyList(const mojaLista<T>&);
};

template <typename T>
class mojaLista<T>::Iterator : public std::bidirectional_iterator_tag{
  public:
    Iterator(){}
    //friend class mojaLista<T>;
    Iterator(const Iterator& it):ptr_{it.ptr_}{}
    
    Iterator& operator=(const Iterator& it){
    if(this!=it){
    ptr_=it.ptr_;
    }
    return *this;
    }

    Iterator(Iterator&& it){
    ptr_=it.ptr_;
    it.ptr_=nullptr;
    }

    Iterator& operator=(Iterator&& it){
    delete ptr_;
    ptr_=it.ptr_;
    it.ptr_=nullptr;
    return *this;
    }

    Iterator(Node<T>* tmpNode){
    ptr_=tmpNode;
    }

    Iterator(T& element){
    ptr_=&element;
    }

    Node<T>* node(){
    return ptr_;
    }
    
    ~Iterator(){
    ptr_=nullptr;
    }

    Iterator& operator++(){
    ptr_=ptr_->next;
    return *this;
    }

    Iterator operator++(int){
    auto tmp=*this;
    ptr_=ptr_->next;
    return tmp;
    }

    Iterator& operator--(){
    ptr_=ptr_->previous;
    return *this;
    }

    Iterator operator--(int){
    auto tmp=*this;
    ptr_=ptr_->previous;
    return tmp;
    }
    
    bool operator==(const Iterator& it){
    return ptr_==it.ptr_;
    }
    
    bool operator!=(const Iterator& it){
    return ptr_!=it.ptr_;
    }
    
    T& operator*()const{
    return ptr_->data;
    }
  private:
    Node<T>* ptr_{nullptr};
};

template <typename T>
void mojaLista<T>::dealoc(){
Node<T>* tmpNode=head_;
while(tmpNode!=nullptr){
  head_=head_->next;
  delete tmpNode;
  tmpNode=head_;
}
head_=nullptr;
tail_=nullptr;
size_=0;
}

template <typename T>
void mojaLista<T>::copyList(const mojaLista<T>& other){
Node<T>* tmpNode=other.head_;
while(tmpNode!=nullptr){
push_back(tmpNode->data);
tmpNode=tmpNode->next;
}
}

template <typename T>
mojaLista<T>::mojaLista()
:size_{0},head_{nullptr},tail_{nullptr}{}

template <typename T>
mojaLista<T>::~mojaLista(){
dealoc();
}

template <typename T>
mojaLista<T>::mojaLista(const mojaLista& other){
copyList(other);
}

template <typename T>
mojaLista<T>& mojaLista<T>::operator=(const mojaLista& other){
if(this!=&other){
  dealoc();
  copyList(other);
}
return *this;
}

template <typename T>
mojaLista<T>::mojaLista(mojaLista&& other){
head_=other.head_;
tail_=other.tail_;
size_=other.size_;
other.head_=other.tail_=nullptr;
other.size_=0;
}

template <typename T>
mojaLista<T>& mojaLista<T>::operator=(mojaLista&& other){
dealoc();
head_=other.head_;
tail_=other.tail_;
size_=other.size_;
other.head_=other.tail_=nullptr;
other.size_=0;
return *this;
}

template <typename T>
mojaLista<T>::mojaLista(const std::initializer_list<T>& il){
//Node<T>* tmpNode=head_;
auto i=il.begin();
while(i!=il.end()){
  push_back(*i);
  ++i;
}
}

template <typename T>
mojaLista<T>& mojaLista<T>::push_back(const T& element){
Node<T>* newNode=new Node<T>(element);
if(head_==nullptr){
  head_=tail_=newNode;
  }
else{
  // newNode->previous=tail_;
  // tail_->next=newNode;
  // tail_=tail_->next;
tail_->next=newNode;
newNode->previous=tail_;
tail_=newNode;
}
++size_;
return *this;
}

template<typename T>
mojaLista<T>& mojaLista<T>::pop_back(){
 if(size_==0)
  return *this;
   //  throw std::logic_error("Prazna lista.");
// Node<T>* tmpNode=tail_;
//  tail_=tail_->previous;
// tail_->next=nullptr;
// tmpNode->previous=nullptr;
// delete tmpNode;



 //moj
    Node<T>* newTail=tail_->previous;
  delete tail_;
  tail_=newTail;
  //newTail po inicijalizaciji stavi previous i next na nullptr
  //zato ne moram ja
  --size_;
  return *this;
  }

template <typename T>
mojaLista<T>& mojaLista<T>::push_front(const T& element){
Node<T>* newNode=new Node<T>(element);
if(head_==nullptr){
head_=tail_=newNode;
++size_;
}
else{
  // newNode->next=head_;
  // head_->previous=newNode;
  // head_=head_->previous;
head_->previous=newNode;
newNode->next=head_;
head_=newNode;
++size_;
}
return *this;
}

template <typename T>
mojaLista<T>& mojaLista<T>::pop_front(){
if(size_==0)
 return *this;
  // throw std::logic_error("Prazna lista.");

  // Node<T>* tmpNode=head_;
  // head_=head_->next;
  // head_->previous=nullptr;
  // tmpNode->next=nullptr;
  // delete tmpNode;
  //moj
    Node<T>* tmpNode=head_->next;
//tmpNode->previous je vec nullptr
delete head_;
head_=tmpNode;
--size_;
return *this;
}

template <typename T>
mojaLista<T>& mojaLista<T>::insert(Iterator pos,const T& element){
Node<T>* posNode=pos.node();
if(pos==begin()){
  push_front(element);
  return *this;
}

if(pos==end()){
  push_back(element);
return *this;
}

if(posNode==tail_){
push_back(element);
return *this;
}

auto* newNode=new Node<T>(element);
Node<T>* prethodni=posNode->previous;
prethodni->next=newNode;
posNode->previous=newNode;
newNode->next=posNode;
newNode->previous=prethodni;

// pos.ptr_->previous->next=newNode;
// newNode->previous=pos.ptr_->previous;
// newNode->next=pos.ptr_;
// pos.ptr_->previous=newNode;
++size_;
return *this;
}

template <typename T>
typename mojaLista<T>::Iterator mojaLista<T>::erase(Iterator pos){
if(empty()) return end();

Node<T>* posNode=pos.node();

if(pos==begin()){
  pop_front();
  return Iterator{head_};
}

if(pos==end())
  return end();

if(posNode==tail_){
pop_back();
return Iterator{tail_};
}

Iterator tmpIt=begin();
//auto* tmpNode=pos.ptr_;

auto ret=Iterator{posNode->next}; 

// tmpNode->previous->next=tmpNode->next;
// tmpNode->next->previous=tmpNode->next;
// tmpNode->next=tmpNode->previous=nullptr;
// Node<T>* prethodni=posNode->previous;
// prethodni->next=posNode->next;
// Node<T>* slijedeci=posNode->next;
// slijedeci->previous=posNode->previous;
// posNode->previous=posNode->next=nullptr;
//delete tmpNode;
//--size_;
//return ret;


//moj
while(tmpIt!=end()){
  if(tmpIt==pos){
  Node<T>* prednji=posNode->next;
  Node<T>* zadnji=posNode->previous;
  zadnji->next=prednji;
  prednji->previous=zadnji;
  delete posNode;
  --size_;
  return ret;
  }
  ++tmpIt;
}
return end();
}

template <typename T>
bool mojaLista<T>::operator==(const mojaLista& other)const{
if(size_!=other.size_) return false;
// auto it1=begin();
// auto it2=other.begin();
// while(it2!=other.end()){
// if(*it1!=*it2)
//   return false;
// ++it1;
// ++it2;
// }
// return true;
auto otherIt=other.begin();
for(auto i=begin();i!=end();++i){
if(*i!=*otherIt)
  return false;
++otherIt;
}
return true;
}

template <typename T>
bool mojaLista<T>::operator!=(const mojaLista& other)const{
return !(*this==other);
}

template <typename T>
typename mojaLista<T>::Iterator mojaLista<T>::begin()const{
return Iterator{head_};
}

template <typename T>
typename mojaLista<T>::Iterator mojaLista<T>::end()const{
  return Iterator{tail_->next};
}

