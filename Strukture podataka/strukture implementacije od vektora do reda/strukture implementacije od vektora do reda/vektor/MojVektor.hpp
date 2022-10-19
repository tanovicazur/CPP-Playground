#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T> 
class MojVector {
  public:
    MojVector():capacity_(10),size_(0){
      arr_=new T[capacity_];
    }

    MojVector(const std::initializer_list<T>& il):capacity_{il.size()},size_{il.size()}{
      arr_=new T[capacity_];
      std::copy(il.begin(),il.end(),arr_);
    }

    MojVector(const MojVector& other):capacity_(other.capacity_),size_(other.size_){
      arr_=new T[capacity_];
      std::copy(other.arr_,other.arr_+size_,arr_);
    }

    MojVector& operator=(const MojVector& other){
      if(this==&other) return *this;
      delete []arr_;
      capacity_=other.capacity_;
      size_=other.size_;
      arr_=new T[capacity_];
      std::copy(other.arr_,other.arr_+size_,arr_);
      return *this;
    }

    MojVector(MojVector&& other){
      capacity_=other.capacity_;
      size_=other.size_;
      arr_=other.arr_;
      other.arr_=nullptr;
      other.size_=0;
      other.capacity_=0;
    }

    MojVector& operator=(MojVector&& other){
      delete []arr_;
      capacity_=other.capacity_;
      size_=other.size_;

      //arr_=new T[capacity_];
      arr_=other.arr_;
      //std::copy(other.arr_,other.arr_+size_,arr_);
      other.arr_=nullptr;
      other.capacity_=other.size_=0;
      return *this;
    }

    ~MojVector(){
      delete []arr_;
      size_=0;
      capacity_=0;
    }
    
    void realoc(){
    T *tmp=arr_;
    arr_=new T[2*capacity_];
    std::copy(tmp,tmp+size_,arr_);
    capacity_*=2;
    delete []tmp;
    }

    MojVector& push_back(T element){
     if(size_>=capacity_)
        realoc();
      *(arr_+size_)=element;
       ++size_;
      return *this;
    }

    T& at(size_t index) const{
      if(index>=size_)
        throw std::out_of_range("Index van opsega vektora.");
      return *(arr_+index);
    }


    T& operator[](size_t index) const{
      return *(arr_+index);  
    }

    void clear(){
      //  size_=0;
      *this=MojVector{};
    }

    size_t size() const{
      return size_;
    }

    bool empty() const{
     return size_==0;
      //return (bool)size_;
    }

    const T& back() const{
      if(empty()) throw std::out_of_range{"Vector je prazan!"};
      return *(arr_+size_-1);
    }

    const T& front() const{
      if(empty()) throw std::out_of_range{"Vector je prazan!"};
      return *arr_;
    }

    T& back(){
      if(empty()) throw std::out_of_range{"Vector je prazan!"};
      return *(arr_+size_-1);
    }

    T& front(){
      if(empty()) throw std::out_of_range{"Vector je prazan!"};
      return *arr_;
    }

    void resize(size_t newCapacity){
      size_t tmpSize;

      tmpSize=(size_>newCapacity) ? newCapacity : size_;
      T *tmp=arr_;
      arr_=new T[newCapacity];
      for(auto i=0u;i<tmpSize;++i)
        arr_[i]=tmp[i];
      for(auto i=tmpSize;i<newCapacity;++i)
        arr_[i]=0;
      size_=newCapacity;
      capacity_=newCapacity;
      delete []tmp;

      // if(size_>newCapacity)
      //   tmpSize=newCapacity;
      // else
      //   tmpSize=size_;

      // T* tmp=new T[tmpSize];
      //
      // std::copy(arr_,arr_+tmpSize,tmp);
      // delete []arr_;
      // arr_=new T[newCapacity];
      // std::copy(tmp,tmp+tmpSize,arr_);
      // size_=tmpSize;
      // capacity_=newCapacity;
      // tmp=nullptr;
    }

    MojVector& pop_back(){
      if(empty()) throw std::out_of_range{"Vector je prazan!"};
      --size_;
      return *this;
    }

    size_t capacity() const{
      return capacity_;
    }

    bool operator==(const MojVector& other) const{
      if(size_!=other.size_)
        return false;

      for(auto i=0u;i<size_;++i){
        if(arr_[i]!=other.arr_[i])
          return false;
      }
      return true;
    }

    bool operator!=(const MojVector& other) const{
      return !(*this==other); 
    }

    class Iterator;

    Iterator begin() const{
      return Iterator{arr_};
    }

    Iterator end() const{
      return Iterator{arr_+size_};
    }

    Iterator find(const T& element) const{
    for(auto it=begin();it!=end();++it){
      if(*it==element)
        return it;
    }
    return end();
      // for(auto i=0u;i<size_;++i){
      //   if(*(arr_+i)==element)
      //     return Iterator{arr_};
      // }
      // return Iterator{arr_+size_};
    }

    MojVector& insert(Iterator it, T element){
     
      size_t index=it-begin();
      if(size_>=capacity_) realoc();
      
      for(auto i=size_;i>index;--i){
      arr_[i]=arr_[i-1];
      }
      arr_[index]=element;
      ++size_;
      return *this;
      // if(it==begin()){
      //   T* tmp;
      //   tmp=new T[capacity_];
      //   std::copy(arr_,arr_+size_-1,tmp);
      //   delete []arr_;
      //   //++size_;
      //   arr_=new T[capacity_];
      //   arr_[0]=element;
      //   for(auto i=1;i<size_;++i){
      //     arr_[i]=tmp[i-1];
      //   }
      //   ++size_;
      //   tmp=nullptr;
      // }
      //
      // else if(it==end()){
      //   push_back(element);
      //   ++size_;
      // }
      //
      // else{
      //   T* tmp;
      //   tmp=new T[capacity_];
      //   auto brojac=0u;
      //   auto tmpIt=begin();
      //
      //   while(tmpIt!=it){
      //     *(tmp+brojac)=*tmpIt;
      //     ++brojac;
      //     ++tmpIt;
      //   }
      //
      //   *(tmp+brojac)=element;
      //   for(auto i=brojac;i<size_;++i){
      //     *(tmp+i+1)=arr_[i];
      //   }
      //   ++size_;
      //   delete [] arr_;
      //   arr_=new T[capacity_];
      //   std::copy(tmp,tmp+size_,arr_);
      //   tmp=nullptr;
      // }
      //return *this;
    }

    Iterator erase(Iterator pos){
  auto tmpIt=pos;
  if(pos==end())return end();
  ++pos;
  while(pos!=end()){
  *(pos-1)=*pos;
  ++pos;
  }
  --size_;
  return tmpIt;

  // if(pos==end())
  //
  //     return end();
  //   size_t index=pos-begin();
  //   --size_;
  //   for(auto i=index;i<size_;++i){
  //   arr_[i]=arr_[i+1];
  //   }
  //   return pos;
  //
      // if(pos==begin()){
      //   // T* tmp=new T[capacity_];
      //   // std::copy(arr_+1,arr_+size_,tmp);
      //   --size_;
      //   for(auto i=0u;i<size_;++i){
      //     arr_[i]=arr_[i+1];
      //   }
      // }
      //
      // else if(pos==end()){
      //   pop_back();
      // }
      //
      // else{
      //   T* tmp;
      //   tmp=new T[capacity_];
      //   auto brojac=0u;
      //   auto tmpIt=begin();
      //
      //   while(tmpIt!=pos){
      //     *(tmp+brojac)=*tmpIt;
      //     ++brojac;
      //     ++tmpIt;
      //   }
      //   ++brojac;
      //   for(auto i=brojac;i<size_;++i){
      //     *(tmp+i-1)=arr_[i];
      //   }
      //   delete [] arr_;
      //   arr_=new T[capacity_];
      //   std::copy(tmp,tmp+size_,arr_);
      //   --size_;
      //   tmp=nullptr;
      // }
      // return pos;
    }

    Iterator erase(Iterator beginIt, Iterator endIt){
    auto tmpIt=beginIt;
    size_t razmak=endIt-beginIt;
    while(endIt!=end())
      *beginIt++=*endIt++;
    size_-=razmak;
    return tmpIt;
      // T* tmp;
      // tmp=new T[capacity_];
      // auto brojac=0u;
      // auto tmpIt=begin();
      // int donjagr=0;
      //
      // while(tmpIt!=endIt){
      //   if(tmpIt==beginIt){
      //     donjagr=brojac;
      //   }
      //   *(tmp+brojac)=arr_[brojac];
      //   ++brojac;
      //   ++tmpIt;
      // }
      //
      // auto razmak=brojac-donjagr;
      // for(auto i=donjagr;i<size_;++i){
      //   *(tmp+i)=arr_[i+razmak];
      // } 
      // size_=size_-razmak;
      // delete [] arr_;
      // arr_=new T[capacity_];
      // std::copy(tmp,tmp+size_,arr_);
      // tmp=nullptr; 
    }

  private:
    size_t capacity_;
    size_t size_;
    T *arr_;
};

template <typename T>
std::ostream &operator<<(std::ostream& out, const MojVector<T>& other){
  for(T e:other){
    out<<e<<"  ";
  }
  out<<std::endl;
  return out;
}

template <typename T>
class MojVector<T>::Iterator
: public std::iterator<std::random_access_iterator_tag, T> {
  public:
    Iterator(T *ptr):ptr_(ptr){}
    T& operator*() const{
      return *ptr_;
    }

    T* operator->() const{
      return ptr_;
    }

    Iterator& operator++(){
      ++ptr_;
      return *this;
    }

    Iterator operator++(int){
      auto tmp=*this;
      ++ptr_;
      return tmp;
    }

    Iterator& operator--(){
      --ptr_;
      return *this;
    }

    Iterator operator--(int){
      auto tmp=*this;
      --ptr_;
      return tmp;
    }

    Iterator operator+(size_t index){
      return Iterator{ptr_+index};
    }

    Iterator operator-(size_t index){
      return Iterator{ptr_-index};
    }

    int operator-(Iterator other)const{
      int rez=0;
      if(ptr_>other.ptr_){
        for(auto it=other;it!=*this;++it,++rez);
        return rez;
      }
      else{
        for(auto it=*this;it!=other;++it,++rez);
        return -rez;
      }
    };

    bool operator==(const Iterator& it) const{
      return ptr_==it.ptr_;
    }
    bool operator!=(const Iterator &it) const{
      return !(ptr_==it.ptr_);
    }

    bool operator<(const Iterator& it) const {
      if(*this-it<0)
        return true;
      return false;
    }

    ~Iterator(){
      ptr_=nullptr;
    }

  private:
    T* ptr_;
};

// template <typename T>
// int MojVector<T>::Iterator::operator-(MojVector<T>::Iterator other){
//       int rez=0;
//       if(ptr_>other.ptr_){
//         for(auto it=other;it!=*this;++it,++rez);
//         return rez;
//       }
//       else{
//         for(auto it=*this;it!=other;++it,++rez);
//         return -rez;
//       }
//     };


