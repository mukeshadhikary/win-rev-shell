#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error initializing Winsock" << std::endl;
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("IP_ADDRESS_OF_NETCAT_LISTENER");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_NUMBER);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    std::cout << "Connected to netcat listener" << std::endl;

    // Send and receive data over the socket

    closesocket(sock);
    WSACleanup();
    return 0;
}
