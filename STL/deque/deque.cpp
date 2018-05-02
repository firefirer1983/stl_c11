#include <gtest/gtest.h>
#include <string>
#include <ostream>
#include <deque>

using std::deque;
using std::string;
using std::cout;
using std::endl;

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

TEST_F(GTest, Deque_GTest){
  deque<Base> base_deque;
  cout << "init deque, push in back and pop in front, use as queue (FIFO) :" <<endl;
  for(int i=0; i<10; i++) {
    base_deque.emplace_back(i);
    cout << i << " ";
  }
  cout << endl;
  while(!base_deque.empty()) {
    cout << base_deque.front().Index() << " " ;
    base_deque.pop_front();
  }
  cout << endl;
  cout << "init deque, push in back and pop in back, use as stack (FILO):" <<endl;
  for(int i=0; i<10; i++) {
    base_deque.emplace_back(i);
    cout << i << " ";
  }
  cout << endl;
  while(!base_deque.empty()) {
    cout << base_deque.back().Index() << " " ;
    base_deque.pop_back();
  }
  cout << endl;
  cout << "init deque, dque is just like a double head vector, so it has iterator for random access:" <<endl;
  for(int i=0; i<10; i++) {
    base_deque.emplace_back(i);
    cout << i << " ";
  }
  cout << endl;
  cout << "itera from head to end" << endl;
  for(auto it=base_deque.begin(); it!=base_deque.end(); it++) {
    cout << it->Index() << " " ;
  }
  cout << endl;
  cout << "itera from end to head" << endl;
  for(auto it=base_deque.rbegin(); it!=base_deque.rend(); it++) {
    cout << it->Index() << " " ;
  }
}
int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
