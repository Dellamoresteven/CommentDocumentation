make: main.cpp
	g++ --std=c++2a -O3 -Wall -o doc \
				main.cpp \

clean:
	rm -f doc
	rm -f *.cpp