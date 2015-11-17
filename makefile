INCDIRS:=/Users/dmielke/Documents/oopl/trees/googletest/googletest/include
LIBDIRS:=/Users/dmielke/Documents/oopl/trees/googletest/googletest/make

FILES :=                                \
    .travis.yml                         \
    dijkstra-tests/EID-RunTheater.in   \
    dijkstra-tests/EID-RunTheater.out  \
    dijkstra-tests/EID-TestTheater.c++ \
    dijkstra-tests/EID-TestTheater.out \
    Theater.c++                        \
    Theater.h                          \
    Theater.log                        \
    html                                \
    RunTheater.c++                     \
    RunTheater.in                      \
    RunTheater.out                     \
    TestTheater.c++                    \
    TestTheater.out                    \
    TheaterBundle.c++

# Call gcc and gcov differently on Darwin
ifeq ($(shell uname), Darwin)
  CXX      := g++
  GCOV     := gcov
  VALGRIND := echo Valgrind not available on Darwin
else
  CXX      := g++-4.8
  GCOV     := gcov-4.8
  VALGRIND := valgrind
endif

CXXFLAGS   := -pedantic -std=c++11 -Wall -I$(INCDIRS)
LDFLAGS    := -lgtest -lgtest_main -pthread -L$(LIBDIRS)
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunTheater
	rm -f RunTheater.tmp
	rm -f TestTheater
	rm -f TestTheater.tmp
	rm -f TheaterBundle

config:
	git config -l

bundle:
	cat Theater.h Theater.c++ RunTheater.c++ | sed -e "s/#include \"Theater.h\"//g" > TheaterBundle.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) TheaterBundle.c++ -o TheaterBundle

scrub:
	make  clean
	rm -f  Theater.log
	rm -rf dijkstra-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunTheater.tmp TestTheater.tmp

RunTheater: Theater.h Theater.c++ RunTheater.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Theater.c++ RunTheater.c++ -o RunTheater

RunTheater.tmp: RunTheater
	./RunTheater < RunTheater.in > RunTheater.tmp
	diff RunTheater.tmp RunTheater.out

TestTheater: Theater.h Theater.c++ TestTheater.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Theater.c++ TestTheater.c++ -o TestTheater $(LDFLAGS)

TestTheater.tmp: TestTheater
	./TestTheater                                                     >  TestTheater.tmp 2>&1
	$(VALGRIND) ./TestTheater                                         >> TestTheater.tmp
	$(GCOV) -b Theater.c++     | grep -A 5 "File 'Theater.c++'"     >> TestTheater.tmp
	$(GCOV) -b TestTheater.c++ | grep -A 5 "File 'TestTheater.c++'" >> TestTheater.tmp
	cat TestTheater.tmp
