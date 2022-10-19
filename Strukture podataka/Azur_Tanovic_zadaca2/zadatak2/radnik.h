#pragma once
#include <iostream>

class Radnik {
  public:
  Radnik() = default;
  Radnik(std::string ime, std::string prezime, int godine, int radniStaz,
         int plata, std::string brojTel) {
    ime_ = ime;
    prezime_ = prezime;
    godine_ = godine;
    radniStaz_ = radniStaz;
    plata_ = plata;
    brojTel_ = brojTel;
  }
  ~Radnik(){};

  std::string getIme() { return ime_; };
  std::string getPrezime() { return prezime_; };
  int getGodine() { return godine_; };
  int getPlata() { return plata_; };
  void setPlata(double plata) { plata_ = plata; };
  int getRadniStaz() { return radniStaz_; };
  std::string getBrTel() { return brojTel_; };
  friend std::ostream& operator<<(std::ostream& out, const Radnik& radnik);

  private:
  std::string ime_, prezime_, brojTel_;
  int radniStaz_, godine_, plata_;
};

