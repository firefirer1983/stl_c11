#include <gtest/gtest.h>
#include <stdarg.h>
using namespace std;

class GTest : public ::testing::Test {

protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

#define LOG_TAG "VARIADIC_MACRO"
enum LOG_LV{
  LOG_DBG,
  LOG_ERR,
};

void print(LOG_LV lv, const char *tag, const char *format, ...) {
  va_list ap;
  char buf[2048];
  va_start(ap, format);
  vsnprintf(buf, 2048, format, ap);
  va_end(ap);
  switch(lv) {
    case LOG_DBG:{
      printf("dbg: ");
      break;
    }
    case LOG_ERR: {
      printf("err: ");
    }
  }
  printf("[ %s ] ",tag);
  printf("%s", buf);
}

#define LOG(lv,tag, format, args...) print(lv,tag,format,args)

#define LOGD(format, args...) LOG(LOG_DBG, LOG_TAG, format, args)
#define LOGE(format, args...) LOG(LOG_ERR, LOG_TAG, format, args)

TEST_F(GTest, PRINT_GTest){
  LOGD("i love you %s\n", "xiaoxiao");
  LOGE("are you are stupid? %s\n", "steven");
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
