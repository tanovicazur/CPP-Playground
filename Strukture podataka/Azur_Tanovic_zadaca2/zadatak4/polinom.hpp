#pragma once

#include <initializer_list>
#include <cmath>
#include "../zadatak1/MojVektor.hpp"

class Polinom{
    public:
        Polinom() = default;
        Polinom(std::initializer_list<int> lista){
            stepen_ = lista.size();
            for(auto it = lista.begin(); it < lista.end(); it++){
                koef_.push_back(*it);
            }
        }
        Polinom(size_t stepen) : stepen_{stepen}{}

        Polinom operator=(const Polinom& other){
            koef_ = other.koef_;
            stepen_ = other.stepen_;
            return *this;
        }

        double operator()(int x){
            double temp;
            for (size_t i = 0; i < stepen_; i++){
                temp += koef_.at(i) * pow(x, stepen_-(stepen_-i));
            }

            return temp;
        }

        Polinom izvod(){
            auto tempK = koef_;
            auto tempS = stepen_;
            koef_.clear();
            stepen_ = 0;
            for (size_t i = 1; i < tempS; i++){
                koef_.push_back(tempK.at(i) * (tempS - (tempS-i)));
            }
            stepen_ = koef_.size();
            return *this;
        }   

        friend Polinom operator*(Polinom const &p1, Polinom const &p2);
        friend Polinom operator-(Polinom const &p1, Polinom const &p2);
        friend Polinom operator+(Polinom const &p1, Polinom const &p2);
        friend std::ostream& operator<<(std::ostream& out, const Polinom& polinom);
        friend std::istream& operator>>(std::istream& input, Polinom& polinom);

    private:
        MojVector<int> koef_;
        size_t stepen_;
};