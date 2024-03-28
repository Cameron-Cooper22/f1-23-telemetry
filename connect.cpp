#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 20777

int main(){
  char *ip{(char *)"127.0.0.1"};

  int sockfd;
  struct sockaddr_in addr;
  char buffer[1460];
  socklen_t addr_size;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr(ip);

  bzero(buffer, 1460);
  strcpy(buffer, "This is a test of UDP sending");
  sendto(sockfd, buffer, 1460, 0, (struct sockaddr*)&addr, sizeof(addr));

  std::cout << "Data sent" << std::endl;
}
