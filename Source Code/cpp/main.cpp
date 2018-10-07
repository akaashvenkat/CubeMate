/*
 @author Akaash Venkat
 */

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "constants/Constants.h"
#include "navigation/Instructor.h"
#include "navigation/Navigator.h"
#include "navigation/PathManager.h"
#include "socket/Socket.h"
#include "sqlconn/SQLConn.h"

using namespace std;

/*
int main()
{
    Socket socket;
    SqlConn sqlconn;
    
    while (1)
    {
        socket.read();
        int startID, endID;
        if (socket.getValidity() == true)
        {
            startID = socket.getStartID();
            endID = socket.getEndID();
        }
        else
        {
            continue;
        }
        Coordinate start, end;
        start = sqlconn.getStart(startID);
        end = sqlconn.getEnd(endID);
        
        PathManager pathManager(start, end);
        vector<Path> paths = pathManager.getPaths();
        
        vector< vector<string> > floorDetails;
        vector< vector< vector<int> > > cumulativePaths;
        for (int i = 0; i < paths.size(); i++)
        {
            Path p = paths[i];
            Point a = p.from;
            Point b = p.to;
            
            Navigator nav(a.building, a.floor, a.xCoord, a.yCoord, b.xCoord, b.yCoord);
            vector< vector<int> > floorNav = nav.navigate();
            
            vector<string> floorDetail;
            floorDetail.push_back(to_string(a.building));
            floorDetail.push_back(to_string(a.floor));
            
            floorDetails.push_back(floorDetail);
            cumulativePaths.push_back(floorNav);
        }
        Instructor instructor(start, end, floorDetails, cumulativePaths);
        vector<string> guidance = instructor.getRouteGuidance();
        socket.write(guidance);
    }
}
 */

int main()
{
    Socket socket;
    SqlConn sqlconn;
    
    int startID = 23;
    int endID = 44;
    
    Coordinate start, end;
    start = sqlconn.getStart(startID);
    end = sqlconn.getEnd(endID);
        
        PathManager pathManager(start, end);
        vector<Path> paths = pathManager.getPaths();
        
        vector< vector<string> > floorDetails;
        vector< vector< vector<int> > > cumulativePaths;
        for (int i = 0; i < paths.size(); i++)
        {
            Path p = paths[i];
            Point a = p.from;
            Point b = p.to;
            
            Navigator nav(a.building, a.floor, a.xCoord, a.yCoord, b.xCoord, b.yCoord);
            vector< vector<int> > floorNav = nav.navigate();
            
            vector<string> floorDetail;
            floorDetail.push_back(to_string(a.building));
            floorDetail.push_back(to_string(a.floor));
            
            floorDetails.push_back(floorDetail);
            cumulativePaths.push_back(floorNav);
        }
        Instructor instructor(start, end, floorDetails, cumulativePaths);
        vector<string> guidance = instructor.getRouteGuidance();
    
    for (int i = 0; i < guidance.size(); i++)
    {
        cout << guidance[i] << endl;
    }
}
