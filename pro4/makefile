calculator:Function.o main.o define.h
	g++ define.h main.o Function.o -o calculator
main.o:main.cpp
	g++ -g -c -fno-stack-protector main.cpp -o main.o
Function.o:Function.cpp
	g++ -g -c -fno-stack-protector Function.cpp -o Function.o
clean:
	rm *.o
	rm calculator
