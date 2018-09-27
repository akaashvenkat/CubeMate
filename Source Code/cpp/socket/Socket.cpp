/*
 Project derived from an idea by a group of three members (Jared Huang, Sana Shrikant, and Akaash Venkat) working on Northrop Grumman’s
    2018 Intern Hackathon at the Woodland Hills Campus.
 Code written by Akaash Venkat.
 */

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

#include "Socket.h"
using namespace std;
#define SOCKET_PATH "/tmp/server.sock"
#define OUT_FILE "../navigation.txt"

Socket::Socket()
{
    signal(SIGINT, sigCall);
    signal(SIGTERM, sigCall);
    signal(SIGKILL, sigCall);
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);
    
    server = socket(PF_UNIX, SOCK_STREAM, 0);
    if (!server)
    {
        perror("socket");
        exit(-1);
    }
    if (bind(server, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(-1);
    }
    if (listen(server, 0) < 0)
    {
        perror("listen");
        exit(-1);
    }
    clientlen = sizeof(client_addr);
    buflen = 1024;
    buf = new char[buflen+1];
}

Socket::~Socket()
{
    close(server);
    unlink(SOCKET_PATH);
}

void Socket::read()
{
    client = accept(server, (struct sockaddr *)&client_addr, &clientlen);
    memset(buf, 0, buflen);
    nread = recv(client, buf, buflen, 0);
    
    string::size_type sz;
    istringstream iss(buf);
    int i = 0;
    int arr[2];
    for (buf; iss >> buf; i++)
    {
        if (i == 2)
        {
            break;
        }
        arr[i] = stoi(buf,&sz);
    }

    startID = arr[0];
    endID = arr[1];
    
    if (strcmp(buf, "99") == 0)
    {
        valid = true;
    }
    else
    {
        valid = false;
    }
}

void Socket::write(vector<string> instructions)
{
    if (appendFile(instructions) == true)
    {
        send(client, buf, 2, 0);
    }
    close(client);
}

int Socket::getStartID() { return startID; }
int Socket::getEndID() { return endID; }
bool Socket::getValidity() { return valid; }

void Socket::sigCall(int sig)
{
    unlink(SOCKET_PATH);
    exit(0);
}

bool Socket::appendFile(vector<string> instructions)
{
    if (instructions.size() == 0)
    {
        return false;
    }
    
    ofstream outfile;
    outfile.open(OUT_FILE);
    for(size_t i = 0; i < instructions.size(); i++)
    {
        outfile << instructions.at(i) << endl;
    }
    return true;
}
