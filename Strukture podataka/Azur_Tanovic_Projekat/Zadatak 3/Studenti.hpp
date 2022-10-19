#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include "Ispiti.hpp"

class Student{
    public:
    Student() = default;
    Student(std::string index, std::string ime, std::string prezime) : index_{index}, ime_{ime}, prezime_{prezime}{};
    void dodajIspit(std::string datum, std::string predmet){
        ispiti_.push_back(Ispit{datum, predmet});
    };

    void dodajOcjenu(short int ocjena){
        ocjene_.push_back(ocjena);
    };

    void setOcjenaSum(short int ocjena){
        ocjenaSum_ += ocjena;
    }

    const int getOcjenaSum(){
        return ocjenaSum_;
    }

    const std::vector<short int>& getOcjene() const { return ocjene_; };
    const std::vector<short int>& getIspiti() const { return ocjene_; };

    friend std::ostream& operator<<(std::ostream& out, const Student& i){
        out << i.index_ << " " << i.ime_ << " " << i.prezime_; 
        return out;
    };

    private:
    std::string index_;
    std::string ime_;
    std::string prezime_;
    std::vector<Ispit> ispiti_;
    std::vector<short int> ocjene_;
    int ocjenaSum_ = 0;
};


