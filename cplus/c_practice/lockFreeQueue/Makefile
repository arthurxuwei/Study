LIB_SRC_FILES = workthreadpool.cpp casqueue.cpp
TEST_SRC_FILES = main.cpp
STD_FLAG = -std=c++0x
INCLUDE_DIR = ./

all: main.o libs
	g++ $(STD_FLAG) -o test_workthreadpool main.o libworkthreadpool.so -lpthread

main.o: $(TEST_SRC_FILES)
	g++ $(STD_FLAG) -c $(TEST_SRC_FILES) -I$(INCLUDE_DIR)

libs: $(LIB_SRC_FILES)
	g++ $(STD_FLAG) -o libworkthreadpool.so -fPIC -O2 -shared -Wl,--no-as-needed -I./ $(LIB_SRC_FILES) -lpthread

.PHONY: clean
clean:
	rm -f test_workthreadpool main.o libworkthreadpool.so
