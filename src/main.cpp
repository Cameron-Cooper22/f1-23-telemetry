#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//TODO remake this line into <json/json.h> if I can figure out how
#include "PacketDefs.h"
#include "Constants.h"

#define PORT 20777



inline std::string getCurrentDateTime(std::string s) {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  if (s == "now")
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
  else if (s == "date")
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
  return std::string(buf);
};

inline void Logger(std::string logMsg) {

  std::string filepath = "/home/kinveth/logging/log_" + getCurrentDateTime("date") + ".txt";
  std::string now = getCurrentDateTime("now");

  std::ofstream ofs(filepath.c_str(), std::ios_base::out | std::ios_base::app);
  ofs << now << '\t' << logMsg << '\n';
  ofs.close();
};

enum Bartypes {
  BrakePressure,
  AcceleratorPressure,
  Gforce
};

class Bar {
public:
  int id;
  int val;

  Bar(int x, Bartypes y) {
    val = y;
    id = x;

    Logger("Bar Created - ID: " + std::to_string(x) + " Type: " + std::to_string(y));
  }

  void refresh() {}
};




int main(int argc, char** argv) {
  char *ip{(char *)"127.0.0.1"};
  
  struct sockaddr_in server_addr, client_addr;
  unsigned char buffer[1460];
  socklen_t addr_size;
  int n;
  
  int sockfd{socket(AF_INET, SOCK_DGRAM, 0)};
  if (sockfd < 0){
    perror("[-]socket error");
    Logger("Socket failed");
    exit(1);
  }

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(ip);
  
  n = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0){
    perror("[-]bind error");
    Logger("Socket Bind failed");
    exit(1);
  }
  if (strcmp(argv[1], "--get-packet")){
    // Zeroes out the buffer
    bzero(buffer, 1460);
    addr_size = sizeof(client_addr);

    // Modifies buffer to be what is sent to server
    recvfrom(sockfd, &buffer, 1460, 0, (struct sockaddr*)&client_addr, &addr_size);
    std::cout << buffer << std::endl;
  } else if (argv[1] == NULL) {
    while (true){
      // Zeroes out the buffer
      bzero(buffer, 1460);
      addr_size = sizeof(client_addr);

      // Modifies buffer to be what is sent to server
      recvfrom(sockfd, &buffer, 1460, 0, (struct sockaddr*)&client_addr, &addr_size);
      std::cout << buffer << std::endl;
    }
  } else {
    std::cout << "[-]Invalid Input" << std::endl;
  }
  return 0;
}
