/*
 * Server.cpp
 *
 *  Created on: Jan 14, 2018
 *      Author: scud
 */

#include "Server.h"

Server::Server(int port) {
	portNum = port;
	errorFlag = false;
	cout << "Server init..." << endl;

	//Create the socket
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverfd < 0) {
		errorFlag = true;
        cout << "ERROR creating socket" << endl;
        exit(-1);
    }

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(portNum);

	int yes = 1;
	if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
	    perror("setsockopt");
	    exit(1);
	}
}

Server::~Server() {
	// TODO cleanup stuff
}

void Server::bindSocket() {

	 if ((bind(serverfd, (struct sockaddr*) &server_addr, sizeof(server_addr)))
	         < 0) {
	 cout << "- Error binding connection, the socket has already been established..."
	      << endl;
	     exit(-1);
	 }

}

void Server::getSizeAndListen() {

	 size = sizeof(server_addr);
	 cout << "Listening for clients" << endl;

	 listen(serverfd, 1);
}

void Server::acceptClient() {

	 clientfd = accept(serverfd, (struct sockaddr *) &server_addr, &size);

}

void Server::serveClient() {

	 char buffer[bufferSize];
	 //while (clientfd > 0) {

	 //TODO How shall we organize this to server WRQs and such?
	 recv(clientfd, buffer, bufferSize, 0);
	 cout << buffer << endl;
	 //}
}

void Server::closeSocket() {
	 close(serverfd);
}
