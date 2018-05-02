#include <gtest/gtest.h>
#include <time.h>

#include <string>
#include <vector>
#include <ostream>
#include <utility>
#include <set>
#include <bitset>
#include <iterator>
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::set;
using std::bitset;
using std::pair;
using std::iterator;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

template <int size>
struct UniRandMarker {
  UniRandMarker() {
    used.reset();
  }
  bitset<size> used;
};

template <typename T, int size>
struct Rand {
  Rand() {
  }
  T GetRand() {
    srand(time(nullptr));

    rand_num=rand()%size - 1;
    unsigned offset = 0;
    unsigned pos = 0;
    while (marker.used[pos = (rand_num + offset)%size]) {
      offset++;
      if(offset == size - 1) {
        marker.used.reset();
      }
    }
    cout << pos << " ";
    marker.used.set(pos);
    return pos;
  }
  UniRandMarker<size> marker;
  T rand_num;
};

TEST_F(GTest, SetInit_GTest){
  set<int> int_set;
  Rand<int,10> box;
  for(int i=0; i<10; i++) {
    int_set.insert(box.GetRand());
  }
  cout << "init set: " << endl;
  for(auto it=int_set.begin(); it!=int_set.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
  pair< set<int>::iterator, bool> ret =  int_set.insert(0);
  EXPECT_FALSE(ret.second);
  pair< set<int>::iterator, bool> ret2 =  int_set.insert(10);
  EXPECT_TRUE(ret2.second);
  auto it = int_set.find(10);
  EXPECT_FALSE(it == int_set.end());
  auto it2 = int_set.find(11);
  EXPECT_TRUE(it2 == int_set.end());
}
int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
