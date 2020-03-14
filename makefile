CXX=g++
CXXFLAGS=-Iinc

cryptopals:  set_1_1.o set_1_2.o set_1_3.o set_1_4.o base64.o
	$(CXX) -o cryptopals set_1_1.o base64.o


base64.o : inc/lib.h
	$(CXX) -c -Iinc src/base64.cc 

set_1_1.o: src/set_1_1.cc inc/lib.h
	$(CXX) -c -Iinc src/set_1_1.cc 

set_1_2.o: src/set_1_2.cc inc/lib.h
	$(CXX) -c -Iinc src/set_1_2.cc 

set_1_3.o: src/set_1_3.cc inc/lib.h
	$(CXX) -c -Iinc src/set_1_3.cc 

set_1_4.o: src/set_1_4.cc inc/lib.h
	$(CXX) -c -Iinc src/set_1_4.cc 
	
#_set_1_1.o: src/base64.cpp inc/base64.hpp
#	$(CXX) -Iinc src/base64.cpp
#
#set_1_2.o: inc/base64.hpp
#	$(CXX) -Iinc src/fixedXOR.cpp 


	
#main.o: src/main.cpp inc/base64.hpp 
#	$(CXX) -Iinc src/main.cpp

clean: cryptopals set_1_1.o
	rm cryptopals set_1_1.o