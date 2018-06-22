output: main.o Socket.o tcp_socket.o Http.o Server.o
	g++ main.o Socket.o tcp_socket.o Http.o Server.o -o main && make clean

main.o: main.cpp
	g++ -c  main.cpp

Socket.o: source/Socket.cc include/Socket.h
	g++ -c  source/Socket.cc

tcp_socket.o: source/tcp_socket.cc include/tcp_socket.h
	g++ -c  source/tcp_socket.cc

Http.o: source/Http.cpp include/Http.h
	g++ -c  source/Http.cpp

Server.o: source/Server.cpp include/Server.h
	g++ -c  source/Server.cpp
clean:
	rm *.o