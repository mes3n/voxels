# Variables to control Makefile operation

CC = g++
MYDIR = .
SRC_DIR = $(MYDIR)/src
OBJ_DIR = $(MYDIR)/obj
CFLAGS = -Wall -g
LDFLAGS = -Wall -g -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLEW# link these

# create list of object files from source files but replace ".cpp" and "src"
OBJ_SUBDIR = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(wildcard $(SRC_DIR)/*/ $(SRC_DIR)/*/*/))# two levels of subdirectories
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp))


main: $(OBJ_FILES)
	$(CC) -o bin/$@ $^ $(LDFLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

all: clean main

run: main
	@echo ""
	exec $(MYDIR)/bin/main


header: HEADER_NAME = $(subst .,_,$(shell echo $(lastword $(subst /, ,$(FILE))) | tr '[:lower:]' '[:upper:]'))
		CPP_FILE = $(subst .hpp,.cpp,$(FILE))

header: 
ifeq ("$(wildcard $(FILE))", "")
	@touch $(FILE) 
	@touch $(CPP_FILE)
	@echo '#ifndef $(HEADER_NAME)' >> $(FILE)
	@echo '#define $(HEADER_NAME)' >> $(FILE)
	@echo '' >> $(FILE)
	@echo '' >> $(FILE)
	@echo '' >> $(FILE)
	@echo '#endif  // $(HEADER_NAME)' >> $(FILE)

	@echo "Created c++ header file ($(FILE)) with header guard ($(HEADER_NAME)) and source file ($(CPP_FILE))."
	git add $(FILE) $(CPP_FILE)

else
	@echo "Header file already exists."

endif


.PHONY: clean
clean:
	rm -rf bin obj
	mkdir bin obj $(OBJ_SUBDIR)
