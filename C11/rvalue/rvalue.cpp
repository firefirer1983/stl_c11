#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
#include <array>
#include <stdexcept>  

using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

class Vector {
public:
  Vector(){
    cout << "Constructor" << endl;
    array_ = new int[10];
    for(int i=0; i<10; i++) {
      array_[i] = i;
    }
  }
  Vector(const Vector& v) {
    cout << "Copy Constructor!" << endl;
    array_ = new int[10];
    for(int i=0; i<10; i++) {
      array_[i] = v.array_[i];
    }
  }
  Vector(Vector&& v) {
    cout << "R Value Copy Constructor!" << endl;
    array_ = v.array_;
    v.array_ = nullptr;
  }
  ~Vector(){
    delete [] array_;
  }
  void print_v() {
    for(int i=0; i<10; i++) {
      cout << array_[i] << " ";
    }
    cout << endl;
  }
  int *array_;
};

void PrintVector(Vector vct) {
  vct.print_v();
}

Vector CreateVector() {
  return Vector();
}

TEST_F(GTest, Test_GTest){
  Vector reusable = CreateVector();
  PrintVector(reusable);
  PrintVector(move(reusable));
  PrintVector(CreateVector());
  PrintVector(Vector());

  EXPECT_EQ(reusable.array_, nullptr);
}
int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
