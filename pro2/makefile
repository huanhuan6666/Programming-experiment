myshell:Function.o main.o define.h
	g++ define.h main.o Function.o -o myshell
main.o:
	g++ -g -c main.cpp -o main.o
Function.o:Function.cpp
	g++ -g -c Function.cpp -o Function.o
clean:
	rm *.o
	rm myshell
