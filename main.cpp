#include "s21_map.h"
#include <iostream>

int main() {
  s21::map<int, std::string> myMap;


  // Inserting values using insert()
  myMap.insert({4, "Four"});
  myMap.insert({5, "Five"});
  myMap.insert({2, "Five"});


  s21::map<int, std::string>::iterator it = myMap.begin();

  std::cout <<  << std::endl;

  return 0;
}