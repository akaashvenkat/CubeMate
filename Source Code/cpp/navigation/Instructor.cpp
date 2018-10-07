/*
 @author Akaash Venkat
 */

#include <math.h>

#include "Instructor.h"
#include "../constants/Constants.h"
#include "../sqlconn/SQLConn.h"
using namespace std;

Instructor::Instructor(Coordinate m_start, Coordinate m_end, vector< vector<string> > m_floorDetails, vector< vector< vector<int> > > m_cumulativePaths)
{
    floorDetails = m_floorDetails;
    cumulativePaths = m_cumulativePaths;
    start = m_start;
    end = m_end;
}

Instructor::~Instructor()
{
}

vector<string> Instructor::getRouteGuidance()
{
    loadGuidance();
    return routeGuidance;
}

void Instructor::loadGuidance()
{
    SqlConn sqlConn;
    int totalDistance = 0;
    
    routeGuidance.push_back(string("Start At: Building ") + string(1, start.building) + ", Floor " + to_string(start.floor) + ", Room " + start.name);
    routeGuidance.push_back("");
    routeGuidance.push_back("");
    
    for (int i = 0; i < cumulativePaths.size(); i++)
    {
        std::string::size_type sz;
        vector<string> startIntermediate = sqlConn.getIntermediate(char(std::stoi(floorDetails[i][0], &sz)), std::stoi(floorDetails[i][1], &sz), cumulativePaths[i][0]);
        
        if (startIntermediate.size() > 0)
        {
            if (startIntermediate[0] == "Entrance" && char(std::stoi(floorDetails[i][0], &sz)) == 'A')
                routeGuidance.push_back("   Walk over to and enter Building A");
            else if (startIntermediate[0] == "Entrance" && char(std::stoi(floorDetails[i][0], &sz)) == 'B')
                routeGuidance.push_back("   Walk over to and enter Building B");
        }
        
        for (int j = 1; j < cumulativePaths[i].size(); j++)
        {
            string direction = findDirection(cumulativePaths[i][j - 1], cumulativePaths[i][j]);
            int distance = getDistance(cumulativePaths[i][j - 1], cumulativePaths[i][j]);
            totalDistance += distance;
            
            if (sqlConn.isLandmark(char(std::stoi(floorDetails[i][0], &sz)), std::stoi(floorDetails[i][1], &sz), cumulativePaths[i][j - 1]) == true)
            {
                vector<string> landmark = sqlConn.getLandmark(char(std::stoi(floorDetails[i][0], &sz)), std::stoi(floorDetails[i][1], &sz), cumulativePaths[i][j - 1]);
                routeGuidance.push_back(string("   At the ") + landmark[0] + ", proceed " + to_string(distance) + " feet " + direction);
            }
            else
                routeGuidance.push_back(string("   Proceed ") + to_string(distance) + " feet " + direction);
        }
        
        vector<string> endIntermediate = sqlConn.getIntermediate(char(std::stoi(floorDetails[i][0], &sz)), std::stoi(floorDetails[i][1], &sz), cumulativePaths[i][cumulativePaths[i].size() - 1]);
        if (endIntermediate.size() > 0)
        {
            if (endIntermediate[0] == "Entrance" && char(std::stoi(floorDetails[i][0], &sz)) == 'A')
                routeGuidance.push_back("   Exit Building A");
            else if (endIntermediate[0] == "Entrance" && char(std::stoi(floorDetails[i][0], &sz)) == 'B')
                routeGuidance.push_back("   Exit Building B");
            else if ((endIntermediate[0].find("Stairs") != string::npos) && (std::stoi(floorDetails[i][1], &sz) == 2))
                routeGuidance.push_back("   Walk down the stairs to the first floor");
            else if ((endIntermediate[0].find("Stairs") != string::npos) && (std::stoi(floorDetails[i][1], &sz) == 1))
                routeGuidance.push_back("   Walk up the stairs to the second floor");
        }
        routeGuidance.push_back("");
    }
    
    routeGuidance.push_back("");
    routeGuidance.push_back(string("End At: Building ") + string(1, end.building) + ", Floor " + to_string(end.floor) + ", Room " + end.name);
    routeGuidance.push_back("");
    routeGuidance.push_back(string("Total Distance Travelled: ") + to_string(totalDistance) + " Feet");
}

int Instructor::getDistance(vector<int> startCoord, vector<int> endCoord)
{
    return sqrt((startCoord[0] - endCoord[0])*(startCoord[0] - endCoord[0]) + (startCoord[1] - endCoord[1])*(startCoord[1] - endCoord[1]));
}

string Instructor::findDirection(vector<int> startCoord, vector<int> endCoord)
{
    if (endCoord[0] - startCoord[0] > 0)
        return "East";
    else if (endCoord[0] - startCoord[0] < 0)
        return "West";
    else if (endCoord[1] - startCoord[1] > 0)
        return "North";
    else
        return "South";
}
