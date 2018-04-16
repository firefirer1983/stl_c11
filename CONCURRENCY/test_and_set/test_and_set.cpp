#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
#include <array>
#include <thread>
#include <atomic>

using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

bool test_and_set(bool *flag) {
  bool prev = *flag;
  *flag = true;
  return prev;
}
struct lock {
  lock() {
    held.clear();
  }
  void acquire() {
    while(held.test_and_set());
  }

  void release() {
    held.clear();
  }
private:
  atomic_flag  held;
};

const unsigned REPEAT_NUM = 10;
unsigned sum = 0;

lock spin_lock;

void Counting(const int offset, const unsigned repeat){
  for(unsigned i=0; i<repeat; i++) {
    spin_lock.acquire();
    cout << offset << endl;
    sum += offset;
    usleep(1);
    spin_lock.release();
  }

}

TEST_F(GTest, TEST_AND_SET_GTest){
  thread th1(Counting, 1, REPEAT_NUM);
  thread th2(Counting, -1, REPEAT_NUM);
  th1.join();
  th2.join();
  cout << "SUM: " << sum << endl;
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
