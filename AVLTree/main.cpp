#include <iostream>
#include <string>
#include <map>
#include "AVLTree.h"
//#include "../map/s21_map.h"
//#include "../set/s21_set.h"

int main() {


  AVLTree<int, std::string> avlTree;

  avlTree.insert(15, "First");
  avlTree.insert(14, "Second");
  avlTree.insert(20, "Third");
  avlTree.insert(27, "Third");
//  avlTree.insert(25, "qwe");
//  avlTree.insert(35, "Third");
//  avlTree.insert(32, "Third");

  std::map<int, std::string> myMap;


  myMap.insert(std::make_pair(15, "First"));
  myMap.insert(std::make_pair(14, "Second"));
  myMap.insert(std::make_pair(20, "Third"));
  myMap.insert(std::make_pair(27, "Third"));




  AVLTree<int, std::string>::iterator it = avlTree.findMin(avlTree.root);

  std::cout << it->first << std::endl;

  std::cout << it->second << std::endl;


  return 0;
}
