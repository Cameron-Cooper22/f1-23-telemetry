#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "PacketDefs.h"

#define PORT 20777
#define SERVER_ADDRESS = ""

using namespace std;

inline string getCurrentDateTime(string s) {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  if (s == "now")
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
  else if (s == "date")
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
  return string(buf);
};

inline void Logger(string logMsg) {

  string filepath = "/Users/558632/logging/log_" + getCurrentDateTime("date") + ".txt";
  string now = getCurrentDateTime("now");

  ofstream ofs(filepath.c_str(), ios_base::out | ios_base::app);
  ofs << now << '\t' << logMsg << '\n';
  ofs.close();
};

enum Bartypes {
  BrakePressure,
  AcceleratorPressure,
  Gforce
};

class TelemetryClient {
  public:

    TelemetryClient(int port){
      Logger("TelemetryClient Created");
    }
};

class Bar {
public:
  int id;
  int val;

  Bar(int x, Bartypes y) {
    val = y;
    id = x;

    Logger("Bar Created - ID: " + to_string(x) + " Type: " + to_string(y));
  }

  void refresh() {}
};


int main() {
  return 0;
}
