CXX	=   /usr/local/bin/g++-9
SRC_DIR =   src
INC_DIR =   inc
OUT_DIR	=   OUTPUT
MKDIR	=   mkdir


#cryptopals:  set_1_1.o set_1_2.o set_1_3.o set_1_4.o \
#	     base64.o 
#	$(CXX) -o cryptopals set_1_1.o base64.o
all: lib.o directories set_1_1 set_1_2 set_1_3 set_1_4 set_1_5
	
directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR} ${OUT_DIR}
	
#base64.o : src/base64.cc inc/lib.h
#	$(CXX) -c -Iinc src/base64.cc

lib.o:
	$(CXX) -Iinc -c $(SRC_DIR)/lib.cc
	
set_1_1: $(SRC_DIR)/set_1_1_lib.cc $(SRC_DIR)/set_1_1_main.cc $(INC_DIR)/lib.h
	$(CXX) -Iinc -o ${OUT_DIR}/set_1_1 $(SRC_DIR)/set_1_1_lib.cc $(SRC_DIR)/set_1_1_main.cc

set_1_2: $(SRC_DIR)/set_1_2_lib.cc $(SRC_DIR)/set_1_2_main.cc $(INC_DIR)/lib.h
	$(CXX) -Iinc -o ${OUT_DIR}/set_1_2 $(SRC_DIR)/set_1_2_lib.cc $(SRC_DIR)/set_1_2_main.cc

set_1_3: $(SRC_DIR)/set_1_3_lib.cc $(SRC_DIR)/set_1_3_main.cc $(INC_DIR)/lib.h
	$(CXX) -Iinc -o ${OUT_DIR}/set_1_3 $(SRC_DIR)/set_1_3_main.cc lib.o #$(SRC_DIR)/set_1_2_lib.cc

set_1_4: $(SRC_DIR)/set_1_4_main.cc $(INC_DIR)/lib.h
	$(CXX) -Iinc -o ${OUT_DIR}/set_1_4 $(SRC_DIR)/set_1_4_main.cc lib.o

set_1_5: $(SRC_DIR)/set_1_5_lib.cc $(SRC_DIR)/set_1_5_main.cc $(INC_DIR)/lib.h
	$(CXX) -g -Iinc -o ${OUT_DIR}/set_1_5 $(SRC_DIR)/set_1_5_main.cc lib.o




#
#set_1_3: $(SRC_DIR)/set_1_3.cc $(INC_DIR)/lib.h set_1_2.o
#	$(CXX) -Iinc -o ${OUT_DIR}/set_1_3 $(SRC_DIR)/set_1_3.cc set_1_2.o
#
#set_1_4: base64.o $(SRC_DIR)/set_1_4.cc $(INC_DIR)/lib.h
#	$(CXX) -Iinc -o ${OUT_DIR}/set_1_4 $(SRC_DIR)/set_1_4.cc base64.o

#set_1_5: base64.o $(SRC_DIR)/set_1_5.cc $(INC_DIR)/lib.h
#	$(CXX) -Iinc -o ${OUT_DIR}/set_1_5 $(SRC_DIR)/set_1_5.cc base64.o

#set_1_2.o: base64.o $(SRC_DIR)/set_1_2.cc
#	$(CXX) -Iinc -c $(SRC_DIR)/set_1_2.cc base64.o
#	
#set_1_3: base64.o set_1_3.o
#	$(CXX) -o set_1_3 set_1_3.o base64.o
#
#set_1_4: base64.o set_1_4.o
#	$(CXX) -o set_1_4 set_1_4.o base64.o


#set_1_1.o: base64.o src/set_1_1.cc inc/lib.h
#	$(CXX) -c -Iinc src/set_1_1.cc
#
#set_1_2.o: src/set_1_2.cc inc/lib.h
#	$(CXX) -c -Iinc src/set_1_2.cc 
#
#set_1_3.o: src/set_1_3.cc inc/lib.h
#	$(CXX) -c -Iinc src/set_1_3.cc 
#
#set_1_4.o: src/set_1_4.cc inc/lib.h
#	$(CXX) -c -Iinc src/set_1_4.cc 
	
#set_1_5.o: src/set_1_5.cc inc/lib.h
#	$(CXX) -g -Iinc src/set_1_5.cc
#	
.PHONY : clean
clean:
	-rm -r ${OUT_DIR} base64.o