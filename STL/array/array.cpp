#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
#include <array>
#include <stdexcept>  

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::array;
using std::out_of_range;
using std::exception;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

void test_const_ref(int *const ref) {
  *ref = 5;
  cout << "const ref: " << *ref << endl;
}
void test_ref(int &ref) {
  ref = 6;
  cout << "ref: " << ref << endl;
}

TEST_F(GTest, Uninit_Array_Member_Is_0_GTest){
  const int ARRAY_SIZE = 100;
  array<int, ARRAY_SIZE> array_test = {0,1,2,3};
  for(int i=0; i< ARRAY_SIZE; i++) {
    cout << "array_test[" << i << "]=" << array_test[i] << endl;
  }
}

TEST_F(GTest, Array_Member_Visit_Check_GTest){
  const int ARRAY_SIZE = 100;
  array<int, ARRAY_SIZE> array_test = {0,1,2,3};
  const int out_of_array_idx = ARRAY_SIZE;
  cout << array_test[out_of_array_idx] << " array_test[100]= " << array_test[out_of_array_idx] << endl;
  try{
    array_test[out_of_array_idx] = array_test[out_of_array_idx];
  } catch(const out_of_range &err) {
    cout << err.what() << endl;
  }
  
  try{
    array_test.at(out_of_array_idx) = array_test.at(out_of_array_idx);
  } catch(const exception &err) {
    cout << err.what() << endl;
  }
}

TEST_F(GTest, Member_Visit_GTest){
  const int ARRAY_SIZE = 5;
  array<int, ARRAY_SIZE> array_test = {0,1,2,3,4};
  cout << "array_test: " << endl;
  for(int i=0; i< ARRAY_SIZE; i++) {
    cout << array_test[i] << " ";
  }
  cout << endl;

  EXPECT_EQ(array_test.front(), array_test[0]);
  EXPECT_EQ(array_test.data(), &array_test[0]);
  EXPECT_EQ(array_test.back(), array_test[ARRAY_SIZE-1]);
}

TEST_F(GTest, Iterator_GTest){
  const int ARRAY_SIZE = 5;
  array<int, ARRAY_SIZE> array_test = {0,1,2,3,4};
  cout << "array_test: " << endl;
  for(int i=0; i< ARRAY_SIZE; i++) {
    cout << array_test[i] << " ";
  }
  cout << endl;
  array<int, ARRAY_SIZE>::iterator itor = array_test.begin();
  EXPECT_EQ(array_test.front(), *itor);
  
  cout << "array_test loop by iterator" << endl;
  for(auto it=array_test.begin(); it!=array_test.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
  
  array<int, ARRAY_SIZE>::const_iterator citor = array_test.cbegin();
  EXPECT_EQ(array_test.front(), *citor);

  cout << "array_test loop by for(auto i:array_test) " << endl;
  for(auto mem:array_test) {
    cout << mem << " ";
  }
  cout << endl;
  
  cout << "array_test loop by reverse iterator" << endl;
  for(auto it=array_test.rbegin(); it!=array_test.rend(); it++) {
    cout << *it << " ";
  }
  cout << endl;
  
  array<int,ARRAY_SIZE> array_test_2 = {4,3,2,1,0};
  array_test.swap(array_test_2);
  cout << "after swaping: " << endl;
  for(auto i:array_test) {
    cout << i << " ";
  }
  cout << endl;

  array<int,ARRAY_SIZE> array_test_3 = {0,1,2,3,4};
  try{
    array_test_2.swap(array_test_3);
  }catch(const exception &err) {
    cout << err.what() << endl;
  }
  cout << endl;

  cout << "size: " << array_test.size() << endl;
  cout << "max_size: " << array_test.max_size() << endl;
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
