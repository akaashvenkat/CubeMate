/*
 Project derived from an idea by a group of three members (Jared Huang, Sana Shrikant, and Akaash Venkat) working on Northrop Grumman’s
    2018 Intern Hackathon at the Woodland Hills Campus.
 Code written by Akaash Venkat.
 */

#include <math.h>
#include <stdio.h>
#include <vector>

#include "PathManager.h"
#include "../constants/Constants.h"
#include "../sqlconn/SQLConn.h"
using namespace std;

PathManager::PathManager(Coordinate m_start, Coordinate m_end)
{
    start = m_start;
    end = m_end;
}

PathManager::~PathManager()
{
}

vector<Path> PathManager::getPaths()
{
    loadPaths();
    return paths;
}

void PathManager::loadPaths()
{
    startCase = findCase(start);
    endCase = findCase(end);
    
    if (startCase == endCase)
    {
        Point point1, point2;
        Path path1;
        
        point1.floor = start.floor;
        point1.building = start.building;
        point1.xCoord = start.xCoord;
        point1.yCoord = start.yCoord;
        point2.floor = end.floor;
        point2.building = end.building;
        point2.xCoord = end.xCoord;
        point2.yCoord = end.yCoord;
        path1.from = point1;
        path1.to = point2;
        paths.push_back(path1);
    }
    else if ((startCase == 1 && endCase == 2) || (startCase == 2 && endCase == 1))
    {
        Point point1, point2, point3, point4;
        Path path1, path2;
        
        point1.floor = start.floor;
        point1.building = start.building;
        point1.xCoord = start.xCoord;
        point1.yCoord = start.yCoord;
        
        if (startCase == 1)
        {
            if (getDistance(start.xCoord, start.yCoord, 9, 5) <= getDistance(start.xCoord, start.yCoord, 40, 43))
            {
                point2.xCoord = 9;
                point2.yCoord = 5;
                point3.xCoord = 9;
                point3.yCoord = 3;
            }
            else
            {
                point2.xCoord = 40;
                point2.yCoord = 43;
                point3.xCoord = 40;
                point3.yCoord = 40;
            }
        }
        else
        {
            if (getDistance(start.xCoord, start.yCoord, 9, 3) <= getDistance(start.xCoord, start.yCoord, 40, 40))
            {
                point2.xCoord = 9;
                point2.yCoord = 3;
                point3.xCoord = 9;
                point3.yCoord = 5;
            }
            else
            {
                point2.xCoord = 40;
                point2.yCoord = 40;
                point3.xCoord = 40;
                point3.yCoord = 43;
            }
        }
        
        point2.floor = start.floor;
        point2.building = start.building;
        point3.floor = end.floor;
        point3.building = end.building;
        
        point4.floor = end.floor;
        point4.building = end.building;
        point4.xCoord = end.xCoord;
        point4.yCoord = end.yCoord;
        path1.from = point1;
        path1.to = point2;
        path2.from = point3;
        path2.to = point4;
        paths.push_back(path1);
        paths.push_back(path2);
    }
    else if (startCase == 3)
    {
        Point point1, point2;
        Path path1;
        
        point1.floor = start.floor;
        point1.building = start.building;
        point1.xCoord = start.xCoord;
        point1.yCoord = start.yCoord;
        point2.floor = start.floor;
        point2.building = start.building;
        point2.xCoord = 5;
        point2.yCoord = 10;
        path1.from = point1;
        path1.to = point2;
        paths.push_back(path1);
        
        if (endCase == 1)
        {
            Point point3, point4;
            Path path2;
            
            point3.floor = end.floor;
            point3.building = end.building;
            point3.xCoord = 5;
            point3.yCoord = 4;
            point4.floor = end.floor;
            point4.building = end.building;
            point4.xCoord = end.xCoord;
            point4.yCoord = end.yCoord;
            path2.from = point3;
            path2.to = point4;
            paths.push_back(path2);
        }
        else
        {
            Point point3, point4, point5, point6;
            Path path2, path3;
            
            point3.floor = 1;
            point3.building = 'A';
            point3.xCoord = 5;
            point3.yCoord = 4;
            point4.floor = 1;
            point4.building = 'A';
            point4.xCoord = 9;
            point4.yCoord = 5;
            path2.from = point3;
            path2.to = point4;
            paths.push_back(path2);
            
            point5.floor = end.floor;
            point5.building = end.building;
            point5.xCoord = 9;
            point5.yCoord = 3;
            point6.floor = end.floor;
            point6.building = end.building;
            point6.xCoord = end.xCoord;
            point6.yCoord = end.yCoord;
            path3.from = point5;
            path3.to = point6;
            paths.push_back(path3);
        }
    }
    else
    {
        if (startCase == 1)
        {
            Point point1, point2;
            Path path1;
            
            point1.floor = start.floor;
            point1.building = start.building;
            point1.xCoord = start.xCoord;
            point1.yCoord = start.yCoord;
            point2.floor = start.floor;
            point2.building = start.building;
            point2.xCoord = 5;
            point2.yCoord = 4;
            path1.from = point1;
            path1.to = point2;
            paths.push_back(path1);
        }
        else
        {
            Point point1, point2, point3, point4;
            Path path1, path2;
            
            point1.floor = start.floor;
            point1.building = start.building;
            point1.xCoord = start.xCoord;
            point1.yCoord = start.yCoord;
            point2.floor = start.floor;
            point2.building = start.building;
            point2.xCoord = 9;
            point2.yCoord = 3;
            path1.from = point1;
            path1.to = point2;
            paths.push_back(path1);
            
            point3.floor = 1;
            point3.building = 'A';
            point3.xCoord = 9;
            point3.yCoord = 5;
            point4.floor = 1;
            point4.building = 'A';
            point4.xCoord = 5;
            point4.yCoord = 4;
            path2.from = point3;
            path2.to = point4;
            paths.push_back(path2);
        }
        
        Point pointY, pointZ;
        Path pathLast;
        
        pointY.floor = end.floor;
        pointY.building = end.building;
        pointY.xCoord = 5;
        pointY.yCoord = 10;
        pointZ.floor = end.floor;
        pointZ.building = end.building;
        pointZ.xCoord = end.xCoord;
        pointZ.yCoord = end.yCoord;
        pathLast.from = pointY;
        pathLast.to = pointZ;
        paths.push_back(pathLast);
    }
}

int PathManager::findCase(Coordinate coord)
{
    int posCase = 0;
    if (coord.building == 'A')
    {
        if (coord.floor == 1)
            posCase = 1;
        else
            posCase = 2;
    }
    else
        posCase = 3;
    
    return posCase;
}

double PathManager::getDistance(int startX, int startY, int endX, int endY)
{
    return sqrt((startX - endX)*(startX - endX) + (startY - endY)*(startY - endY));
}
