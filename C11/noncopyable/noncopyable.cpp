#include <stdio.h>

class Base{
public:

  Base(){
  }

  void hi() {
    printf("hi, b!\n");
  }
  Base(const Base &b) = delete;

  Base operator=(const Base &b) = delete;
private:

};

class Derive: public Base{
public:
  Derive() {
  }
  void hi() {
    printf("hi, d\n");
  }
};

void hello(Base b) {
  b.hi();
}
void hello_derive(Derive d) {
  d.hi();
}
int main(int arvc, char *argv[]) {
  Derive d1;
  Derive d3 = d1;
  Derive d4;
  hello_derive(d3);
  d4 = d1;
  return 0;
}
