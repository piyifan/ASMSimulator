all : asm.exe
general.o: general.h general.cpp
	g++ -c general.cpp -o general.o
register.o: register.cpp register.h general.h
	g++ -c register.cpp -o register.o
label.o: label.h label.cpp
	g++ -c label.cpp -o label.o
command.o: command.h command.cpp register.h general.h label.h
	g++ -c command.cpp -o command.o
asm.o: asm.h asm.cpp command.h register.h general.h label.h
	g++ -c asm.cpp -o asm.o
main.o: main.cpp asm.h
	g++ -c main.cpp -o main.o
asm.exe: main.o asm.o command.o label.o register.o general.o
	g++ main.o asm.o command.o label.o general.o register.o -o asm.exe