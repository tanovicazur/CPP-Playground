#include "SingleLinkedList.hpp"
#include <string>
#include <iostream>
#include <chrono>

int main(int argc, char* argv[]) {
  Types::SingleLinkedList<std::string> lista;
  lista.push_back("word1");
  Types::SingleLinkedList<std::string> lista2=lista;
std::cout << lista << std::endl;
std::cout << lista2 << std::endl;
lista.push_back("word2");
std::cout << lista << std::endl;
std::cout << lista2 << std::endl;
lista.extend(lista);
std::cout << lista << std::endl;
std::cout << lista2 << std::endl;

lista2.extend(lista);
std::cout << lista << std::endl;
std::cout << lista2 << std::endl;


  Types::SingleLinkedList<int> lista3;
  Types::SingleLinkedList<int> lista4=lista3;

  srand(time(NULL));


  auto start = std::chrono::high_resolution_clock::now();
  for (auto i = 0u; i < 1000000; ++i) {
    lista3.push_front(rand());
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
    std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Push front duration: " << (duration.count() / 1000) << "ms"
    << std::endl;

  lista3.empty();

  start = std::chrono::high_resolution_clock::now();
  for (auto i = 0u; i < 1000000; ++i) {
    lista3.push_back(rand());
  }
  end = std::chrono::high_resolution_clock::now();
 duration =
    std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Push back duration: " << (duration.count() / 1000) << "ms"
    << std::endl;
 std::cout << "Zakljucujemo da je za 1000000 elemenata, push back brzi za oko 6 ms." << std::endl;

    start = std::chrono::high_resolution_clock::now();
  for (auto i = 0u; i < 10000000; ++i) {
    lista3.push_front(rand());
  }
   end = std::chrono::high_resolution_clock::now();
   duration =
    std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Push front duration: " << (duration.count() / 1000) << "ms"
    << std::endl;

  lista3.empty();

  start = std::chrono::high_resolution_clock::now();
  for (auto i = 0u; i < 10000000; ++i) {
    lista3.push_back(rand());
  }
  end = std::chrono::high_resolution_clock::now();
 duration =
    std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Push back duration: " << (duration.count() / 1000) << "ms"
    << std::endl;
 std::cout << "Zakljucujemo da je za 10000000 elemenata, push back brzi za oko 15 ms." << std::endl;
 //   lista2=listd;
//  lista.push_back("word2");
//    std::cout << lista << std::endl;
//   std::cout << lista2 << std::endl;
//   lista2.extend(lista);
//   std::cout << lista << std::endl;
//   std::cout << lista2 << std::endl;
//   lista.extend(lista2);
//   std::cout<<lista.size()<<std::endl;
//   std::cout << lista << std::endl;
//  lista2=Types::SingleLinkedList<std::string>{"miki","maus"};
  //   lista.push_back("word1").push_back("word2");
//   lista.push_front("word3");
// //  std::cout << lista << std::endl;
// //  lista.pop_front();
//   //std::cout << lista << std::endl;
//   lista.push_back("word3");
//  // std::cout << lista << std::endl; 
//  // lista.pop_back();
//   std::cout << lista << std::endl;
//  Types::SingleLinkedList<std::string> lista2=lista;
//  std::cout << "OVDJE" << std::endl;
//   lista2.push_back("word3").push_back("word4");
//   std::cout << lista << std::endl;
//   std::cout << lista2 << std::endl;
 
// std::cout << lista2 << std::endl;
// lista2.extend(lista);
// //lista.extend(lista2);
// std::cout << lista << std::endl;
// std::cout << lista2 << std::endl;
//
// // lista.push_front("word0");
//  lista.extend(lista2);
// std::cout << lista << std::endl;
// //lista2.extend(lista);
// std::cout << lista2 << std::endl;

  return 0;
}
