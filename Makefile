make: main.cpp
	g++ --std=c++2a -O3 -Wall -o doc \
				main.cpp \
				config.cpp \
				createTex.cpp \

clean:
	rm -f doc
	rm -f *.cpp