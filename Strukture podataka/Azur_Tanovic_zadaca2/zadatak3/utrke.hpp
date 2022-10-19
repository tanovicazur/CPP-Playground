#pragma once
#include "../zadatak1/MojVektor.hpp"
#include <iostream>

class Osoba{
   protected:
    std::string ime_;
    std::string prezime_;
    int gStarosti_;
};

class Automobil{
   private:
    std::string model_;
    std::string boja_;
    int gProizvodnje_;
};

class Vozac : public Osoba{
    public:
      double getVrijeme() { return vrijeme_; };
      friend void unos(MojVector<Vozac>&, int);
      void ispis(MojVector<Vozac>&);
      friend std::ostream& operator<<(std::ostream&, Vozac& vozac);
    private:
      double vrijeme_;
      int gStaza_;
      Automobil auto_;
};
