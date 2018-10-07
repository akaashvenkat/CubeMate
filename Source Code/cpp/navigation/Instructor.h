/*
 @author Akaash Venkat
 */

#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <math.h>

#include "../constants/Constants.h"
#include "../sqlconn/SQLConn.h"
using namespace std;

class Instructor
{
public:
    Instructor(Coordinate m_start, Coordinate m_end, vector< vector <string> > m_floorDetails, vector< vector< vector<int> > > m_cumulativePaths);
    ~Instructor();
    vector<string> getRouteGuidance();
    
private:
    int getDistance(vector<int> startCoord, vector<int> endCoord);
    string findDirection(vector<int> startCoord, vector<int> endCoord);
    void loadGuidance();
    
    Coordinate start, end;
    vector<string> routeGuidance;
    vector< vector<string> > floorDetails;
    vector< vector< vector<int> > > cumulativePaths;
};

#endif
