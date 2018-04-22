#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
#include <array>
#include <unordered_map>
#include <functional>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::array;
using std::unordered_map;
using std::pair;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

TEST_F(GTest, Init_GTest){
  unordered_map<string, string> color_map;
  pair< unordered_map<string,string>::iterator , bool> ret =  color_map.emplace("RED", "#FF0000");
  if(!ret.second) {
    cout << "insert " << ret.first->first <<  " failed!" << endl;
  }
  ret = color_map.emplace("GREEN", "#00FF00");
  if(!ret.second) {
    cout << "insert " << ret.first->first <<  " failed" << endl;
  }
  ret = color_map.emplace("BLUE", "#0000FF");
  if(!ret.second) {
    cout << "insert " << ret.first->first <<  " failed" << endl;
  }
  ret = color_map.emplace("RED", "#0000FF");

  if(!ret.second) {
    cout << "insert " << ret.first->first <<  " failed" << endl;
  }
  unordered_map<string,string>::iterator it = color_map.find("GREEN");
  if(it != color_map.end()) {
    cout << "find GREEN success: " << it->second << endl;
  }
  cout << "RED BUCKET: " << color_map.bucket("GREEN") << endl;
  cout << "GREEN BUCKET: " << color_map.bucket("GREEN") << endl;
  cout << "BLUE BUCKET: " << color_map.bucket("GREEN") << endl;

  cout << "map size: " << color_map.size() << endl;
  cout << "load factor" << color_map.load_factor() << endl;
  cout << "buckets count: " << color_map.bucket_count() << endl;
  cout << "max load factor" << color_map.max_load_factor() << endl;

}
int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
