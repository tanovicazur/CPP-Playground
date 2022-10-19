#pragma once

#include "List.hpp"
#include <stdexcept>

namespace Types{
  //Model cvora
  template <typename T>
    struct Node{
      T data;
      Node* next;
      Node(const T& element):data{element},next{nullptr}{}
    };

  template <typename T>
    class SingleLinkedList:public List<T>{
      public:
        using Iterator=typename List<T>::Iterator;
        SingleLinkedList();
        SingleLinkedList(const SingleLinkedList&);
        SingleLinkedList(SingleLinkedList&&);
        SingleLinkedList& operator=(const SingleLinkedList&);
        SingleLinkedList& operator=(SingleLinkedList&&);
        ~SingleLinkedList();
        SingleLinkedList& push_back(const T&)override;
        SingleLinkedList& push_front(const T&) override;
        SingleLinkedList& pop_front()override;
        SingleLinkedList& pop_back()override;
        bool empty()const override;
        size_t size()const override;
        SingleLinkedList& extend(const SingleLinkedList&);
        Iterator find(const T& element)const;
        SingleLinkedList& insert(Iterator pos,const T& element);
        Iterator erase(Iterator pos);
        Iterator begin()const override;
        Iterator end() const override;
        const Iterator cbegin()const override;
        const Iterator cend()const override;
        SingleLinkedList& erase_elements(T);

        friend std::ostream& operator<<(std::ostream& out,const SingleLinkedList& lista){
          Node<T>* tmpNode=lista.head_;
          out<<"[";
          while(tmpNode!=nullptr){
            out<<tmpNode->data<<" ";
            tmpNode=tmpNode->next;
          }
          out<<"]"<<std::endl;
          return out;
        }  
      private:
        void copyList(const SingleLinkedList&);
        void dealoc();
        Node<T>* head_{nullptr};
        Node<T>* tail_{nullptr};
        size_t size_{0};

    };

  //Slozenost O(n)
  //potrebno je proci kroz cijelu listu 
  //i na svaki Cvor primjeniti operator delete
  template <typename T>
    void SingleLinkedList<T>::dealoc(){
      Node<T>* tmp=head_;
      while(tmp!=nullptr){
        head_=tmp->next;
        delete tmp;
        tmp=head_;
      }
      head_=tail_=nullptr;
      size_=0;
    }

  //Slozenost O(n)
  //potrebno je proci kroz proslijedjenu listu
  //i svaki Cvor dodati u novu listu
  template <typename T>
    void SingleLinkedList<T>::copyList(const SingleLinkedList& other){
      Node<T>* tmpNode=other.head_;
      while(tmpNode!=nullptr){
        //push_back(tmpNode->data);
        //ili
        if(head_==nullptr){
          head_=tail_=tmpNode;
          tail_->next=nullptr;
        }
        else{
          tail_->next=tmpNode;
          tail_=tmpNode;
        }
        ++size_;
        tmpNode=tmpNode->next;
      }

    }

  //Slozenost O(1)
  //samo dodjeljivanje 3 vrijednosti
  template<typename T>
    SingleLinkedList<T>::SingleLinkedList(){
      tail_=head_=nullptr;
      size_=0;
    }

  //Slozenost O(n)
  //poziva se metod copyList koji je objasnjen ranije
  template<typename T>
    SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList& other){
      copyList(other);
    }

  //Slozenost O(1)
  //samo se proslijede vrijednosti jer je MOVE KONSTRUKTOR
  template <typename T>
    SingleLinkedList<T>::SingleLinkedList(SingleLinkedList&& other){
      head_=other.head_;
      tail_=other.tail_;
      size_=other.size_;
      other.head_=other.tail_=nullptr;
    }

  //Slozenost O(n), mozda cak i gora
  //poziva se dealociranje i kopiranje koje je objasnjeno ranije
  template<typename T>
    SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList& other){
      if(this!=&other){
        dealoc();
        copyList(other);
      }
      return *this;
    }
  //SLozenost O(n)
  //jer je prvo potrebno dealocirati objekat s lijeve strane(onaj koji je pozvao)
  //a onda se izvrsi samo dodjeljianje vrijednosti
  template<typename T>
    SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList&& other){
      dealoc();
      head_=other.head_;
      tail_=other.tail_;
      size_=other.size_;
      other.head_=other.tail_=nullptr;
      return *this;
    }

  //Slozenost O(n)
  //potrebno izvrsiti dealociranje cijele liste
  template <typename T>
    SingleLinkedList<T>::~SingleLinkedList(){
      dealoc();
    }

  //Slozenost O(1)
  //samo dodjele vrijednosti
  template <typename T>
    SingleLinkedList<T>& SingleLinkedList<T>::push_back(const T& element){
      Node<T>* newNode=new Node<T>(element);
      // newNode->data=element; OVAKO PRAVI PROBLEM JA MSM 
      // JER AKO JE TIPA STRING ON NE ZNA KOLKO DA ZAUZME NA HEAPU..

      if(head_==nullptr){
        head_=tail_=newNode;
        // head_->data=element;
        // tail_->data=element;
        // tail_->next=nullptr;
        // head_->next=nullptr;
      }
      else{
        tail_->next=newNode;
        tail_=newNode;
      }
      ++size_;
      return *this;
    }

  //Slozenost O(1)
  //samo dodjele vrijednosti
  template <typename T>
    SingleLinkedList<T>& SingleLinkedList<T>::push_front(const T& element){
      Node<T>* newNode=new Node<T>(element);
      if(head_==nullptr){
        head_=newNode;
        tail_=newNode;
      }
      else{
        newNode->next=head_;
        head_=newNode;
        //head_->data=element;
      }
      ++size_;
      return *this;
    }

  //Slozenost O(1)
  //samo manipulisanje pointerima i dodjele vrijednosti
  //te jednom pozivanje operatora delete 
  template<typename T>
    SingleLinkedList<T>& SingleLinkedList<T>::pop_front(){
      if(!empty()){
        Node<T>* tmpNode=head_;
        head_=head_->next;
        delete tmpNode;
        --size_;
      }
      return *this;
    }

  //Slozenost O(n)
  //jer je potrebno iterirati kroz cijelu listu dok ne dodjemo
  //do cvora koji pokazuje na zadnji koji ce biti obrisan.
  //to radimo iz razloga da mozemo podesiti tail_ na novi cvor
  template <typename T>
    SingleLinkedList<T>& SingleLinkedList<T>::pop_back(){
      if(size_!=0){
        Node<T>* tmpNode=head_;
        while(tmpNode->next!=tail_){
          tmpNode=tmpNode->next;
        }
        delete tail_;
        tail_=tmpNode;
        tail_->next=nullptr;
        --size_;
      }
      return *this;
    }

  //Slozenost O(1)
  //samo se izvrse dvije operacije
  template <typename T>
    bool SingleLinkedList<T>::empty()const{
      return head_==nullptr;
    }

  //Slozenost O(1)
  template <typename T>
    size_t SingleLinkedList<T>::size()const{
      return size_;
    }

  //Slozenost O(n)
  //jer je potrebno proci kroz listu koja ce biti dodana na listu
  //koja je pozvala metod
  template <typename T>
    SingleLinkedList<T>& SingleLinkedList<T>::extend(const SingleLinkedList& other){
      if(this==&other) return *this;
      Node<T>* tmpNode=other.head_;
      while(tmpNode!=nullptr){
        push_back(tmpNode->data);
        tmpNode=tmpNode->next;
      }
      //size_=size_+other.size_;
      return *this;
    }

  //svi metodi nad Iteratorima moraju biti O(1) u suprotnom se ne prave
  template <typename T>
    class List<T>::Iterator : public std::forward_iterator_tag{
      public:
        Iterator()=default;
        Iterator(const Iterator& other):ptr_(other.ptr_){}
        Iterator(Iterator&& it):ptr_{it.ptr_}{}
        Node<T>* node() const{return ptr_;}
        Iterator& operator=(const Iterator& it){
          if(this!=&it){
            ptr_=it.ptr_;
          }
          return *this;
        }
        Iterator& operator=(Iterator&& it){
          ptr_=it.ptr_;
          it.ptr_=nullptr;
          return *this;
        }
        ~Iterator(){
          ptr_=nullptr;
        }
        Iterator(Node<T>* tmpNode):ptr_{tmpNode}{}
        Iterator(T& element):ptr_{&element}{}
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& it)const;
        bool operator!=(const Iterator& it)const;
        T& operator*()const;
      private:
        Node<T>* ptr_{nullptr};
    };
  //Slozenost O(1)
  template <typename T>
    typename List<T>::Iterator& List<T>::Iterator::operator++(){
      ptr_=ptr_->next;
      return *this;
    }

  //Slozenost O(1)
  template <typename T>
    typename List<T>::Iterator List<T>::Iterator::operator++(int) {
      Iterator tmp=*this;
      ptr_=ptr_->next;
      return tmp;
    }

  //Slozenost O(1)
  template <typename T>
    bool List<T>::Iterator::operator==(const Iterator& it)const{
      return ptr_==it.ptr_;
    }

  //Slozenost O(1)
  template <typename T>
    bool List<T>::Iterator::operator!=(const Iterator& it)const{
      return ptr_!=it.ptr_;
    }

  //Slozenost O(1)
  template <typename T>
    T& List<T>::Iterator::operator*()const{
      return ptr_->data;
    }

  //Slozenost O(n)
  //potrebno je proci kroz listu cijelu i traziti odgovarajuci podatak
  //iz svakog cvora.
  //najbolji slucaj da je na pocetku O(1)
  //najgori slucaj da je na kraju ili da ga nema O(n)
  template <typename T>
    typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::find(const T& element)const{
      if(empty()) return end();

      Iterator pom(head_);
      while(pom!=end()){
        if(*pom==element)
          return pom;
        ++pom;
      }
      return pom;
    }

  //modifikacija insert metoda - ubacivanje ispred trenutnog
  //slozenost O(1) 
  //samo se izvrsi zamjena podataka u dva Cvora
  //jedan Cvor je dodan ispred drugog (manipulisanje pointerima O(1))
  //i onda samo zamjena vrijednosti (dodjela vrijednosti O(1))
  template <typename T>       
    SingleLinkedList<T>& SingleLinkedList<T>::insert(Iterator pos,const T& element){
      if(pos==end() || empty()) {
        push_back(element);
        return *this;
      }

      if(pos==begin()){
        push_front(element);
        return *this;
      }

      //cuvamo novi cvor na trenutnu poziciju
      Node<T>* positionNode=pos.node();
      Node<T>* newNode=new Node<T>(element);
      newNode->next=positionNode->next;
      positionNode->next=newNode;
      //ubacili smo ga iza positionNode
      //i sada im zamijenimo vrijednosti
      newNode->data=positionNode->data;
      positionNode->data=element;
      ++size_;
      return *this;
    }


  //modifikacija insert metoda
  //SLOZENOST O(n) nacin
  //jer u ovoj implementaciji, moramo proci kroz cijelu listu
  //da nadjemo prethodni od pozicije u koju ubacujemo noviCvor
  //(nije radjena zamjena vrijednosti kao u prijasnjoj implementaciji)
  // template <typename T>       
  // SingleLinkedList<T>& SingleLinkedList<T>::insert(Iterator pos,const T& element){
  // if(pos==end() || empty()) {
  // push_back(element);
  // return *this;
  // }
  //
  // if(pos==begin()){
  // push_front(element);
  // return *this;
  // }
  // //cuvamo novi cvor na trenutnu poziciju
  // Node<T>* positionNode=pos.node();
  // //alociramo novi cvor
  // Node<T>* newNode=new Node<T>(element);
  // Node<T>* tmpNode=head_;
  // while(tmpNode->next!=positionNode){
  // tmpNode=tmpNode->next;
  // }
  // tmpNode->next=newNode;
  // newNode->next=positionNode;
  // ++size_;
  // return *this;
  // }


  //sa vjezbi implementacija
  //dodavanje iza
  // template <typename T>       
  // SingleLinkedList<T>& SingleLinkedList<T>::insert(Iterator pos,const T& element){
  // if(pos==end()) return *this;
  //
  // //cuvamo novi cvor na trenutnu poziciju
  // Node<T>* positionNode=pos.node();
  // //alociramo novi cvor
  // Node<T>* newNode=new Node<T>(element);
  // //naredni cvor preusmjeravamo na cvor ispred trenutne pozcicije
  // //newNode->data=element;
  // //naredni cvor od trenutne pozicije je novi cvor
  // newNode->next=positionNode->next;
  // positionNode->next=newNode;
  // ++size_;
  // return *this;
  // }


  //Slozenost O(n)
  //jer je potrebno proci kroz listu da se nadje prethodni od ovog kojeg brisemo
  //kako bi obrisali i linkali opet listu
  //treba nam prethodni
  template <typename T>     
    typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::erase(Iterator pos){
      if(pos==end()) return end();

      //cuvamo cvor na trenutnu ppoziciju
      Node<T>* positionNode=pos.node();

      Node<T>* tmpNode=head_;

      if(positionNode==tail_){
        pop_back();
        return end();
      }
      //brisemo prvi element
      if(tmpNode!=nullptr && positionNode==head_){
        head_=head_->next;
        delete tmpNode;
        return Iterator(head_);
      }

      else{
        //iteriramo do pozicije ispred trazenog cvora kako bi next
        //preusmjerili na cvor iza iteratora pos
        while(tmpNode->next!=positionNode){
          tmpNode=tmpNode->next;
        }
      }
      //tmpNode je nevalidan vracamo end() iterator
      if(tmpNode==nullptr)return end();

      tmpNode->next=positionNode->next;

      delete positionNode;

      --size_;
      return pos;
    }

  //Slozenost O(1)
  template <typename T>      
    typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::begin()const{
      return Iterator{head_};
    }

  //Slozenost O(1)
  template <typename T>      
    typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::end() const{
      return Iterator{tail_->next};
    }

  //Slozenost O(1)
  template <typename T>     
    const typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::cbegin()const{
      return Iterator{head_};
    }

  //Slozenost O(1)
  template <typename T>     
    const typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::cend()const{
      return Iterator{tail_->next};
    }
  //Slozenost O(n)
  //potrebno je proci kroz cijelu listu i pretraziti sve Cvorove
  //(tj njihove podatke uporediti sa argumentom)
  //ako su jednaki potrebno je izvrsiti delete tog Cvora
  //(sto je dodatni posao na samo prolazenje kroz listu)
  template<typename T>
    SingleLinkedList<T>& SingleLinkedList<T>::erase_elements(T element){
      //sve dok prvi cvor ima ovaj eleemnt radi pop_front
      while(head_->data==element){
        pop_front();
      }
      //sada kad smo sigurni da nije na prvom cvoru
      //mozemo iterirati kroz petlju pocevsi od drugog cvora
      //kako bu uvijek cuvali lokaciju prethodnog cvora
      Node<T>* prethodni=head_;
      Node<T>* tmpNode=head_->next;

      //iteriramo kroz petlju sve dok tmpNode ne postane invalidan pointer
      while(tmpNode!=nullptr){
        //ukoliko je podatak iz nekog Cvora jednak elementu trazenom
        //ulazimo u mali blok naeedbi kako bi obrisali taj cvor
        //radjeno je slicno kao obicni erase metod, manipulisanjem pointera next
        //i operatorom delete smo obrisali Cvor koji sadrzi u sebi ovaj podatak
        if(tmpNode->data==element){
          prethodni->next=tmpNode->next;
          delete tmpNode;
          tmpNode=prethodni->next;
          --size_;
        }
        //ukoliko je tmpNode van liste, izlazimo iz petlje
        if(tmpNode==tail_->next){
          break;
        }
        //prolazak kroz listu
        prethodni=prethodni->next;
        tmpNode=tmpNode->next;
      }
      //podesavamo tail_ na prethodni, jer je tmpNode bio prethodni->next 
      //i on je bio jednak nullptr, znaci sad je prethodni zadnji Cvor u listi
      //i zbog toga njegov next stavljamo na nullptr
      prethodni->next=nullptr;
      tail_=prethodni;
      return *this;
    }
}//Types
