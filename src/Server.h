/*
 * Server.h
 *
 *  Created on: Jan 14, 2018
 *      Author: scud
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <netinet/ip.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
class Server {
private:
    int serverfd, clientfd;
	int portNum;
	int bufferSize = 1024;
    bool errorFlag;
    struct sockaddr_in server_addr;
    socklen_t size;

public:
	Server(int port);
	~Server();

	/**
	 * Bind the socket.
	 */
	void bindSocket();

	/**
	 * Did the server encounter an error?
	 */
	bool hasError() { return errorFlag; }

	void getSizeAndListen();
	void acceptClient();
	void serveClient();
	void closeSocket();
};

#endif /* SERVER_H_ */
