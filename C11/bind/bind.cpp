#include <gtest/gtest.h>
#include <functional>

using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

struct Person {
  Person(const string &name) {
    name_ = name;
  }
  void Greeting(string words, string reply) {
    cout << "Hi, i am " << name_ << ". and i want to tell you " << words << endl;
    cout << "Reply: " << reply << endl;
  }
  void SayHi(string words) {
    cout << "Hi, i am " << name_ << ". and i want to tell you " << words << endl;
  }
  string name_;
};


TEST_F(GTest, Bind_Obj_GTest) {
  Person xy("xy");
  auto sayHi = bind(&Person::SayHi, xy, placeholders::_1);
  sayHi("i love you baby!");
  function<void (const string &)> xyHi(sayHi);
  xyHi("why not ?");

  Person *xiaoxiao = new Person("xiaoxiao");
  function<void (const string &)> xiaoxiaoHi = bind(&Person::SayHi, xiaoxiao, placeholders::_1);
  xiaoxiaoHi("i love you too");


  function<void (const string &, const string &)> greeting = bind(&Person::Greeting, xiaoxiao, "hahahha", placeholders::_1);
  greeting("ilove you too","please let me drive?");
}

class Task{
public:
  template <class T, class... Args> // Member function.
  Task(const char *name, T *i, void (T::*func)(Args...), Args... args)
      : tsk_name(name), m_fun(std::bind(func, i, args...)) {}

  template <class F, class... Args> // Functor or global|static function.
  Task(const char *name, F func, Args... args)
      : tsk_name(name), m_fun(std::bind(func, args...)) {}

  virtual void Execute() {
    cout << "Task :" << tsk_name << endl;
    m_fun();
  }

private:
  const string tsk_name;
  function<void()> m_fun;
};


template <class T, class ...Args>
function<void ()> InjectTask(T *i, void (T::*func)(Args...), Args... args) {
  return bind(func, i, args...);
};

void Size(int size) {
  cout << "Size of "<< size << endl;
}

typedef void(*SizeFunc_t)(int);

TEST_F(GTest, Bind_Template_GTest) {
  Person *xy = new Person("xy");
  Task *tsk = new Task("Greeting", xy, &Person::Greeting, string("i love you baby"), string("i love you too"));
  tsk->Execute();
  cout << "=================================" << endl;
  auto func = InjectTask(xy, &Person::SayHi, string("i love you baby"));
  func();

  void (*size_func_ptr)(int) = &Size;
  (*size_func_ptr)(5);

  SizeFunc_t sizeFunc = Size;
  sizeFunc(5);


}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
