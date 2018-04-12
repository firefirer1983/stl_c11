#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
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

TEST_F(GTest, Init_GTest){
  const int ARRAY_SIZE = 100;
  array<int, ARRAY_SIZE> array_test = {0,1,2,3};
  for(int i=0; i< ARRAY_SIZE; i++) {
    cout << "array_test[" << i << "]=" << array_test[i] << endl;
  }
}
int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
