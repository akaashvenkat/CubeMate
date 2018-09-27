#																		\
 Project derived from an idea by a group of three members (Jared Huang, Sana Shrikant, and Akaash Venkat) working on Northrop Grumman’s		\
    2018 Intern Hackathon at the Woodland Hills Campus.												\
 Code written by Akaash Venkat.


main: navigation.o socket.o sqlconn.o
	g++ -o main_cpp  -I/usr/local/include -I/Volumes/D/www/c++ -L. -lmysqlcppconn Instructor.o Navigator.o PathManager.o socket.o sqlconn.o main.cpp
	rm *.o

navigation.o:
	g++ -c navigation/Instructor.cpp
	g++ -c navigation/Navigator.cpp
	g++ -c navigation/PathManager.cpp

socket.o: 
	g++ -c socket/socket.cpp

sqlconn.o: 
	g++ -c sqlconn/sqlconn.cpp
