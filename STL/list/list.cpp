#include <gtest/gtest.h>
#include <list>

using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};
template <typename T>
void print_l(const list<T> &l) {
  for(auto it=l.begin(); it!=l.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}
TEST_F(GTest, Init_GTest){
  list<int> list_int;
  for (int i = 0; i < 10; i++) {
    list_int.push_back(i);
  }
  cout<<"init list with 0~9: " << endl;
  print_l(list_int);
  cout << endl;
  list<int> list_copy;
  list_copy.assign(list_int.begin(), list_int.end());
  cout << "list_copy:" << endl;
  print_l(list_copy);

  cout << "Remove 5 in list_copy" << endl;
  list_copy.remove(5);
  print_l(list_copy);
  cout << "size: " << list_copy.size() << endl;

  cout << "Erase element at position 5: " << endl;
  list<int>::iterator it = list_copy.begin();
  for(int i=0; i < 5; i++) {
    it ++;
  }
  list_copy.erase(it);
  print_l(list_copy);

  bool test = false;
  list_copy.remove_if(test);
}
int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
