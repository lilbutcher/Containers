
#include "../map/s21_map.h"
#include <gtest/gtest.h>

TEST(map, ConstructorDefaultMap) {
s21::map<int, char> my_empty_map;
std::map<int, char> orig_empty_map;
EXPECT_EQ(my_empty_map.empty(), orig_empty_map.empty());
}


TEST(map, ConstructorInitializerMap) {
s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
EXPECT_EQ(my_map.size(), orig_map.size());
auto my_it = my_map.begin();
auto orig_it = orig_map.begin();
for (; my_it != my_map.end(); ++my_it, ++orig_it) {
EXPECT_TRUE(my_it->first == orig_it->first);
EXPECT_TRUE(my_it->second == orig_it->second);
  }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}