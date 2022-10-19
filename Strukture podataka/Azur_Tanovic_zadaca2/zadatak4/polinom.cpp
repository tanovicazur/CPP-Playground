#include "polinom.hpp"

std::ostream& operator<<(std::ostream& out, const Polinom& polinom){
    if((polinom.stepen_) > 1 && (polinom.koef_.at(0) != 0))
        out << polinom.koef_.at(0) << " + ";
    if((polinom.stepen_ <= 1) && (polinom.koef_.at(0) != 0))
        out << polinom.koef_.at(0);
    if((polinom.stepen_ > 2) && (polinom.koef_.at(1) != 0))
        out << polinom.koef_.at(1) << "*x + ";
    if((polinom.stepen_ <= 2) && (polinom.koef_.at(1) != 0))
        out << polinom.koef_.at(1) << "*x";
    for (size_t i = 2; i < polinom.stepen_; i++){
        if((i == polinom.stepen_-1) && (polinom.koef_.at(i) != 0))
            out << polinom.koef_.at(i) << "*x^" << i;
        else
            out << polinom.koef_.at(i) << "*x^" << i << " + ";
    }
    return out;
}

std::istream& operator>>(std::istream& input, Polinom& polinom){
    int koeficijent;
    for (size_t i = 0; i < polinom.stepen_; i++){
        if(input >> koeficijent) polinom.koef_.push_back(koeficijent);
        else throw std::logic_error("Invalid data type");
    }
    return input;
};

Polinom operator+(Polinom const &p1, Polinom const &p2){
    Polinom temp;
    if(p1.stepen_ > p2.stepen_){
        temp.stepen_ = p1.stepen_;
        for (size_t i = 0; i < temp.stepen_; i++){
            if(i < p2.stepen_) temp.koef_.push_back(p1.koef_.at(i) + p2.koef_.at(i));
            else temp.koef_.push_back(p1.koef_.at(i));
        }
    }
    if(p2.stepen_ > p1.stepen_){
        temp.stepen_ = p2.stepen_;
        for (size_t i = 0; i < p2.koef_.size(); i++){
            if(i < p1.stepen_) temp.koef_.push_back(p1.koef_.at(i) + p2.koef_.at(i));
            else temp.koef_.push_back(p2.koef_.at(i));
        }
    }

    return temp;
}

Polinom operator-(Polinom const &p1, Polinom const &p2){
    Polinom temp;
    if(p1.stepen_ > p2.stepen_){
        temp.stepen_ = p1.stepen_;
        for (size_t i = 0; i < temp.stepen_; i++){
            if(i < p2.stepen_) temp.koef_.push_back(p1.koef_.at(i) - p2.koef_.at(i));
            else temp.koef_.push_back(p1.koef_.at(i));
        }
    }
    if(p2.stepen_ > p1.stepen_){
        temp.stepen_ = p2.stepen_;
        for (size_t i = 0; i < p2.koef_.size(); i++){
            if(i < p1.stepen_) temp.koef_.push_back(p1.koef_.at(i) - p2.koef_.at(i));
            else temp.koef_.push_back(p2.koef_.at(i));
        }
    }

    return temp;
}

Polinom operator*(Polinom const &p1, Polinom const &p2){
    Polinom temp;
    if(p1.stepen_ > p2.stepen_){
        temp.stepen_ = p1.stepen_;
        for (size_t i = 0; i < temp.stepen_; i++){
            if(i < p2.stepen_) temp.koef_.push_back(p1.koef_.at(i) * p2.koef_.at(i));
            else temp.koef_.push_back(p1.koef_.at(i));
        }
    }
    if(p2.stepen_ > p1.stepen_){
        temp.stepen_ = p2.stepen_;
        for (size_t i = 0; i < p2.koef_.size(); i++){
            if(i < p1.stepen_) temp.koef_.push_back(p1.koef_.at(i) * p2.koef_.at(i));
            else temp.koef_.push_back(p2.koef_.at(i));
        }
    }

    return temp;
}