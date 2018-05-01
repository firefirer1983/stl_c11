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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class GTest : public ::testing::Test {

protected:
  virtual void SetUp(){
  }
  
  virtual void TearDown(){
  }
};

TEST_F(GTest, SockConnectInfo_GTest) {

  int csock = 0;
  if((csock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("create socket failed!");
  }

  struct sockaddr_in server_sa;
  bzero(&server_sa, sizeof(server_sa));
  server_sa.sin_family = AF_INET;
  server_sa.sin_port = htons(80);
  inet_pton(AF_INET, "123.125.115.110", &server_sa.sin_addr);
  if(connect(csock, (struct sockaddr*)&server_sa, sizeof(server_sa)) < 0) {
    perror("connect error!");
  }

  struct sockaddr_storage addr;
  socklen_t len;
  char ip[] = "255.255.255.255";
  len = sizeof(addr);
  if(getpeername(csock, (sockaddr*)&addr, &len)) {
    perror("getpeername failed!");
  } else {
    struct sockaddr_in *sa = (struct sockaddr_in*)&addr;
    std::cout << "ip: " << inet_ntop(AF_INET, &(sa->sin_addr), ip, sizeof(ip)) << std::endl;
    std::cout << "port: " << sa->sin_port << std::endl;
  }
}

TEST_F(GTest, GetNameInfo_GTest) {

  char host[1024];
  char service[20];
  struct sockaddr_in server_sa;
  server_sa.sin_family = AF_INET;
  server_sa.sin_port = htons(80);
  inet_aton("123.125.115.110", &server_sa.sin_addr);

  getnameinfo((sockaddr *)&server_sa, sizeof(server_sa), host, sizeof(host), service ,sizeof(service), 0);
  std::cout<< "host: " << host << std::endl;
  std::cout << "service: " << service << std::endl;
}

TEST_F(GTest, GetHostByName_GTest){
  struct hostent *host_name = gethostbyname("baidu.com");

  if(host_name == nullptr) {
    std::cout << "err:" << hstrerror(h_errno) << std::endl;
    herror("gethostbyname");
  }

  struct in_addr **addr_list = (struct in_addr **)host_name->h_addr_list;
  char present[] = "255.255.255.255";
  for(unsigned i=0; addr_list[i]; i++) {
    std::cout << inet_ntop(AF_INET, addr_list[i], present, sizeof(present)) << std::endl;
  }
}

typedef union {
  unsigned short s;
  unsigned char f[2];
}Endian;

TEST_F(GTest, ByteOrder_GTest) {
//  The least significant byte (the "little end") of the data is placed at the byte with the lowest address
  Endian en;
  en.s = 0x0102;
  if(en.f[0] == 0x02) {
    std::cout << "little endian" << std::endl;
  } else if(en.f[0] == 0x01) {
    std::cout << "big endian" << std::endl;
  }

  en.s = htons(0x0102);
  if(en.f[0] == 0x02) {
    std::cout << "little endian" << std::endl;
  } else if(en.f[0] == 0x01) {
    std::cout << "big endian" << std::endl;
  }
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
