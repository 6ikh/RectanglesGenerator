make: main.o
	g++ main.o -o make	
main.o: main.cpp
	g++ -c main.cpp 	
clean: 
	rm *.o
	rm rectangles.txt
	rm make
debug: make
	gdb ./make

run: make
	./make
