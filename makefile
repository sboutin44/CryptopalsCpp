CXX=g++
CXXFLAGS=-Iinc

cryptopals:  _set_1_1.o set_1_2.o main.o
	$(CXX) -o cryptopals set_1_1.o set_1_2.o main.o

set_1_1.o: src/set_1_1.cpp inc/base64.hpp

_set_1_1.o: src/base64.cpp inc/base64.hpp
	$(CXX) -Iinc src/base64.cpp

set_1_2.o: src/fixedXOR.cpp inc/base64.hpp
	$(CXX) -Iinc src/fixedXOR.cpp 


	
#main.o: src/main.cpp inc/base64.hpp 
#	$(CXX) -Iinc src/main.cpp

