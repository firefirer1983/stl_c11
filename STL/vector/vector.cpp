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
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(GTest, Init_GTest) {
  vector<int> init_vct;
  cout << "Just Constructor:" << endl;
  cout << "size: " << init_vct.size() << endl;
  cout << "max_size: " << init_vct.max_size() << endl;
  cout << "capacity: " << init_vct.capacity() << endl;

  cout << "Reserve 1000:" << endl;
  init_vct.reserve(1000);
  cout << "size: " << init_vct.size() << endl;
  cout << "max_size: " << init_vct.max_size() << endl;
  cout << "capacity: " << init_vct.capacity() << endl;

  for (int i = 0; i < 10; i++) {
    init_vct.push_back(i);
  }
  cout << "Push back 10 elements" << endl;
  cout << "size: " << init_vct.size() << endl;
  cout << "max_size: " << init_vct.max_size() << endl;
  cout << "capacity: " << init_vct.capacity() << endl;

  init_vct.shrink_to_fit();
  cout << "Shrink to fit" << endl;
  cout << "size: " << init_vct.size() << endl;
  cout << "max_size: " << init_vct.max_size() << endl;
  cout << "capacity: " << init_vct.capacity() << endl;


  cout << "Push back 100000 elements to see how capacity change" << endl;
  unsigned capacity_prev = init_vct.capacity();
  for (int i = 0; i < 100000; i++) {
    init_vct.push_back(i);
    if (capacity_prev != init_vct.capacity()) {
      cout << "prev capacity: " << capacity_prev << " cur capacity: " << init_vct.capacity() << endl;
      capacity_prev = init_vct.capacity();
    }
  }

  init_vct.clear();
  EXPECT_TRUE(init_vct.empty());
  cout << "After clear call:" << endl;
  cout << "size: " << init_vct.size() << endl;
  cout << "max_size: " << init_vct.max_size() << endl;
  cout << "capacity: " << init_vct.capacity() << endl;
  EXPECT_EQ(capacity_prev, init_vct.capacity());
  cout << "After clear, capacity don't change" << endl;
  vector<int> vct;
  init_vct.swap(vct);
  cout << "After swap with a empty vector:" << endl;
  cout << "size: " << init_vct.size() << endl;
  cout << "max_size: " << init_vct.max_size() << endl;
  cout << "capacity: " << init_vct.capacity() << endl;
  EXPECT_EQ(init_vct.capacity(), 0);

  cout << "Create a vector from 0 to 9" << endl;
  for (int i = 0; i < 10; i++) {
    init_vct.push_back(i);
    cout << init_vct.at(i) << " ";
  }
  cout << endl;

  init_vct.insert(init_vct.end(),10);
  cout << "After insert 10 to before end:" << endl;
  for(auto mem:init_vct) {
    cout << mem << " ";
  }
  cout << endl;

  init_vct.insert(init_vct.begin(),-1);
  cout << "After insert -1 to before begin:" << endl;
  for(auto mem:init_vct) {
    cout << mem << " ";
  }
  cout << endl;
  cout << "Result of vector<int> v1(3, 111) : Create a vector with 3 element, each element value is 111" << endl;
  vector<int> v1(3, 111);
  for(auto v: v1) {
    cout << v << " ";
  }

  cout << endl;

  init_vct.insert(init_vct.begin()+7, {111,111,111});
  cout << "After insert v1 before the 7th element=>(6) in init_vct" << endl;
  for(auto mem: init_vct) {
    cout << mem << " ";
  }
  cout << endl;

  init_vct.resize(10);
  cout << "After init_vct to 10 elements: " << endl;
  for(auto mem: init_vct) {
    cout << mem << " ";
  }
  cout << endl;
  cout << "size: " << init_vct.size() << endl;
  cout << "max_size: " << init_vct.max_size() << endl;
  cout << "capacity: " << init_vct.capacity() << endl;
  cout << endl;

  cout << "Itera the vector from end to begin:" << endl;
  vector<int>::const_reverse_iterator it = init_vct.crbegin();
  for(;it!=init_vct.crend();it++) {
    cout << *it << " ";
  }
  cout << endl;


  cout << "Original vector: " << endl;
  for(auto it=init_vct.begin(); it!=init_vct.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
  cout << "Erase from begin to begin + 3: [begin:begin+3) " << endl;
  init_vct.erase(init_vct.begin(), init_vct.begin()+3);
  for(auto it=init_vct.cbegin(); it!=init_vct.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
  cout << "size: " << init_vct.size() << endl;
  cout << "max_size: " << init_vct.max_size() << endl;
  cout << "capacity: " << init_vct.capacity() << endl;
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
