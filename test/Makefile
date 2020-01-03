
EXEC_PATH=./build/
SRC_PATH=../src/
LTYPES_PATH=./ltypes/
EXT=.exe

all: before_test

before_test:
	mkdir -p $(EXEC_PATH)

ltypes_test: 
	gcc -o $(EXEC_PATH)/ltypes_test_1$(EXT) $(LTYPES_PATH)/ltypes_test_1.c $(SRC_PATH)/lstring.c
    
ltypes_test_1:
	$(EXEC_PATH)/ltypes_test_1$(EXT)