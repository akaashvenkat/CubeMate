/*
 @author Akaash Venkat
 */

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

#include "SQLConn.h"
#include "../constants/Constants.h"
using namespace std;

SqlConn::SqlConn()
{
    try
    {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "pass");
        con->setSchema("iTurn");
    }
    catch (sql::SQLException &e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

SqlConn::~SqlConn()
{
    delete con;
}

Coordinate SqlConn::getStart(int sID)
{
    Coordinate start;
    try
    {
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;
        
        pstmt = con->prepareStatement("SELECT Building, Floor, Name, xCoord, yCoord FROM Regions WHERE ID = " + to_string(sID));
        res = pstmt->executeQuery();
        res->beforeFirst();

        while (res->next())
        {
            if (res->getString("Building") == "A")
                start.building = BUILD_A;
            else
                start.building = BUILD_B;
            
            if (res->getString("Floor") == "1")
                start.floor = FLR_1;
            else
                start.floor = FLR_2;
            
            start.name = res->getString("Name");
            start.xCoord = res->getInt("xCoord");
            start.yCoord = res->getInt("yCoord");
        }
        
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    
    return start;
}

Coordinate SqlConn::getEnd(int eID)
{
    Coordinate end;
    try
    {
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;
        
        pstmt = con->prepareStatement("SELECT Building, Floor, Name, xCoord, yCoord FROM Regions WHERE ID = " + to_string(eID));
        res = pstmt->executeQuery();
        res->beforeFirst();
        
        while (res->next())
        {
            if (res->getString("Building") == "A")
                end.building = BUILD_A;
            else
                end.building = BUILD_B;
            
            if (res->getString("Floor") == "1")
                end.floor = FLR_1;
            else
                end.floor = FLR_2;
            
            end.name = res->getString("Name");
            end.xCoord = res->getInt("xCoord");
            end.yCoord = res->getInt("yCoord");
        }
        
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    
    return end;
}

vector< vector<int> > SqlConn::getNeighbors(char building, int floor, vector<int> coord)
{
    vector< vector<int> > neighborsList;
    try
    {
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;
        
        string query = string("SELECT pt1X, pt1Y FROM Segments WHERE Building = '") + building + "' AND Floor = " + to_string(floor) + " AND pt2X = " + to_string(coord[0]) + " AND pt2Y = " + to_string(coord[1]);
        pstmt = con->prepareStatement(query);
        res = pstmt->executeQuery();
        res->beforeFirst();
        
        while (res->next())
        {
            vector<int> neighbor;
            neighbor.push_back(res->getInt("pt1X"));
            neighbor.push_back(res->getInt("pt1Y"));
            
            neighborsList.push_back(neighbor);
        }

        query = string("SELECT pt2X, pt2Y FROM Segments WHERE Building = '") + building + "' AND Floor = " + to_string(floor) + " AND pt1X = " + to_string(coord[0]) + " AND pt1Y = " + to_string(coord[1]);
        pstmt = con->prepareStatement(query);
        res = pstmt->executeQuery();
        res->beforeFirst();
        
        while (res->next())
        {
            vector<int> neighbor;
            neighbor.push_back(res->getInt("pt2X"));
            neighbor.push_back(res->getInt("pt2Y"));
            
            neighborsList.push_back(neighbor);
        }
        
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    
    return neighborsList;
}

vector<string> SqlConn::getIntermediate(char building, int floor, vector<int> coord)
{
    vector<string> intermediates;
    try
    {
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;
        
        string query = string("SELECT Name FROM Intermediates WHERE Building = '") + building + "' AND Floor = " + to_string(floor) + " AND xCoord = " + to_string(coord[0]) + " AND yCoord = " + to_string(coord[1]);
        pstmt = con->prepareStatement(query);
        res = pstmt->executeQuery();
        res->beforeFirst();
        
        while (res->next())
            intermediates.push_back(res->getString("Name"));
        
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    
    return intermediates;
}

vector<string> SqlConn::getLandmark(char building, int floor, vector<int> coord)
{
    vector<string> landmarks;
    try
    {
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;
        
        string query = string("SELECT Type, Color FROM Landmarks WHERE Building = '") + building + "' AND Floor = " + to_string(floor) + " AND xCoord = " + to_string(coord[0]) + " AND yCoord = " + to_string(coord[1]);
        pstmt = con->prepareStatement(query);
        res = pstmt->executeQuery();
        res->beforeFirst();
        while (res->next())
        {
            if (res->getString("Type") == "floor")
            {
                string landmark = res->getString("Color") + " floor marker";
                landmarks.push_back(landmark);
            }
            else
            {
                string landmark = res->getString("Color") + res->getString("Type");
                landmarks.push_back(landmark);
            }
        }
        
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    
    return landmarks;
}

bool SqlConn::isLandmark(char building, int floor, vector<int> coord)
{
    vector<string> landmarks;
    try
    {
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;
        
        string query = string("SELECT Type FROM Landmarks WHERE Building = '") + building + "' AND Floor = " + to_string(floor) + " AND xCoord = " + to_string(coord[0]) + " AND yCoord = " + to_string(coord[1]);
        pstmt = con->prepareStatement(query);
        res = pstmt->executeQuery();
        res->beforeFirst();
        
        while (res->next())
            landmarks.push_back(res->getString("Type"));
        
        delete res;
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    
    if (landmarks.size() > 0)
        return true;
    else
        return false;
}
