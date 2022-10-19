#include "QueueLinkedList.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  using Types::Queue;
  Queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(4);
  while (!queue.empty()) {
    std::cout << queue.pop() << std::endl;
  }
  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(1);
  queue.push(2);
  queue.push(3);
//  queue.ispis();
  Queue<int> queue2 = queue;
  Queue<int> queue3 = queue;
  std::cout << "Queue1" << std::endl;
  while (!queue.empty()) {
    std::cout << queue.pop() << std::endl;
  }
  
  Queue<int> queue4;
  queue4.push(51);
  queue4.push(52);
  queue4.push(53);

  queue4.swap(queue2);
  

  std::cout << "queue2" << std::endl;
  while (!queue2.empty()) {
    std::cout << queue2.pop() << std::endl;
  }
  queue2 = queue3;

  std::cout << "queue2 op=" << std::endl;
  while (!queue2.empty()) {
    std::cout << queue2.pop() << std::endl;
  }

  std::cout << "queue4" << std::endl;
  while (!queue4.empty()) {
    std::cout << queue4.pop() << std::endl;
  }
  return 0;
}
