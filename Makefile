UNITY_ROOT=./unity
INCLUDE_DIRS=-I $(UNITY_ROOT)
CFLAGS=$(INCLUDE_DIRS) -g -Wall
SRC_FILES=$(UNITY_ROOT)/unity.c testfile.c cmdproc.c
TEST_RUNNER=test

all: clean $(TEST_RUNNER)
	./$(TEST_RUNNER)

$(TEST_RUNNER): $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TEST_RUNNER)

clean:
	rm -f $(TEST_RUNNER)