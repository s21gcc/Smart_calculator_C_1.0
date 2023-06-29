#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags



SRCS        := calc.c
TEST_SRCS	:= test.c
OBJS        := $(SRCS:.c=.o)
TEST_OBJS	:= $(TEST_SRCS:.c=.o)

CC				:= gcc
CFLAGS			:= -c -std=c11 -Wall -Werror -Wextra
PROFILE_FLAGS 	:= -fprofile-arcs -ftest-coverage
TST_LIBS		:= -lcheck -lm -lpthread
COV_LIBS		:= -lgcov -coverage

#------------------------------------------------#
#   PEERS                                        #
#------------------------------------------------#

all: clean uninstall install open


install:
	make clean
	mkdir build
	cd smart_calc && qmake && make && make clean  && cd ../ && mv smart_calc/calc.app build

uninstall:
	rm -rf build*

test: clean
	cd smart_calc && $(CC) $(CFLAGS) $(SRCS) $(PROFILE_FLAGS) -o calc.o
	cd smart_calc && $(CC) $(CFLAGS) $(TEST_SRCS) -o test.o
	cd smart_calc && $(CC) $(TEST_OBJS) $(OBJS) $(TST_LIBS) $(COV_LIBS) -o $@
	cd smart_calc && ./test

gcov_report: test
	cd smart_calc && lcov -t "s21_smart_calc" -o test.info -c -d .
	cd smart_calc && genhtml -o report test.info
	cd smart_calc && open ./report/index.html

clean:
	cd smart_calc && rm -rf *.o *.a
	cd smart_calc && rm -rf *.gcno *gcda *.gcov *.info
	cd smart_calc && rm -rf test ./report && rm -rf .qmake.stash && rm -rf .qmake.stash

style:
	cd smart_calc && clang-format -style=Google -n *.c *.h *.cpp

dist: install
	rm -rf Dist_SmartCalc/
	mkdir Dist_SmartCalc/
	mkdir Dist_SmartCalc/src
	mv ./build/calc.app Dist_SmartCalc/src/
	tar cvzf Dist_SmartCalc.tgz Dist_SmartCalc/
	rm -rf Dist_SmartCalc/
	rmdir build

open:
	open ./build/calc.app

dvi:
	open dvi.txt

