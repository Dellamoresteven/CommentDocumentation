make: main.cpp config.cpp createTex.cpp
	g++ --std=c++2a -Wall -o doc \
				main.cpp \
				config.cpp \
				

clean:
	rm -f doc
	rm -f *.cpp