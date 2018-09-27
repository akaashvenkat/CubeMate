/*
 Project derived from an idea by a group of three members (Jared Huang, Sana Shrikant, and Akaash Venkat) working on Northrop Grumman’s
    2018 Intern Hackathon at the Woodland Hills Campus.
 Code written by Akaash Venkat.
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

enum Direction {HORIZONTAL = 0, VERTICAL = 1};
enum Floor {FLR_1 = 1, FLR_2 = 2};
enum Building {BUILD_A = 'A', BUILD_B = 'B'};
enum Mark {FLOOR = 0, PLACARD = 1};
    
struct Coordinate
{
    Building building;
    Floor floor;
        
    string name;
    int xCoord;
    int yCoord;
};
    
struct Landmark
{
    Building building;
    Floor floor;
    Mark mark;
        
    string color;
    int xCoord;
    int yCoord;
};
    
struct Segment
{
    Building building;
    Floor floor;
    Direction direction;
        
    int pt1X;
    int pt1Y;
    int pt2X;
    int pt2Y;
        
    float weight;
};

struct Point
{
    int floor;
    char building;
    int xCoord;
    int yCoord;
};

struct Path
{
    Point from;
    Point to;
};

#endif
