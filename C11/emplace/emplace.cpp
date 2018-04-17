#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
#include <array>
#include <stdexcept>

using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};


class Box{
public:
  Box(int size)
      : size_(size){
    cout << "Constructor" << endl;
  }
  Box(const Box &box) {
    cout << "Copy constructor" << endl;
    size_ = box.size_;
  }
  unsigned Size() {
    return size_;
  }
private:
  unsigned size_;
};

TEST_F(GTest, Init_GTest){
  cout << "Create a vector, and reserve for 10 elements" << endl;
  vector<Box> box_vct;
  box_vct.reserve(10);
  cout << "Insert a 0 in the begin:" << endl;
  box_vct.insert(box_vct.begin(),0);
  for( auto box = box_vct.begin(); box!=box_vct.end(); box++) {
    cout << box->Size()<< " ";
  }
  cout << "Insert done!" <<endl;
  cout << "Emplace a 1 in the end:" << endl;
  box_vct.emplace(box_vct.end(),1);
  cout << "Emplace done!" <<endl;
  for(auto it=box_vct.begin(); it!=box_vct.end(); it++) {
    cout << it->Size() << " ";
  }
  cout << endl;
  cout << "emplace_back a box6:" << endl;
  box_vct.emplace_back(6);
  cout << "emplace_back done!" <<endl;
  for(auto it=box_vct.begin(); it!=box_vct.end(); it++) {
    cout << it->Size() << " ";
  }
  cout << endl;

}
TEST_F(GTest, Insert_GTest) {
  vector<Box> box_vct;
  box_vct.reserve(10);
  for(int i=0; i<10; i++ ) {
    box_vct.emplace_back(i);
  }

  for(auto &b: box_vct) {
    cout << b.Size() << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
