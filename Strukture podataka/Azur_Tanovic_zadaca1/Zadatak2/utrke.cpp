#include "utrke.hpp"

void unos(std::vector<Vozac>& vozaci, int n) {
  for (int i = 0; i < n; ++i) {
    std::cout << "\tVozac " << i+1 << std::endl;
    Vozac vozac;
    std::cout << "Unesite ime vozaca: ";
    std::cin >> vozac.ime_;
    std::cout << "Unesite prezime vozaca: ";
    std::cin >> vozac.prezime_;
    std::cout << "Unesite godine vozaca: ";
    std::cin >> vozac.gStarosti_;
    std::cout << "Unesite staz vozaca: ";
    std::cin >> vozac.gStaza_;
    std::cout << "Unesite prolazno vrijeme vozaca: ";
    std::cin >> vozac.vrijeme_;

    vozaci.push_back(vozac);
    std::cout << std::string(34, '-') << std::endl;
  }
}

std::ostream& operator<<(std::ostream& out, Vozac& vozac) {
  out << vozac.ime_ << " " << vozac.prezime_ << ", " << vozac.gStarosti_ << ", "
      << vozac.gStaza_ << ", " << vozac.vrijeme_;
  return out;
}

void ispis(std::vector<Vozac>& vozaci) {
  auto begin = vozaci.begin();
  int mjesto = 1;
  while (begin != vozaci.end()) {
    std::cout << mjesto << ". mjesto: ";
    std::cout << *begin << std::endl;
    mjesto++;
    begin++;
  }
}
