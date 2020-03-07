make: main.cpp config.cpp createTex.cpp
	g++ --std=c++2a -Wall -lboost_program_options -o doc \
				main.cpp \
				token.cpp \
				config.cpp \
				

clean:
	rm -f doc
	rm -f *.cpp