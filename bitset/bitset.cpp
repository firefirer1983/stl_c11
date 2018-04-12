#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iostream>
#include <array>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::array;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;  
}
