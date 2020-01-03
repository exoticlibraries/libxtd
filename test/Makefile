
EXEC_PATH=./build/
SRC_PATH=../src/
LTYPES_TEST_PATH=./ltypes/
LBOOL_TEST_PATH=./lbool/
LSTRING_TEST_PATH=./lstring/
EXT=

all: compile line run

compile: ltypes_test lbool_test lstring_test
run: run_ltypes_test run_lbool_test run_lstring_test

ltypes_test: 
	gcc -o $(EXEC_PATH)/ltypes_test_1$(EXT) $(LTYPES_TEST_PATH)/ltypes_test_1.c
    
run_ltypes_test:
	$(EXEC_PATH)/ltypes_test_1$(EXT)

lbool_test: 
	gcc -o $(EXEC_PATH)/lbool_test_1$(EXT) $(LBOOL_TEST_PATH)/lbool_test_1.c
    
run_lbool_test:
	$(EXEC_PATH)/lbool_test_1$(EXT)

lstring_test: 
	gcc -o $(EXEC_PATH)/lstring_test_1$(EXT) $(LSTRING_TEST_PATH)/lstring_test_1.c
	gcc -o $(EXEC_PATH)/lstring_test_2$(EXT) $(LSTRING_TEST_PATH)/lstring_test_2.c
	gcc -o $(EXEC_PATH)/lstring_test_3$(EXT) $(LSTRING_TEST_PATH)/lstring_test_3.c
	gcc -o $(EXEC_PATH)/lstring_test_4$(EXT) $(LSTRING_TEST_PATH)/lstring_test_4.c
	gcc -o $(EXEC_PATH)/lstring_test_5$(EXT) $(LSTRING_TEST_PATH)/lstring_test_5.c
	gcc -o $(EXEC_PATH)/lstring_test_6$(EXT) $(LSTRING_TEST_PATH)/lstring_test_6.c
	gcc -o $(EXEC_PATH)/lstring_test_utf8$(EXT) $(LSTRING_TEST_PATH)/lstring_test_utf8.c
    
run_lstring_test:
	$(EXEC_PATH)/lstring_test_1$(EXT)
	$(EXEC_PATH)/lstring_test_2$(EXT)
	$(EXEC_PATH)/lstring_test_3$(EXT)
	$(EXEC_PATH)/lstring_test_4$(EXT)
	$(EXEC_PATH)/lstring_test_5$(EXT)
	$(EXEC_PATH)/lstring_test_6$(EXT)
	$(EXEC_PATH)/lstring_test_utf8$(EXT)
	
line: 
	@echo =====================================
	@echo =====================================
