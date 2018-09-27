/*
 Project derived from an idea by a group of three members (Jared Huang, Sana Shrikant, and Akaash Venkat) working on Northrop Grumman’s
    2018 Intern Hackathon at the Woodland Hills Campus.
 Code written by Akaash Venkat.
 */

#ifndef SQLCONN_H
#define SQLCONN_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "mysql_cppconn/cppconn/driver.h"
#include "mysql_cppconn/cppconn/exception.h"
#include "mysql_cppconn/cppconn/prepared_statement.h"
#include "mysql_cppconn/cppconn/resultset.h"
#include "mysql_cppconn/cppconn/statement.h"
#include "mysql_cppconn/mysql_connection.h"

#include "../constants/Constants.h"
using namespace std;

class SqlConn
{
    
public:
    SqlConn();
    ~SqlConn();

    Coordinate getStart(int sID);
    Coordinate getEnd(int eID);
    vector<Landmark> getLandmarks();
    vector<Coordinate> getIntermediates();
    vector<Segment> getSegments();
    vector< vector<int> > getNeighbors(char building, int floor, vector<int> coord);
    vector<string> getIntermediate(char building, int floor, vector<int> coord);
    vector<string> getLandmark(char building, int floor, vector<int> coord);
    bool isLandmark(char building, int floor, vector<int> coord);
    
private:
    sql::Driver *driver;
    sql::Connection *con;
    
    vector<Landmark> landmarkList;
    vector<Coordinate> intermediateList;
    vector<Segment> segmentList;
    
    void loadLandmarks();
    void loadIntermediates();
    void loadSegments();
};

#endif
