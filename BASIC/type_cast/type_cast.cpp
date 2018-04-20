#include <gtest/gtest.h>
#include <stdarg.h>
#include <time.h>

using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

enum EN {
  EN_1ST,
  EN_2ND
};

TEST_F(GTest, TYPE_SIZE_GTest){
  EXPECT_EQ(sizeof(int), 4);
  EXPECT_EQ(sizeof(short), 2);
  EXPECT_EQ(sizeof(char), 1);
  EXPECT_EQ(sizeof(unsigned), 4);
  EXPECT_EQ(sizeof(long), 8);
  EXPECT_EQ(sizeof(long long), 8);
  EXPECT_EQ(sizeof(float), 4);
  EXPECT_EQ(sizeof(double), 8);
  EXPECT_EQ(sizeof(bool), 1);
  EXPECT_EQ(sizeof(enum EN), 4);
}

struct Person {
  int id;
  int height;
  bool male;
  char capital;
};

class Base{
public:
  virtual ~Base(){};
  virtual void Greeting() {
    cout << " I am a Base class object" <<endl;
  }
};
class Derived1:public Base{
  string address;

public:
  Derived1() {
    address = "Guangdong shenzhen";
  }
  ~Derived1(){};
  void Greeting() {
    cout << " I am a Derived1 class object" <<endl;
  }
};
class Derived2:public Base{
  string name;
public:
  Derived2() {
    name = "fyman";
  }
  ~Derived2(){};
  void Greeting() {
    cout << " I am a Derived2 class object" <<endl;
  }

  void TellName() {
    cout << "I am " << name << endl;
  }
};

TEST_F(GTest, REINTERPRET_CAST_GTest){
  Person *pFyman = new Person;
  pFyman->id = 1;
  pFyman->height = 171;
  pFyman->male = true;
  pFyman->capital = 'F';

  int *id = reinterpret_cast<int *>(pFyman);
//  int *id1 = static_cast<int *>(pFyman);
  cout << *id << endl;
//  cout << *id1 << endl;
}

TEST_F(GTest, STATIC_CAST_GTest){
  Base *b1 = new Derived1;
  Base *b2 = new Base;

  Derived1 *d1 = static_cast<Derived1 *>(b1);
  d1->Greeting();
  Derived1 *d2 = static_cast<Derived1 *>(b2);
  d2->Greeting();

}

TEST_F(GTest, TYPEID_GTest){
  Base *b1 = new Derived1;
  Base *b2 = new Base;

  cout << typeid(b1).name() << endl;
  cout << typeid(b2).name() << endl;
  EXPECT_TRUE(typeid(b1) == typeid(b2));

  cout << typeid(static_cast<Derived1 *>(b1)).name() << endl;
  cout << typeid(static_cast<Derived1 *>(b2)).name() << endl;
  EXPECT_TRUE(typeid(static_cast<Derived1 *>(b1)) == typeid(static_cast<Derived1 *>(b2)));
}

TEST_F(GTest, DYNAMIC_CAST_GTest){
  srand(time(nullptr));
  Base *b1 = ((rand()%2)? static_cast<Base*>(new Derived1):static_cast<Base*>(new Derived2));
  if(dynamic_cast<Derived1*>(b1)) {
    cout << "Derived1 Object" << endl;
  } else if(dynamic_cast<Derived2*>(b1)) {
    cout << "Derived2 Object" << endl;
  }
}

TEST_F(GTest, STAITC_VS_DYNAMIC_CAST_GTest){
  Base *b = new Derived1;
  Derived2 *d2 = static_cast<Derived2 *>(b);
  d2->TellName();

  Derived2 *d2_r = dynamic_cast<Derived2 *>(b);
  if(d2_r) {
    d2_r->TellName();
  } else {
    cout << "it not a Derived2 class object" << endl;
  }

}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
