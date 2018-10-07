/*
 @author Akaash Venkat
 */

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "../constants/Constants.h"
#include "../sqlconn/SQLConn.h"
using namespace std;

class Node
{
public:
    Node(int coordX, int coordY);
    Node(int coordX, int coordY, Node* parentNode);
    ~Node();
    
    bool isEqual(Node* other);
    vector<int> getCoords();
    Node* getParent();
    
    int getG();     void setG(int val);
    int getH();     void setH(int val);
    int getF();     void setF(int val);
    
private:
    Node* parent;
    int xCoord, yCoord;
    int g, h, f;
};



class Navigator
{
public:
    Navigator(char m_building, int m_floor, int startX, int startY, int endX, int endY);
    ~Navigator();
    vector< vector<int> > navigate();
    
private:
    vector< vector<int> > refinePath(vector< vector<int> > initialPath);
    
    Node* startNode;
    Node* endNode;
    vector<Node*> openList, closedList;
    char building;
    int floor;
};

#endif
