/*
 @author Akaash Venkat
 */

#include "Navigator.h"
#include "../constants/Constants.h"
#include "../sqlconn/SQLConn.h"
using namespace std;

Node::Node(int coordX, int coordY)
{
    xCoord = coordX;
    yCoord = coordY;
    parent = NULL;
    g = 0;
    h = 0;
    f = 0;
}

Node::Node(int coordX, int coordY, Node* parentNode)
{
    xCoord = coordX;
    yCoord = coordY;
    parent = parentNode;
    g = 0;
    h = 0;
    f = 0;
}

Node::~Node()
{
    if (parent != NULL)
        delete parent;
    delete this;
}

bool Node::isEqual(Node* other)
{
    return getCoords() == other->getCoords();
}

vector<int> Node::getCoords()
{
    vector<int> coords;
    coords.push_back(xCoord);
    coords.push_back(yCoord);
    return coords;
}

Node* Node::getParent()
{
    return parent;
}

int Node::getG()
{
    return g;
}

int Node::getH()
{
    return h;
}

int Node::getF()
{
    return f;
}

void Node::setG(int val)
{
    g = val;
}

void Node::setH(int val)
{
    h = val;
}

void Node::setF(int val)
{
    f = val;
}



Navigator::Navigator(char m_building, int m_floor, int startX, int startY, int endX, int endY)
{
    startNode = new Node(startX, startY);
    endNode = new Node(endX, endY);
    openList.push_back(startNode);
    
    building = m_building;
    floor = m_floor;
}

Navigator::~Navigator()
{
}

vector< vector<int> > Navigator::navigate()
{
    SqlConn sqlConnector;
    while (openList.size() > 0)
    {
        Node* currNode = openList[0];
        int currIndex = 0;
        
        for (int i = 0; i < openList.size(); i++)
        {
            if (openList[i]->getF() < currNode->getF())
            {
                currNode = openList[i];
                currIndex = i;
            }
        }
        
        openList.erase(find(openList.begin(), openList.end(), currNode));
        closedList.push_back(currNode);
        
        if (currNode->isEqual(endNode))
        {
            vector< vector<int> > revPath;
            vector< vector<int> > path;
            Node* c = currNode;
            
            while (c != NULL)
            {
                revPath.push_back(c->getCoords());
                c = c->getParent();
            }
            
            for (int i = 0; i < revPath.size(); i++)
                path.push_back(revPath[revPath.size() - i - 1]);
            
            vector< vector<int> > refinedPath = refinePath(path);
            return refinedPath;
        }
        
        vector<Node*> children;
        vector< vector<int> > neighbors = sqlConnector.getNeighbors(building, floor, currNode->getCoords());
        
        for (int i = 0; i < neighbors.size(); i++)
        {
            vector<int> neighbor = neighbors[i];
            Node* newNode = new Node(neighbor[0], neighbor[1], currNode);
            children.push_back(newNode);
        }
        
        for (int j = 0; j < children.size(); j++)
        {
            for (int k = 0; k < closedList.size(); k++)
            {
                if (children[j]->isEqual(closedList[k]))
                    continue;
            }
            
            children[j]->setG(currNode->getG() + 1);
            children[j]->setH((children[j]->getCoords()[0] - endNode->getCoords()[0]) * (children[j]->getCoords()[0] - endNode->getCoords()[0]) + (children[j]->getCoords()[1] - endNode->getCoords()[1]) * (children[j]->getCoords()[1] - endNode->getCoords()[1]));
            children[j]->setF(children[j]->getG() + children[j]->getH());
            
            for (int k = 0; k < openList.size(); k++)
            {
                if (children[j]->isEqual(openList[k]) && children[j]->getG() > openList[k]->getG())
                    continue;
            }
            openList.push_back(children[j]);
        }
    }
}

vector< vector<int> > Navigator::refinePath(vector< vector<int> > initialPath)
{
    SqlConn sqlConnector;
    vector< vector<int> > refinedPath;
    refinedPath.push_back(initialPath[0]);
    
    for (int i = 1; i < initialPath.size() - 1; i++)
    {
        if (((initialPath[i][0] == initialPath[i - 1][0]) && (initialPath[i][0] == initialPath[i + 1][0])) || ((initialPath[i][1] == initialPath[i - 1][1]) && (initialPath[i][1] == initialPath[i + 1][1])))
        {
            if (sqlConnector.isLandmark(building, floor, initialPath[i]) == true)
                refinedPath.push_back(initialPath[i]);
        }
        else
            refinedPath.push_back(initialPath[i]);
    }
    
    refinedPath.push_back(initialPath[initialPath.size() - 1]);
    return refinedPath;
}
