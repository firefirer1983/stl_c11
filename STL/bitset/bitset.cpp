#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <bitset>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::array;
using std::bitset;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

const unsigned BITSET_SIZE = 256;

void print_b(bitset<BITSET_SIZE> &set) {
  int cnt = set.size();
  if(cnt > 0) {
    for(int i=0; i<cnt; i++) {
      cout << set[i] << " ";
    }
  }
  cout << endl;
}

TEST_F(GTest, BitSet_GTest){
  bitset<BITSET_SIZE> used;
  cout << "Initial bitset:" <<endl;
  cout << "count: " << used.count() << endl;
  cout << "size: " << used.size() << endl;
  print_b(used);
  for(unsigned i=0; i<BITSET_SIZE; i++) {
    used[i] = true;
  }
  print_b(used);
  EXPECT_EQ(used.count(), BITSET_SIZE);
  used[5] = false;
  EXPECT_EQ(used.count(), BITSET_SIZE-1);
  used[5].flip();
  EXPECT_EQ(used.count(), BITSET_SIZE);
  cout <<"Stringify:" <<  used.to_string() << endl;

  bitset<8> highest("10000000");
  EXPECT_TRUE(highest[7]);
  EXPECT_EQ(highest.to_ulong(), 128);
  EXPECT_TRUE(highest.test(7));
  EXPECT_TRUE(highest.any());
  EXPECT_TRUE(highest.flip(7).none());
  EXPECT_EQ(highest.flip(),255);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
