#GNU C/C++ Compiler and linker
GCC = g++
LINK = g++

BIN_DIR = bin
SRC_DIR = src
INC_DIR = inc

MAIN_NAME = maze
MAIN = $(SRC_DIR)/main.cpp
ALT_MAINS = $(SRC_DIR)/unittests.cpp

INC    = -I$(INC_DIR)
FILES  = $(shell echo $(SRC_DIR)/*.cpp)
SOURCE = $(filter-out $(MAIN) $(ALT_MAINS), $(FILES))
OBJS   = $(subst $(SRC_DIR),$(BIN_DIR),$(SOURCE:.cpp=.o))
EXES   = $(MAIN_NAME).exe $(subst $(SRC_DIR)/,,$(ALT_MAINS:.cpp=.exe))

# Compiler flags
CXXFLAGS = -Wall -O3 -std=c++14

# Fill in special libraries needed here
LIBS = -lX11 -lGL -lpthread -lpng -lstdc++fs

.PHONY: clean realclean help .setdebug .tests

all: $(BIN_DIR) main

main: $(BIN_DIR)/main.o $(OBJS)
	$(LINK) $(CXXFLAGS) -o $(MAIN_NAME).exe $^ $(LIBS)

debug: .setdebug all

unittests: .setdebug .tests
.tests: $(BIN_DIR)/unittests.o $(OBJS)
	$(LINK) $(CXXFLAGS) -o unittests.exe $^ $(LIBS)

$(BIN_DIR)/%.o: $(BIN_DIR)
	$(GCC) $(CXXFLAGS) -c -o $@ $(subst $(BIN_DIR),$(SRC_DIR),$(@:.o=.cpp)) $(INC)

clean:
	rm -rf $(BIN_DIR) core $(EXES)

realclean: clean
	rm -f $(MAIN_NAME).zip

zip: clean
	zip -r $(MAIN_NAME).zip Makefile $(SRC_DIR) $(INC_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)

.setdebug:
	$(eval CXXFLAGS = -DDEBUG -g -std=c++14)

help:
	@echo "	make all       - builds the main target"
	@echo "	make           - same as make all"
	@echo "	make unittests - builds the unittests target"
	@echo "	make debug     - make all with -g and -DDEBUG"
	@echo "	make clean     - remove bin/*, core, and executables"
	@echo "	make realclean - cleans and removes .zip"
	@echo "	make zip       - zip the Makefile, ./src, and ./inc"
	@echo "	make help      - this message"
