output: main.o Socket.o tcp_socket.o Http.o Server.o
	g++ main.o Socket.o tcp_socket.o Http.o Server.o -o main && make clean

main.o: main.cpp
	g++ -c  main.cpp

Socket.o: source/Socket.cc
	g++ -c  source/Socket.cc

tcp_socket.o: source/tcp_socket.cc
	g++ -c  source/tcp_socket.cc

Http.o: source/Http.cpp
	g++ -c  source/Http.cpp

Server.o: source/Server.cpp
	g++ -c  source/Server.cpp
clean:
	rm *.o
