
EXEC_PATH=./build/
SRC_PATH=../src/
LTYPES_TEST_PATH=./ltypes/
LBOOL_TEST_PATH=./lbool/
EXT=.exe

all: compile line run

compile: ltypes_test lbool_test
run: run_ltypes_test run_lbool_test

ltypes_test: 
	gcc -o $(EXEC_PATH)/ltypes_test_1$(EXT) $(LTYPES_TEST_PATH)/ltypes_test_1.c
    
run_ltypes_test:
	$(EXEC_PATH)/ltypes_test_1$(EXT)

lbool_test: 
	gcc -o $(EXEC_PATH)/lbool_test_1$(EXT) $(LBOOL_TEST_PATH)/lbool_test_1.c
    
run_lbool_test:
	$(EXEC_PATH)/lbool_test_1$(EXT)
	
line: 
	@echo =====================================
	@echo =====================================