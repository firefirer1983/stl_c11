#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>

using std::vector;
using std::string;
using std::cout;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

TEST_F(GTest, Create_GTest){
}
int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
