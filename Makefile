make: src/main.cpp src/config.cpp src/createTex.cpp
	g++ --std=c++2a -Wall -lboost_program_options -o doc \
				src/main.cpp \
				src/token.cpp \
				src/config.cpp \
				

clean:
	rm -f doc
	rm -f *.cpp