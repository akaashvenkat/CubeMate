/*
 Project derived from an idea by a group of three members (Jared Huang, Sana Shrikant, and Akaash Venkat) working on Northrop Grumman’s
    2018 Intern Hackathon at the Woodland Hills Campus.
 Code written by Akaash Venkat.
 */

#ifndef PATHMANAGER_H
#define PATHMANAGER_H

#include <math.h>
#include <stdio.h>
#include <vector>

#include "../constants/Constants.h"
#include "../sqlconn/SQLConn.h"
using namespace std;

class PathManager
{
public:
    PathManager(Coordinate m_start, Coordinate m_end);
    ~PathManager();
    
    vector<Path> getPaths();
    
private:
    void loadPaths();
    int findCase(Coordinate coord);
    double getDistance(int startX, int startY, int endX, int endY);
    Coordinate start, end;
    int startCase, endCase;
    vector<Path> paths;
};

#endif
