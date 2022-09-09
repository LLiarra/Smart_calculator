CC=gcc
FLAGS=-g -Wall -Wextra -Werror -std=c11 -pedantic
CFLAGS=-c $(FLAGS)
TEST_FLAGS=-lcheck -lgcov -lm -lrt -lpthread -lsubunit

#SRCS
SRC_CFILES=s21_linked_list.c polish_notation.c s21_calculate.c s21_smart_calc.c
SRC_TEST=s21_test.c

SOURCES=./Qcustomplot/qcustomplot.cpp \
		./main.cpp \
		./mainwindow.cpp \
  		./s21_calculations/s21_calculate.c \
  		./s21_collection/s21_linked_list.c \
  		./s21_polish_notation/polish_notation.c \
  		./s21_smart_calc.c
HEADERS=./Qcustomplot/qcustomplot.h \
 		./mainwindow.h \
 		./s21_calculations/s21_calculate.h \
 		./s21_collection/s21_linked_list.h \
 		./s21_collection/struct.h \
  		./s21_polish_notation/polish_notation.h \
 		./s21_smart_calc.h

#OBJECTS
OBJ=$(notdir $(SRC_CFILES:.c=.o))
OBJ_TEST=$(notdir $(SRC_TEST:.c=.o))

#DIRECTORY
OBJ_DIR=objects
SRC_DIR=./SmartCalc/s21_collection ./SmartCalc/s21_polish_notation ./SmartCalc/s21_calculations ./SmartCalc
TEST_DIR=s21_test
BD=../build/

#INCLUDES
INCLUDE=s21_linked_list.h \
		polish_notation.h \
		s21_calculate.h \
		struct.h \

vpath %.c $(SRC_DIR) $(TEST_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(SRC_DIR)

.PHONY: all clean test gcov_report build install uninstall div

all: build

build: $(BD)SmartCalc.pro
	cd $(BD); qmake SmartCalc.pro
	make -C $(BD)

./$(BD)SmartCalc.pro:
	@mkdir -p ../build/  2>/dev/null
	cp SmartCalc.pro $(BD)

./$(BD)%.o: */*/%.cpp
	g++ -C $< -o $@

install: build
	@mkdir -p ../Applications/  2>/dev/null
	cp -rf $(BD)SmartCalc ../Applications/
	make clean

uninstall:
	rm -rf ../Applications

dvi:
	latex ./Documentation/SmartCalc.tex
	mv ./SmartCalc.dvi ./Documentation
	rm -rf ./SmartCalc.aux ./SmartCalc.log

dist: install dvi
	tar -cvf SmartCalc.tar Documentation/SmartCalc.dvi ../Applications/SmartCalc
	gzip SmartCalc.tar

%.o: %.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(addprefix $(OBJ_DIR)/, $@) -c $<

tests: $(OBJ_TEST) $(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ) $(OBJ_TEST)) $(TEST_FLAGS) -o test
	./test

gcov_report:CFLAGS += -coverage
gcov_report: clean tests
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;

valgrind: tests
	valgrind --leak-check=full ./test

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ./SmartCalc/*.c ./$(TEST_DIR)/*.c ./SmartCalc/s21_collection/*.c \
	./SmartCalc/s21_polish_notation/*.c ./SmartCalc/s21_calculations/*.c

clean:
	rm -rf $(OBJ_DIR) report test gcov_report.info ./$(BD)* ./$(BD).qmake.stash ./$(BD).qm

fclean: clean uninstall
	rm ./Documentation/SmartCalc.dvi SmartCalc.tar.gz
