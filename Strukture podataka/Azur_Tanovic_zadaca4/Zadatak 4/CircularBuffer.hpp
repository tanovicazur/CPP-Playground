#pragma once

#include <iostream>

namespace Types{
  template <typename T>
    class CircularBuffer{

      public:
        CircularBuffer();
        CircularBuffer(const CircularBuffer&);
        CircularBuffer& operator=(const CircularBuffer&);
        CircularBuffer(CircularBuffer&&);
        CircularBuffer& operator=(CircularBuffer&&);
        ~CircularBuffer();
        template <typename U>
          CircularBuffer& push(U&&);
        T pop();
        T& top();
        size_t capacity()const{return capacity_;}
        size_t size()const{return size_;}
        bool empty()const{return size_==0;};
        bool full()const{return size_==capacity_;};
        friend std::ostream& operator<<(std::ostream& out,const CircularBuffer& cb){
          if(cb.front_<=cb.back_){
            out<<"[";
            for(auto i=cb.front_;i<=cb.back_;++i){
              out<<cb.arr_[i]<<" ";
            }
            out<<"]"<<std::endl;
          }

          else if(cb.back_<cb.front_){
            out<<"[";
            for(auto i=cb.front_;i<cb.capacity_;++i){
              out<<cb.arr_[i]<<"f ";
            }
            for(auto i=0;i<=cb.back_;++i){
              out<<cb.arr_[i]<<"b ";
            }
            out<<"]"<<std::endl;
          }

          return out;
        }

      private:
        size_t front_;
        size_t back_;
        size_t capacity_;
        size_t size_;
        T* arr_;
        void realoc();
        void copyCircularBuffer(const CircularBuffer&);
        void dealocCircularBuffer();
    };

  template <typename T>
    void CircularBuffer<T>::realoc(){
      T* tmp=arr_;
      arr_=new T[capacity_*2];


      for(auto i=front_;i<=capacity_-1;++i){
        arr_[i-front_]=tmp[i];
      }
      for(auto i=0;i<=back_;++i){
        arr_[i+capacity_-front_]=tmp[i];
      }
      front_=0;
      back_=capacity_-1;
      capacity_=2*capacity_;
      size_=size_;
      delete []tmp;
    }

  template <typename T>
    void CircularBuffer<T>::dealocCircularBuffer(){
      delete []arr_;
      size_=capacity_=front_=back_=0;
    }

  template <typename T>
    void CircularBuffer<T>::copyCircularBuffer(const CircularBuffer& other){  
      front_=other.front_;
      back_=other.back_;
      capacity_=other.capacity_;
      size_=other.size_;
      arr_=new T[capacity_];
      std::copy(other.arr_+front_,other.arr_+back_+1,arr_);
    }

  template <typename T>
    CircularBuffer<T>::CircularBuffer(){
      front_=0;
      back_=0;
      capacity_=10;
      size_=0;
      arr_=new T[capacity_];
    }

  template <typename T>
    CircularBuffer<T>::CircularBuffer(const CircularBuffer& other){
      copyCircularBuffer(other);
    }

  template <typename T>
    CircularBuffer<T>& CircularBuffer<T>::operator=(const CircularBuffer& other){
      if(this!=&other){
        dealocCircularBuffer();
        copyCircularBuffer(other);
      }
      return *this;
    }

  template <typename T>
    CircularBuffer<T>::CircularBuffer(CircularBuffer&& other){
      front_=other.front_;
      back_=other.back_;
      capacity_=other.capacity_;
      size_=other.size_;
      arr_=other.arr_;
      other.arr_=nullptr;
    }
  
  template <typename T>
    CircularBuffer<T>& CircularBuffer<T>::operator=(CircularBuffer&& other){
      dealocCircularBuffer();
      front_=other.front_;
      back_=other.back_;
      capacity_=other.capacity_;
      size_=other.size_;
      swap(arr_,other.arr_);
      return *this;
    }

  template <typename T>
    CircularBuffer<T>::~CircularBuffer(){
      dealocCircularBuffer();
    }

  template <typename T>
    template <typename U>
    CircularBuffer<T>& CircularBuffer<T>::push(U&& element){
      if(empty()){
        back_=front_;
        arr_[back_]=std::forward<U>(element);
        ++size_;
        return *this;
      }
      else if(full()){

        realoc();
        back_=(back_+1)%capacity_;
        arr_[back_]=std::forward<U>(element);
        ++size_;
        return *this;

      }

      else {
        back_=(back_+1)%capacity_;
        arr_[back_]=std::forward<U>(element);

        ++size_;
        return *this;
      }
    }

  template<typename T>
    T CircularBuffer<T>::pop(){
      if(empty())
        throw std::logic_error("Prazan buffer.");
      int indeks_za_pop=front_;
      front_=(front_+1)%capacity_;
      --size_;
      return std::move(arr_[indeks_za_pop]);
    }

  template <typename T>
    T& CircularBuffer<T>::top(){
      if(empty())
        throw std::logic_error("Prazan buffer.");
      return std::move(arr_[front_]);
    }

}
