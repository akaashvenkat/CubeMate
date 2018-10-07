main: navigation.o socket.o sqlconn.o
	g++ -o main_cpp  -I/usr/local/include -I/Volumes/D/www/c++ -L. -lmysqlcppconn Instructor.o Navigator.o PathManager.o socket.o sqlconn.o main.cpp
	rm *.o

navigation.o:
	g++ -c navigation/Instructor.cpp
	g++ -c navigation/Navigator.cpp
	g++ -c navigation/PathManager.cpp

socket.o: 
	g++ -c socket/Socket.cpp

sqlconn.o: 
	g++ -c sqlconn/SQLConn.cpp
