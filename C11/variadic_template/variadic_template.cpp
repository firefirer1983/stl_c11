#include <gtest/gtest.h>

using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

void print(){
  cout << endl;
}

template <typename T, typename ...Args>
void print(T t, Args... args) {
  cout << t << " ";
  print(args...);
};

TEST_F(GTest, PRINT_GTest){
  int a = 5;
  print(a,2,"i love you baby", '@');
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
