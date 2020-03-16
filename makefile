CXX	=   /usr/local/bin/g++-9
SRC_DIR =   src
INC_DIR =   inc
OUT_DIR	=   OUTPUT
MKDIR	=   mkdir

all: directories lib.o set_1_1 set_1_2 set_1_3 set_1_4 set_1_5
	
directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR} ${OUT_DIR}
	
lib.o: $(SRC_DIR)/lib.cc
	$(CXX) -g -Iinc -o ${OUT_DIR}/lib.o -c $(SRC_DIR)/lib.cc
	
set_1_1: $(SRC_DIR)/set_1_1_lib.cc $(SRC_DIR)/set_1_1_main.cc $(INC_DIR)/lib.h
	$(CXX) -g -Iinc -o ${OUT_DIR}/set_1_1 $(SRC_DIR)/set_1_1_main.cc ${OUT_DIR}/lib.o

set_1_2: $(SRC_DIR)/set_1_2_lib.cc $(SRC_DIR)/set_1_2_main.cc $(INC_DIR)/lib.h
	$(CXX) -g -Iinc -o ${OUT_DIR}/set_1_2 $(SRC_DIR)/set_1_2_main.cc ${OUT_DIR}/lib.o

set_1_3: $(SRC_DIR)/set_1_3_lib.cc $(SRC_DIR)/set_1_3_main.cc $(INC_DIR)/lib.h
	$(CXX) -g -Iinc -o ${OUT_DIR}/set_1_3 $(SRC_DIR)/set_1_3_main.cc ${OUT_DIR}/lib.o

set_1_4: $(SRC_DIR)/set_1_4_main.cc $(INC_DIR)/lib.h
	$(CXX) -g -Iinc -o ${OUT_DIR}/set_1_4 $(SRC_DIR)/set_1_4_main.cc ${OUT_DIR}/lib.o

set_1_5: $(SRC_DIR)/set_1_5_lib.cc $(SRC_DIR)/set_1_5_main.cc $(INC_DIR)/lib.h
	$(CXX) -g -Iinc -o ${OUT_DIR}/set_1_5 $(SRC_DIR)/set_1_5_main.cc ${OUT_DIR}/lib.o


.PHONY : clean
clean:
	-rm -r ${OUT_DIR}