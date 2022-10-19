#include <iostream>
#include "utrke.hpp"
#include "utrke.cpp"
#include <algorithm>

int main(int argc, char *argv[])
{
  std::vector<Vozac> vozaci;
  int n;
  std::cout << "Unesite broj vozaca na utrci: ";
  std::cin >> n;
  std::cout << std::string(34, '-') << std::endl;
  unos(vozaci, n);
  std::sort(vozaci.begin(), vozaci.end(), [](Vozac vozac1, Vozac vozac2){ return vozac1.getVrijeme() < vozac2.getVrijeme();});
  ispis(vozaci);
  return 0;
}
