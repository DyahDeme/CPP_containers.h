OS=$(shell uname)
ifeq ($(OS), Linux)
	CXXFLAGS = -lgtest -g -lpthread
else
	CXXFLAGS = -lgtest -g
endif

LEAKS = CK_FORK=no leaks --atExit --
CXX=g++ -std=c++17 -Wall -Wextra -Werror
SUBDIRS = my_list my_queue my_array my_stack my_vector my_map my_set my_multiset 


all: tests lint

tests: clean $(SUBDIRS)

$(SUBDIRS): clean
	@$(CXX) --coverage -O0 -C $@/test_$@.cpp -o $@_tests $(CXXFLAGS)
	$(LEAKS) ./$@_tests

gcov_report: tests
	lcov -t "gcov_report" --no-external -o all_tests.info -c -d .
	genhtml -o all_report all_tests.info
	@open -a "Safari" all_report/index.html

clean:
	rm -rf *.gcda *.gcno *.o *.info *_tests */*.out *.dSYM all_report

lint:
	@clang-format -i -style=Google my_*/*.h
	clang-format -n -style=Google my_*/*.h

.PHONY:  check clean_gcov gcov_report tests $(SUBDIRS)
