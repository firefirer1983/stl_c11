#include <string>
#include <vector>
#include <ostream>
#include <array>
#include <stdexcept>  


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

const unsigned BUF_SIZE = 2048;
int main(int argc, char *argv[])
{
  char buf[BUF_SIZE] = {0};
  while(fgets(buf, sizeof(buf), stdin) != nullptr) { //enter ctrl + d , fgets will return nullptr
    fputs(buf, stdout);
  }
  return 0;
}
