CC = g++
CFLAGS = -c -Wall -Wextra -Werror -g -std=c++17 
TEST_CFLAGS = -lgtest -lgmock -pthread
OBJ = $(CFILES:.cc=.o)
TESTS_OBJ = $(TESTS_CFILES:.cc=.o)
TESTS_CFILES = $(wildcard tests/*.cc)
CFILES = $(wildcard source/*.cc)
LIBRARY = s21_3d_viewer.a
OPEN = open
# GCOV_FLAGS=--coverage -Wall -Werror -Wextra -std=c++17

ifeq ($(shell uname -s), Linux)
	OPEN = xdg-open
endif


# $^ вызов всех подцелей
# $< вызов первой подцели
# $@ вызов цели

all: install

$(LIBRARY) : $(OBJ)
	ar -rc $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY)

install:
ifeq ($(shell uname -s), Linux)
	cd interface && qmake6 && make && make clean
	cp -r interface/3d_viewer_v2.0 ~/Desktop
endif
ifeq ($(shell uname -s), Darwin)
	cd interface && qmake6 && make && make clean
	cd interface/3d_viewer_v2.0.app/Contents/MacOS && ./3d_viewer_v2.0
endif
uninstall:
ifeq ($(shell uname -s), Linux)
	rm -rf interface/3d_viewer_v2.0
	rm -rf ~/Desktop/3d_viewer_v2.0
	rm -rf interface/interface/Makefile
endif
ifeq ($(shell uname -s), Darwin)
	rm -rf interface/3d_viewer_v2.0.app
endif

tests : $(TESTS_OBJ) $(LIBRARY)
	$(CC) $^ -o test $(TEST_CFLAGS)
	./test

dvi:
	doxygen
	$(OPEN) ./documentation/html/index.html

dist: install
	mkdir archiv
	cp -r source/*.h source/*.cc Makefile Doxyfile interface/ archiv
	tar -cvzf 3d_viewer_v2.tar.gz archiv
	rm -rf archiv

checkstyle:
	clang-format -style=google -n tests/*.cc
	clang-format -style=google -n tests/*.h
	clang-format -style=google -n source/*.cc
	clang-format -style=google -n source/*.h

%.o : %.cc
	$(CC) $(CFLAGS) $^ -o $@


clean:
	rm -rf $(OBJ) $(TESTS_OBJ) test *.gcov *.gcno *.gcda *.info report $(LIBRARY)
	-rm -rf ./documentation/
