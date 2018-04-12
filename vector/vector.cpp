#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::vector;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

template <typename T>
class Container{
public:
  typedef T value_type;
  Container(T val) {
    value = val;
  };
  T value;
  T Get() {
    return value;
  }
};

template <typename C>
typename C::value_type DoubleValue(C container) {
  typename C::value_type val = container.Get();
  return 2*val;
};

TEST_F(GTest, Init_GTest){
  int y = 2;
  Container<int> box(y);
  EXPECT_EQ(DoubleValue(box), 4);
}


int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
