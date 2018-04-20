#include <gtest/gtest.h>
#include <string>
#include <ostream>
#include <queue>

using std::string;
using std::cout;
using std::endl;
using std::queue;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

class Base {
  int idx;
public:
  Base(int id):idx(id) {
  }
  int Index() {
    return  idx;
  }
};

TEST_F(GTest, Queue_GTest){
  queue<Base> base_queue;
  cout << "queue is a FIFO(First in first out data structure)" << endl;
  cout << "init queue:" << endl;
  for(int i=0; i<10; i++) {
    cout << i << " " ;
    base_queue.emplace(i);
  }
  cout << endl;
  cout << "Queue size: " << base_queue.size() << endl;
  while (!base_queue.empty()) {
    cout << base_queue.front().Index() << " ";
    base_queue.pop();
  }
}
int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
