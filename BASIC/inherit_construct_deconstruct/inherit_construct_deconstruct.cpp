#include <gtest/gtest.h>

using namespace std;

class Base {
public:
  Base() {
    cout << "Base Created" << endl;
  }
  ~Base() {
    cout << "Base Destroied" << endl;
  }
};

class Derived: public Base{
public:
  Derived() {
    cout << "Derived Created" << endl;
  }
  ~Derived() {
    cout << "Derived Destroied" << endl;
  }
};

class BaseV {
public:
  BaseV() {
    cout << "BaseV Created" << endl;
  }
  virtual ~BaseV() {
    cout << "BaseV Destroied" << endl;
  }
};

class DerivedV: public BaseV{
public:
  DerivedV() {
    cout << "DerivedV Created" << endl;
  }
  ~DerivedV() {
    cout << "DerivedV Destroied" << endl;
  }
};

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(GTest, NO_VIRTUAL_GTest){
  {
    Base *b1 = new Base;
    Base *d1 = new Derived;
    delete b1;
    delete d1;
  }
}

TEST_F(GTest, VIRTUAL_GTest){
  {
    BaseV *b1 = new BaseV;
    BaseV *d1 = new DerivedV;
    delete b1;
    delete d1;
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
