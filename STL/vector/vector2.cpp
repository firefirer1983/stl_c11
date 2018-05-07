#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
#include <queue>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::queue;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};
const unsigned MAX_SLICE_CHK_NUM = 8;
TEST_F(GTest, Init_GTest) {
  unsigned slice_num = 27;
  double end = slice_num;
  std::queue<unsigned> idx_queue;
  double interval = 1.0;
  if(end > MAX_SLICE_CHK_NUM) {
    interval = end/MAX_SLICE_CHK_NUM;
  }
  std::cout << "interval: " << interval << " end: " << end << endl;
  for(double pos = 0.0; pos < end; pos += interval) {
    idx_queue.push((unsigned)(pos+0.5));
  }
  while(!idx_queue.empty()) {
    std::cout << idx_queue.front() << " ";
    idx_queue.pop();
  }

  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
