#include <gtest/gtest.h>
#include <stack>

using std::string;
using std::cout;
using std::endl;
using std::stack;

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
  stack<Base> base_stack;
  cout << "stack is a FILO(First in last out data structure)" << endl;
  cout << "init stack:" << endl;
  for(int i=0; i<10; i++) {
    cout << i << " " ;
    base_stack.emplace(i);
  }
  cout << endl;
  cout << "Queue size: " << base_stack.size() << endl;
  while (!base_stack.empty()) {
    cout << base_stack.top().Index() << " ";
    base_stack.pop();
  }
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
