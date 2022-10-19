#include "radnik.h"
#include <algorithm>
#include <fstream>
#include "../zadatak1/MojVektor.hpp"
#include <string>
#include <vector>

std::ostream& operator<<(std::ostream& out, const Radnik& radnik) {
  return out << radnik.ime_ << " " << radnik.prezime_ << " " << radnik.godine_
             << " " << radnik.radniStaz_ << " " << radnik.plata_ << " "
             << radnik.brojTel_ << std::endl;
}

void loadFrom(std::string file, MojVector<Radnik>& vec) {
  std::string ime, prezime, brojTel, temp;
  int godine, radniStaz, plata;
  std::ifstream input{file};
  if (input.is_open()) {
    while (!input.eof()) {
      std::getline(input, ime, ',');
      std::getline(input, prezime, ',');
      input >> godine;
      std::getline(input, temp, ',');
      input >> radniStaz;
      std::getline(input, temp, ',');
      input >> plata;
      std::getline(input, temp, ',');
      std::getline(input, brojTel);

      if (ime == "") continue;

      Radnik radnik{ime, prezime, godine, radniStaz, plata, brojTel};
      vec.push_back(radnik);
    }
    input.close();
    input.clear();
  }
}

void erase_if(MojVector<Radnik>& vec) {
  auto begin = vec.begin();
  while (begin != vec.end()) {
    if (begin->getGodine() > 55) {
      begin = vec.erase(begin);
    } else
      begin++;
  }
}

void povPlate10(MojVector<Radnik>& vec) {
  auto begin = vec.begin();
  int brojac = 0;
  double povecanje;
  double plata;
  std::sort(begin, vec.end(), [](Radnik radnik1, Radnik radnik2) {
    return radnik1.getGodine() < radnik2.getGodine();
  });
  while (brojac != 15) {
    brojac++;
    povecanje = (begin->getPlata() * 10) / 100;
    plata = povecanje + begin->getPlata();
    begin->setPlata(plata);
    begin++;
  }
}

void povPlate20(MojVector<Radnik>& vec) {
  auto begin = vec.begin();
  double povecanje;
  double plata;
  std::sort(begin, vec.end(), [](Radnik radnik1, Radnik radnik2) {
    return radnik1.getRadniStaz() > radnik2.getRadniStaz();
  });
  while (begin->getRadniStaz() > 15) {
    povecanje = (begin->getPlata() * 20) / 100;
    plata = povecanje + begin->getPlata();
    begin->setPlata(plata);
    begin++;
  }
}

void loadIn(){
  
}
