#include <gtest/gtest.h>
#include <memory>

using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

class Container{
public:
  Container(int val) {
    value = val;
    cout << "Container Constructor=> val:" << val << endl;
  };
  Container(const Container &c) {
    cout << "Copy Container=> val: " <<endl;
  }
  ~Container(){
    cout << "Container Destroyed! => val:" << value << endl;
  }
  int value;
  int Get() {
    return value;
  }
};


class Shape{
public:
  Shape() { cout << "Shape Constructor" << endl; }
  virtual ~Shape() { cout << "Shape Destructor" << endl; }
  virtual void draw() const = 0;
};

class Circle: public Shape {
  double center;
  double radiums;
public:
  Circle(double c, double r):Shape(),
           center(c),
           radiums(r)
  {
    cout << "Circle Constructor" << endl;
  }
  ~Circle() { cout << "Circle Destructor" << endl; }

  virtual void draw() const  { cout << "draw Circle" << endl; }
};

class Smile: public Circle {
public:
  Smile(double x, double y):
      Circle(0, 5),
      pos(new double[2])
  {
    pos[0] = x;
    pos[1] = y;
    cout << "Smile Constructor" << endl;
  }

  ~Smile() {
    cout << "Smile Destructor" << endl;
    delete[] pos;
    pos = nullptr;
  }
  void set(double x, double y) {
    pos[0] = x;
    pos[1] = y;
  }
  void draw() const override {
    Circle::draw();
    printf("draw Smile x:%f y:%f\n",pos[0], pos[1]);
  }

private:
  double *pos;
};

class Vector {
public:
  Vector(std::initializer_list<double>lst):
      sz_(lst.size()),
      ary_(new double[sz_]){
    int i = 0;
    for(auto &m:lst) {
      ary_[i] = m;
      ++i;
    }
  }

  void clear() {
    for(unsigned i=0; i!=sz_; i++) {
      ary_[i] = 0;
    }
  }
  void show() {
    for(unsigned i=0; i!=sz_; i++) {
      printf("%f ",ary_[i]);
    }
    printf("\n");
  }
  ~Vector(){
    if(ary_) {
//      delete[] ary_;
//      ary_ = nullptr;
    }
  }
private:
  size_t sz_;
  double *ary_;
};



TEST_F(GTest, CopyConstructor_GTest){
  Vector v1({1.0,2.0,3.0,4.0,5.0});
  Vector v2 = v1;
  v1.show();
  v2.show();
  v1.clear();
  v2.show();
}

unique_ptr<Container> getOneContainer() {
//  {
//    unique_ptr<Container>p1  =  unique_ptr<Container>(new Container(5));
//    unique_ptr<Container>ret = std::move(p1);
//  }
  return std::move(unique_ptr<Container>(new Container(10)));
}
TEST_F(GTest, UNIQUE_PTR_GTest){
  {
    unique_ptr<Container> cPtr(new Container(7));
    cout << "Get return for unique_ptr " << cPtr->Get() << endl;
  }
  {
    unique_ptr<Container> outer = getOneContainer();
  }

}

TEST_F(GTest, SHARED_PTR_GTest){
  {
    cout <<  "entered 1st bracket" << endl;
    shared_ptr<Container> s1;
    {
      cout <<  "entered 2nd bracket" << endl;
      shared_ptr<Container> s2 = make_shared<Container>(8);
      cout << "Get return for unique_ptr " << s2->Get() << endl;
      s1 = s2;
      cout <<  "exiting 1st bracket" << endl;
    }
    cout <<  "exiting 2nd bracket" << endl;
  }
}

TEST_F(GTest, WEAK_PTR_GTest){
  {
    cout <<  "entered 1st bracket" << endl;
    weak_ptr<Container> w1;
    {
      cout <<  "entered 2nd bracket" << endl;
      shared_ptr<Container> s2 = make_shared<Container>(8);
      cout << "Get return for unique_ptr " << s2->Get() << endl;
      w1 = s2;
      cout << "w1 expired:" << w1.expired()<< endl;
      shared_ptr<Container> s3 = w1.lock();
      if(s3) {
        cout << "w1 expired: " << w1.expired() << endl;
        cout << "promote w1 to s3 successed, s2 value: " << s3->Get() << endl;
      }
      cout << "w1 value:" << s3->Get() << endl;
      cout <<  "exiting 1st bracket" << endl;
    }
    cout <<  "exited 1st bracket" << endl;
    auto s4 = w1.lock();
    if(s4) {
      cout << "promote w1 to s4 successed, s4 value: " << s4->Get() << endl;
    } else {
      cout << "promote w1 to s4 failed!" << endl;
      cout << "w1 expired:" << w1.expired() << endl;
    }
    cout <<  "exiting 2nd bracket" << endl;
  }
  cout <<  "exited 2nd bracket" << endl;

}

struct RefCount {
  RefCount(): ref_(0) {
  }

  void AddRef() {
    ++ref_;
  }

  unsigned ReleaseRef() {
    return --ref_;
  }

  unsigned GetRef() {
    return ref_;
  }

private:
  unsigned ref_;
};

template<typename T>
class sp {
public:
  sp() {
    ptr_ = nullptr;
    rc_ = new RefCount;
    rc_->AddRef();
    cout << "sp empty constructor rc: " << rc_->GetRef() << endl;
  }

  sp(T *ptr) {
    ptr_ = ptr;
    rc_ = new RefCount;
    rc_->AddRef();
    cout << "sp constructor rc: " << rc_->GetRef() << endl;
  }

  ~sp() {
    cout << "sp deconstructor rc: " << rc_->GetRef() << endl;
    if (!rc_->ReleaseRef()) {
      delete ptr_;
      ptr_ = nullptr;
      delete rc_;
    }
    rc_ = nullptr;

  }

  sp(const sp<T> &p) :rc_(p.rc_), ptr_(p.ptr_){
    if(&p != this) {
      rc_->AddRef();
      cout << "sp copy constructor rc: " << rc_->GetRef() << endl;
    }
  }

  sp<T> &operator=(const sp<T> &p) {
    if(&p != this) {
      /*
      *  because the old value is obsoleted ,
       *  so the entity it original hold should check for deconstructor
      */
      if (!(rc_->ReleaseRef())) {
        cout << " = operator make old right value refcount == 0" << endl;
        delete ptr_;
        delete rc_;
      }
      p.rc_->AddRef();
      rc_ = p.rc_;
      ptr_ = p.ptr_;
    }
    cout << "sp copy constructor rc: " << rc_->GetRef() << endl;
    return *this;
  }

  T *operator->() {
    return ptr_;
  }

  T& operator*() {
    return *ptr_;
  }

  bool Expired() {
    return ptr_ == nullptr;
  }

private:
  RefCount *rc_;
  T *ptr_;
};

class Entity {
public:
  Entity(const string &name) {
    cout << "Entity Created" << endl;
    m_name = name;
  }

  ~Entity() {
    cout << "Entity Destroyed" << endl;
  }

  string GetName() {
    return m_name;
  }

private:
  string m_name;
};

TEST_F(GTest, SMART_PTR_GTest) {
  {
    sp<Entity> sp1;
    cout << "entered 1st" << endl;
    {
      cout << "entered 2nd" << endl;
      sp<Entity> sp2(new Entity("fyman"));
      sp2->GetName();
      sp<Entity> sp0 = sp2;
      sp1 = sp2;
      cout << "exiting 2nd" << endl;
      EXPECT_FALSE(sp2.Expired());
    }
    EXPECT_FALSE(sp1.Expired());
    cout << "exited 2nd" << endl;
    cout << "exiting 1st" << endl;
    sp<Entity> sp3(sp1);
  }
  cout << "exited 1st" << endl;

}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
