//#include <iostream>
//#include "s21_set.h"
//
//int main() {
//  s21::set<int> mySet = {1, 2, 3, 4, 5};
//
//  // Использование функции begin и end
//  for(auto it = mySet.begin(); it != mySet.end(); ++it) {
//    std::cout << *it << " ";
//  }
//  std::cout << std::endl;
//
//  // Использование функции empty
//  std::cout << "Is empty: " << mySet.empty() << std::endl;
//
//  // Использование функции size
//  std::cout << "Size: " << mySet.size() << std::endl;
//
//  // Использование функции insert
//  auto [it, inserted] = mySet.insert(6);
//  if(inserted) {
//    std::cout << "Inserted successfully: " << *it << std::endl;
//  }
//
//  // Использование функции erase
//  mySet.erase(mySet.find(4));
//
//  // Использование функции find и contains
//  int key = 3;
//  if(mySet.contains(key)) {
//    std::cout << key << " found in set" << std::endl;
//  } else {
//    std::cout << key << " not found in set" << std::endl;
//  }
//
//  // Использование функции clear
//  mySet.clear();
//  std::cout << "Cleared set. Is empty: " << mySet.empty() << std::endl;
//
//  return 0;
//}