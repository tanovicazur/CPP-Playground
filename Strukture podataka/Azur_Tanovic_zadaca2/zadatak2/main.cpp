#include <algorithm>
#include <iostream>
#include "radnik.cpp"
#include "radnik.h"


int main(void) {
  std::string file1{"acme.txt"};
  std::string file2{"globex.txt"};
  MojVector<Radnik> vec;
  // Ucitava acme.txt u vector
  loadFrom(file1, vec);
  // Ucitava globex.txt u vector
  loadFrom(file2, vec);
  // Brise radnike koji imaju vise od 55 godina
  erase_if(vec);
  // Povecava platu za 10% za 15 najmladjih radnika
  povPlate10(vec);
  // Povecava platu za 20% svim radnicima koji imaju preko 15 godina staza
  povPlate20(vec);
  // Sortira vector po imenu
  std::sort(vec.begin(), vec.end(), [](Radnik radnik1, Radnik radnik2) {
    if(radnik1.getIme() == radnik2.getPrezime())
      return radnik1.getPrezime() < radnik2.getPrezime();
    else
      return radnik1.getIme() < radnik2.getIme();
  });
  // Unos radnika u novi fajl corp.txt
  std::ofstream output{"corp.txt"};
  if (output.is_open()) {
    auto begin = vec.begin();
    while (begin != vec.end()) {
      output << begin->getIme() << " " << begin->getPrezime() << " "
             << begin->getGodine() << " " << begin->getRadniStaz() << " "
             << begin->getBrTel() << std::endl;
      begin++;
    }
    output.close();
  }

  return 0;
}
