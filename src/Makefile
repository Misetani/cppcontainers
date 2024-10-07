CC = g++
CFLAGS = --std=c++17 -Wall -Wextra -Werror
LIBS = -lgtest -lgtest_main -lpthread

TEST_SRC = $(wildcard tst_src/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

HEADERS = $(wildcard *.h) $(wildcard lib_src/*.h) $(wildcard tst_src*.h)

PROGRAM = test

all: test clean

test: $(TEST_OBJ)
	@$(CC) $(CFLAGS) $(TEST_OBJ) -o $(PROGRAM) $(LIBS)
	@./$(PROGRAM) || true

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

#check: $(TEST_OBJ)
#	@cppcheck $(TEST_SRC) $(HEADERS)

#clang-check:
#	@cp ../materials/linters/.clang-format .
#	@clang-format -n -style=Google $(TEST_SRC) $(HEADERS)
#
#	@rm -f .clang-format
	
#clang-format:
#	@cp ../materials/linters/.clang-format .
#	@clang-format -i -style=Google $(TEST_SRC) $(HEADERS)
#
#	@rm -f .clang-format

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./test > /dev/null

clean:
	@rm -rf $(TEST_OBJ) $(PROGRAM) *.css *.html *.gcno *.gcda *.info tests report *.dSYM