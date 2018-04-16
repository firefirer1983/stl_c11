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

class Container{
public:
  Container(int val) {
    cout << "Container Created" << endl;
    value = val;
  };
  Container(const Container &c) {
    cout << "Copy Container" <<endl;
  }
  ~Container(){
    cout << "Container Destroyed!" << endl;
  }
  int value;
  int Get() {
    return value;
  }
};


TEST_F(GTest, UNIQUE_PTR_GTest){
  {
    unique_ptr<Container> cPtr(new Container(7));
    cout << "Get return for unique_ptr " << cPtr->Get() << endl;
  }
}

TEST_F(GTest, SHARED_PTR_GTest){
  {
    cout <<  "entered 1st bracket" << endl;
    shared_ptr<Container> s1;
    {
      cout <<  "entered 2nd bracket" << endl;
      shared_ptr<Container> s2 = make_shared<Container>(8);
      cout << "Get return for unique_ptr " << s2->Get() << endl;
      s1 = s2;
      cout <<  "exiting 1st bracket" << endl;
    }
    cout <<  "exiting 2nd bracket" << endl;
  }
}

TEST_F(GTest, WEAK_PTR_GTest){
  {
    cout <<  "entered 1st bracket" << endl;
    weak_ptr<Container> w1;
    {
      cout <<  "entered 2nd bracket" << endl;
      shared_ptr<Container> s2 = make_shared<Container>(8);
      cout << "Get return for unique_ptr " << s2->Get() << endl;
      w1 = s2;
      cout << "w1 expired:" << w1.expired()<< endl;
      shared_ptr<Container> s3 = w1.lock();
      if(s3) {
        cout << "w1 expired: " << w1.expired() << endl;
        cout << "promote w1 to s3 successed, s2 value: " << s3->Get() << endl;
      }
      cout << "w1 value:" << s3->Get() << endl;
      cout <<  "exiting 1st bracket" << endl;
    }
    cout <<  "exited 1st bracket" << endl;
    auto s4 = w1.lock();
    if(s4) {
      cout << "promote w1 to s4 successed, s4 value: " << s4->Get() << endl;
    } else {
      cout << "promote w1 to s4 failed!" << endl;
      cout << "w1 expired:" << w1.expired() << endl;
    }
    cout <<  "exiting 2nd bracket" << endl;
  }
  cout <<  "exited 2nd bracket" << endl;

}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
