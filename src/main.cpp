#include <iostream>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sstream>

int sock;
struct sockaddr_in client;
int PORT = 443;

int main()
{
    struct hostent * host = gethostbyname("www.alphavantage.co");
    std::cout << host->h_addr << std::endl;

    if ( (host == NULL) || (host->h_addr == NULL) ) {
        std::cout << "Error retrieving DNS information." << std::endl;
        exit(1);
    }

    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons( PORT );
    memcpy(&client.sin_addr, host->h_addr, host->h_length);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        std::cout << "Error creating socket." << std::endl;
        exit(1);
    }

    if ( connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
        close(sock);
        std::cout << "Could not connect" << std::endl;
        exit(1);
    }

    std::stringstream ss;
    ss << "GET /query?function=LISTING_STATUS&state=active&datatype=json&apikey=dem4o HTTP/1.1\r\n"
       << "Host: www.alphavantage.co\r\n"
       << "Accept: application/json\r\n"
       << "Connection: close\r\n"
       << "\r\n\r\n";
    std::string request = ss.str();
    std::cout << request.c_str();

    if (send(sock, request.c_str(), request.length(), 0) != (int)request.length()) {
        std::cout << "Error sending request." << std::endl;
        exit(1);
    }

    char cur;
    while ( read(sock, &cur, 1) > 0 ) {
        std::cout << cur;
    }


    return 0;
}