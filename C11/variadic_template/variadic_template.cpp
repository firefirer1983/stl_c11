#include <gtest/gtest.h>

using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

void print(){
  cout << endl;
}

template <typename T, typename...R>
void print(T t, R...r) {
  cout << t << " ";
  print(r...);
};

TEST_F(GTest, PRINT_GTest){
  int a = 5;
  print(a,2,"i love you baby", '@');
}

template <typename T>
struct StaticDelete{
  static void Delete(T *ptr) {
    delete ptr;
  }
};

template <typename T, typename D=StaticDelete<T> >
struct SmartPtr {

  SmartPtr(){
    cout << "sp empty constructor" << endl;
    m_ptr = nullptr;
    m_ref = 0;
  }
  SmartPtr(T *ptr){
    cout << "sp constructor" << endl;
    m_ref = 0;
    m_ptr = ptr;
    ++m_ref;
  }

  SmartPtr(SmartPtr &p) {
    cout << "sp copy constructor" << endl;
    m_ptr = p.m_ptr;
    m_ref = p.m_ref;
    p.m_ref ++;
  }

  SmartPtr &operator=(SmartPtr &p) {
    cout << "sp operator =" << endl;
    m_ptr = p.m_ptr;
    m_ref = p.m_ref;
    p.m_ref ++;
    return *this;
  }
  ~SmartPtr() {
    --m_ref;
    cout << "sp destructor cnt: "<< m_ref << endl;
    if(!m_ref) {
//      D::Delete(m_ptr);
      delete m_ptr;
      m_ptr = nullptr;
    }
  }
  T *operator->() {
    return m_ptr;
  }

  bool Expired() {
    return m_ptr == nullptr;
  }
private:
  static unsigned m_ref;
  T *m_ptr;
};

template <typename T, typename D>
unsigned SmartPtr<T,D>::m_ref = 0;

class Entity{
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

TEST_F(GTest, SMART_PTR_1ST_GTest){
  {
    cout << "entered 1st" << endl;
    {
      cout << "entered 2nd" << endl;
      SmartPtr<Entity> sp2(new Entity("fyman"));
      sp2->GetName();
      cout << "exiting 2nd" << endl;
      EXPECT_FALSE(sp2.Expired());
    }

    cout << "exited 2nd" << endl;
    cout << "exiting 1st" << endl;
  }
  cout << "exited 1st" << endl;
}

TEST_F(GTest, SMART_PTR_2ND_GTest){
  {
    SmartPtr<Entity> sp1;
    cout << "entered 1st" << endl;
    {
      cout << "entered 2nd" << endl;
      SmartPtr<Entity> sp2(new Entity("fyman"));
      sp2->GetName();
      SmartPtr<Entity> sp0 = sp2;
      sp1 = sp2;
      cout << "exiting 2nd" << endl;
      EXPECT_FALSE(sp2.Expired());
    }
    EXPECT_FALSE(sp1.Expired());
    cout << "exited 2nd" << endl;
    cout << "exiting 1st" << endl;
    SmartPtr<Entity> sp3(sp1);
  }
  cout << "exited 1st" << endl;
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
