#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
#include <array>
#include <map>
#include <utility>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::array;
using std::map;
using std::pair;
using std::make_pair;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

TEST_F(GTest, Insert_GTest) {
  map<string, unsigned> age_map;
  age_map.emplace("fyman", 34);
  age_map.emplace("xiaoxiao", 27);
  cout << "map size: " << age_map.size() << endl;
  pair<string, unsigned> info = make_pair(string("helijing"), 34U);
  pair<map<string, unsigned>::iterator, bool> ret = age_map.insert(info);
  cout << "insert ret: " << ret.second << endl;
  if (!ret.second) {
    cout << "insert " << ret.first->first << " failed!" << endl;
  }
  pair<map<string, unsigned>::iterator, bool> ret2 = age_map.insert(info);
  cout << "insert ret: " << ret2.second << endl;
  if (!ret2.second) {
    cout << "insert " << ret2.first->first << " failed!" << endl;
  }
}

TEST_F(GTest, Find_GTest) {
  map<string, unsigned> age_map;
  age_map.emplace("fyman", 34);
  age_map.emplace("xiaoxiao", 27);
  cout << "map size: " << age_map.size() << endl;
  pair<string, unsigned> info = make_pair(string("helijing"), 34U);
  pair<map<string, unsigned>::iterator, bool> ret = age_map.insert(info);
  cout << "insert ret: " << ret.second << endl;
  if (!ret.second) {
    cout << "insert " << ret.first->first << " failed!" << endl;
  }
  map<string, unsigned>::iterator it = age_map.find(string("helijing"));
  cout << it->first << " is " << it->second << " years old" << endl;

  cout << "Name&Age:" << endl;
  for(auto &it: age_map) {
    cout << it.first << " :" << it.second << endl;
  }
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
