#include <iostream>
#include "heap.hpp"

int main()
{
    Heap<int> gomila{};
    gomila.insert(5);
    gomila.insert(10);
    gomila.insert(15);
    gomila.insert(2);
    gomila.insert(1);
    gomila.insert(34);
    gomila.insert(12);
    gomila.insert(30);
    gomila.insert(19);
    gomila.insert(7);
    gomila.insert(13);
    gomila.insert(10);
    std::cout << "Gomila: " << gomila << std::endl;
    Heap<int> gomila1{gomila};
    Heap<int> gomila2{std::move(gomila)};
    std::cout << "Gomila 1: " << gomila1 << std::endl;
    std::cout << "Gomila 2: " << gomila2 << std::endl;
    Heap<int> gomila3{};
    gomila3.insert(7);
    gomila3.insert(3);
    gomila3.insert(12);
    gomila3.insert(19);
    gomila3.insert(2);
    gomila3.insert(9);
    std::cout << "Gomila 3: " << gomila3 << std::endl;
    gomila1 = gomila3;
    gomila2 = std::move(gomila3);
    std::cout << "Gomila 1: " << gomila1 << std::endl;
    std::cout << "Gomila 2: " << gomila2 << std::endl;
    std::cout << "Najmanji element u Gomila 1: " << gomila1.min() << std::endl;
    std::cout << "Najveci element u Gomila 1: " << gomila1.max() << std::endl;
    std::cout << std::endl;
    gomila1.removeMin();
    std::cout << "gomila1 nakon brisanja najmanjeg elementa: " << gomila1;
    std::cout << "Novi najmanji element u Gomila 1: " << gomila1.min() << std::endl;
    std::cout << std::endl;
    gomila1.removeMax();
    std::cout << "Gomila1 nakon brisanja najveceg elementa: " << gomila1;
    std::cout << "Novi najveci element u Gomila 1: " << gomila1.max() << std::endl;
    return 0;
}