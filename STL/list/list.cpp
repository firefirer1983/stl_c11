#include <gtest/gtest.h>
#include <list>
#include <cmath>
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

}

bool is_odd(const int &value) {
  return value%2;
}

struct is_single_digit{
  bool operator()(const int &value){
    return value < 10;
  }
};

TEST_F(GTest, REMOVE_IF_GTest) {

  list<int> list_tst = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
  print_l(list_tst);
  cout << "Remove all the odd value:" << endl;
  list_tst.remove_if(is_odd);
  print_l(list_tst);
  list_tst.remove_if(is_single_digit());
  print_l(list_tst);
  cout << "Remove all the 1 digit number" << endl;

}

TEST_F(GTest, ADVANCE_GTest) {

  list<int> list_tst = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
  print_l(list_tst);
  auto it = list_tst.begin();
  std::advance(it, 5);
  cout << "From the begin advance 5 element:" << endl;
  cout << *it << endl;
  EXPECT_EQ(*it, 5);
}

bool compare_max(const int &first, const int &second) {
    return (first > second);
}

TEST_F(GTest, SORT_GTest) {

  list<int> list_tst = {16,1,2,7,4,5,6,3,8,9,10,11,12,13,14,15,0,17,18,19,20};
  print_l(list_tst);
  cout << "After sort with max algothm:" << endl;
  list_tst.sort(compare_max);
  print_l(list_tst);
  auto it = list_tst.begin();
  for(int i=20; i>=0; i--) {
    EXPECT_EQ(i, *it);
    it ++;
  }
}

TEST_F(GTest, SWAP_GTest) {

  list<int> list_tst_first = {0,1,2,3,4};
  list<int> list_tst_second = {5,6,7,8,9};
  print_l(list_tst_first);
  print_l(list_tst_second);
  cout << "After swap:" << endl;
  list_tst_first.swap(list_tst_second);
  print_l(list_tst_first);
  print_l(list_tst_second);
}

TEST_F(GTest, SPLICE_GTest) {

  list<int> list_tst_first = {0,1,2,3,4,5,10,11,12};
  list<int> list_tst_second = {11,12,6,7,8,9,13,14};
  print_l(list_tst_first);
  print_l(list_tst_second);
  cout << "After splice:" << endl;
  auto insert = list_tst_first.begin();
  std::advance(insert, 6);
  auto begin = list_tst_second.begin();
  std::advance(begin,2);
  cout << "begin: " << *begin << endl;
  auto end = list_tst_second.begin();
  std::advance(end,6);
  cout << "end: " << *end << endl;
  list_tst_first.splice(insert,list_tst_second,begin,end );
  print_l(list_tst_first);
  print_l(list_tst_second);
}
struct is_near{
  bool operator() (const double &first, const  double &second) {
    return (fabs(first-second)<1);
  }
};
struct Vector2 {
  Vector2() {
    cout << "Vector2 Created!" << endl;
  }
  ~Vector2() {
    cout << "Vector2 Destroyed!" << endl;
  }
  float x,y;
};
TEST_F(GTest, UNIQUE_GTest){
  list<double> list_tst = {0,1,1,2,4,5,10,10,12};
  print_l(list_tst);
  list_tst.unique();
  list<double> list_tst_double = {0,1.1,1.2,2,4,5,10.5,10.6,12};
  print_l(list_tst_double);
  list_tst_double.unique(is_near());
  print_l(list_tst);
  {
    Vector2 &vct = *(new Vector2);
  }
}

int main(int argc, char *argv[])
{


  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
