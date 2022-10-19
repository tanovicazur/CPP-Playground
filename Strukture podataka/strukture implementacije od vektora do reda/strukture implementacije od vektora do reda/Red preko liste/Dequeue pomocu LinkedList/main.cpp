#include <iostream>

#include "DequeueLinkedList.hpp"

int main(int argc, char* argv[]) {
  using Types::Dequeue;
  Dequeue<int> deq;
  // 6 4 3 1 2 5 7
  deq.push_back(1)
      .push_back(2)
      .push_front(3)
      .push_front(4)
      .push_back(5)
      .push_front(6)
      .push_back(7);
  std::cout << "Test 1" << std::endl;
  std::cout << deq << std::endl;
  std::cout << deq.pop_back() << std::endl;
  std::cout << deq.pop_front() << std::endl;
  std::cout << deq.pop_front() << std::endl;
  std::cout << deq.pop_back() << std::endl;
  std::cout << deq.pop_front() << std::endl;
  // EXPECTED:  1 2
  std::cout << "test 2" << std::endl;
  std::cout << deq << std::endl;
  deq.push_back(-1)
      .push_back(-2)
      .push_front(-3)
      .push_front(-4)
      .push_back(-5)
      .push_front(-6)
      .push_back(-7);
  // EXPECTED: -6 -4 -3 1 2 -1 -2 -5 -7
  std::cout << "test 3" << std::endl;
  std::cout << deq << std::endl;
  std::cout << deq.pop_back() << std::endl;
  std::cout << deq.pop_front() << std::endl;
  std::cout << deq.pop_front() << std::endl;
  std::cout << deq.pop_back() << std::endl;
  std::cout << deq.pop_front() << std::endl;
  return 0;
}
