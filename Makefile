NAME = s21_containers
CC = clang++
CC_FLAGS = -std=c++17 -Wall -Wextra -Werror -g
GCOV_FLAGS = -L. -lgcov -lgtest -lgtest_main  --coverage
OS = $(shell uname)
#-o test -lgtest  -pthread - флаги для тестов из статьи
ifeq ($(OS), Linux)
		CHECK_FLAGS = -lgtest -pthread -lrt -lm -lsubunit
else
    CHECK_FLAGS = $(shell pkg-config --libs --cflags gtest)
endif

TEST_COMPILE = $(CC) $(CC_FLAGS) test/*.cpp   $(CHECK_FLAGS)
all: clean

clean:
	rm -rf *.o, *.g* *.info *.out report *.a *.dSYM

re: clean all


test:
	$(TEST_COMPILE)
	./a.out

clang:
	clang-format -i vector/*.h array/*.h array/test/*.cc vector/test/*.cc array/test/*.h vector/test/*.h

gcov_report:  test
	rm -f *.g*
	$(CC) $(CC_FLAGS) array/test/*.cc vector/test/*.cc  $(CHECK_FLAGS) $(GCOV_FLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno

check:
	clang-format -style=google -n array/*.h vector/*.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind ./a.out --leak-check=full
endif
	make clean

.PHONY: all clean re s21_containers.a test gcov_report check
