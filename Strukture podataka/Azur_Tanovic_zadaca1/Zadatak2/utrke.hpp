#pragma once
#include <vector>
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
      friend void unos(std::vector<Vozac>&, int);
      void ispis(std::vector<Vozac>&);
      friend std::ostream& operator<<(std::ostream&, Vozac& vozac);
    private:
      double vrijeme_;
      int gStaza_;
      Automobil auto_;
};
