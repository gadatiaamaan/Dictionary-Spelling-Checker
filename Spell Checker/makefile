spellCheck: main.o
	g++ main.o -o spellCheck

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

clean:
	rm -f *.o
	rm -f spellCheck

run: spellCheck
	./spellCheck


