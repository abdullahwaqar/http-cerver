output: main.o Socket.o
	g++ main.o Socket.o -o main && make clean

main.o: main.cpp
	g++ -c  main.cpp

Socket.o: source/Socket.cc include/Socket.h
	g++ -c  source/Socket.cc

clean:
	rm *.o