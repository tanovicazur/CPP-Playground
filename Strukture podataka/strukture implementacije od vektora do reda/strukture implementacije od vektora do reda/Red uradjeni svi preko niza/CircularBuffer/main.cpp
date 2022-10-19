#include "CircularBuffer.hpp"
#include <iostream>

int main(int argc, char* argv[]) {

  using Types::CircularBuffer;
  CircularBuffer<int> buffer;
  buffer.push(1).push(2).push(3);
  buffer.push(1).push(2).push(3);
  std::cout << buffer << std::endl;

  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  std::cout << buffer << std::endl;

  buffer.push(1).push(2).push(3);
  buffer.push(1).push(2).push(3);
  buffer.push(1).push(2).push(3);
  buffer.push(1).push(2).push(3);
  
  std::cout << buffer << std::endl;

  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  buffer.pop();
  //buffer.pop();
  buffer.push(1).push(2).push(3);
  buffer.push(1).push(2).push(3);
  //   buffer.pop();
  //   buffer.pop();
  //   buffer.pop();
  //   buffer.pop();

  std::cout << buffer << std::endl;
  std::cout << buffer.size() << std::endl;
  return 0;
}
