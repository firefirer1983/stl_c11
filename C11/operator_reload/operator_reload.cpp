#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
#include <array>
#include <stdexcept>
#include <memory>

using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

class complex{
public:
  double real;
  double imag;
  complex() : real(0.0), imag(0.0){ }
  complex(double a, double b) : real(a), imag(b){ }
  void display()const{ cout << real << " + " << imag << "i" << endl; }

  complex operator+(const complex &y) {
    cout << "In complex c+c" << endl;
    complex tmp;
    tmp.real = real + y.real;
    tmp.imag = imag + y.imag;
    return tmp;
  }

  complex operator+(const float &y) {
    cout << "In complex c+f" << endl;
    complex tmp;
    tmp.real = real + y;
    tmp.imag = imag;
    return tmp;
  }
};

complex operator+(const float &A, const complex &B){ // this is a global operator reload!
  cout << "In global f+c" << endl;

  complex C;
  C.real = A + B.real;
  C.imag = B.imag;
  return C;
}

TEST_F(GTest, WEAK_PTR_GTest){
  complex c1(4.3, 5.8);
  complex c2(2.4, 3.7);
  complex c3;
  c3 = c1 + c2;
  c3.display();
  complex c4;
  c4 = 4 + c3;
  c4.display();
  complex c5 = c3 + 6;
  c5.display();

}

int main(int argc, char *argv[]) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
