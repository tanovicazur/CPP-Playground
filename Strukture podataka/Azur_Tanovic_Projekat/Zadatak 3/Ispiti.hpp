#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

class Ispit{
    public:
    Ispit() = default;
    Ispit(std::string datum, std::string predmet) : datum_{datum}, predmet_{predmet}{};
    friend std::ostream& operator<<(std::ostream& out, const Ispit& i){
        out << i.datum_ << " " << i.predmet_; 
        return out;
    };

    bool operator==(const Ispit& other){
        return datum_ == other.datum_ && predmet_ == other.predmet_;
    };

    std::string getDatum() const { return datum_; };
    std::string getPredmet() const { return predmet_; } ; 

    private:
    std::string datum_;
    std::string predmet_;
};