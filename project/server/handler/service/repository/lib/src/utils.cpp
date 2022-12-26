#include <iostream>

#include "utils.hpp"

std::string my_func() {
  std::string word1("world");
  std::string word2("hello");
  MyStruct my_obj(word1, word2);
  std::swap(my_obj.strl, my_obj.strr);
  // int *n = new int(4);
  // delete n;
  return my_obj.strl + ' ' + my_obj.strr;
}

// int main() { std::cout << my_func() << std::endl; }
