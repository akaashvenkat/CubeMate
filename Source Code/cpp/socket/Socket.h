/*
 Project derived from an idea by a group of three members (Jared Huang, Sana Shrikant, and Akaash Venkat) working on Northrop Grumman’s
    2018 Intern Hackathon at the Woodland Hills Campus.
 Code written by Akaash Venkat.
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <vector>

using namespace std;
#define SOCKET_PATH "/tmp/server.sock"
#define OUT_FILE "../navigation.txt"

class Socket
{
public:
    Socket();
    ~Socket();
    
    void read();
    void write(vector<string> instructions);
    int getStartID();
    int getEndID();
    bool getValidity();
    
private:
    struct sockaddr_un server_addr, client_addr;
    socklen_t clientlen;
    unsigned int client;
    int server, nread, buflen;
    char *buf;
    
    int startID, endID;
    bool valid;
    
    static void sigCall(int sig);
    bool appendFile(vector<string> instructions);
};

#endif
