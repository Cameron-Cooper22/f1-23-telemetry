#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include "Constants.h"
#include "PacketDefs.h"

#pragma comment(lib, "ws2_32.lib")

#define PORT 20777
#define BUFLEN 1460

int main() {
    // Start WINSOCK
    WSADATA wsa;
    WORD version = MAKEWORD(2, 2);
    int wsOk = WSAStartup(version, &wsa);
    if (wsOk != 0) {
        std::cout << "\t[-] Cannot init Winsock " << wsOk << "\n";
        exit(EXIT_FAILURE);
    }

    // Bind socket to IP
    SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in server{};
    server.sin_addr.S_un.S_addr = ADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT); // convert little endian to big endian
    // Little side note, htons may have to be taken out as the
    // current f1-23-telemetry UDP packets are in little endian,
    // and so is my computer. Unsure if conflicts will be created from this.

    if (bind(in, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cout << "\t[-] Failed to bind socket " << WSAGetLastError() << "\n";
        exit(EXIT_FAILURE);
    }

    sockaddr_in client{};
    int clientLen = sizeof(client);
    ZeroMemory(&client, sizeof(client));

    char buffer[BUFLEN];

    // Enter a loop
    while (true) {
        ZeroMemory(buffer, BUFLEN);

        // wait for message
        int bytesIn = recvfrom(in, buffer, BUFLEN, 0, (sockaddr*)&client, &clientLen);
        if (bytesIn == SOCKET_ERROR) {
            std::cout << "\t[-] Error recieving from client " << WSAGetLastError() << "\n";
            continue;
        }

        // display message and client info
        char clientIp[256];
        ZeroMemory(clientIp, 256);

        inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

        std::cout << "[+] Message recv from " << clientIp << ": \n" << buffer << "\n";
    }

    // close socket
    closesocket(in);

    // shutdown winsock
    WSACleanup();
}

