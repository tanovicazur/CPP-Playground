#pragma once

#include <iostream>
namespace Types {

template <typename T>
class List {
  public:
  virtual List& push_back(const T&) = 0;
  virtual List& push_front(const T&) = 0;
  virtual List& pop_front() = 0;
  virtual List& pop_back() = 0;
  virtual bool empty() const = 0;
  virtual size_t size() const = 0;
};
} /* Types */
