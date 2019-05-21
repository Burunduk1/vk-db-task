flags = -std=c++17 -Wall -Wextra -O3 # -pg 

corecpp = base.cpp testTool.cpp commonElements.cpp
main: Makefile $(corecpp) main.cpp *.h 
	g++ $(flags) main.cpp $(corecpp) -o main #2>&1 | grep -iE "(warning)|(error)|(note)"

mainTest: Makefile mainTest.cpp $(corecpp) *.h
	g++ -DTEST_MODE $(flags) mainTest.cpp $(corecpp) -o mainTest #2>&1 | grep -iE "(warning)|(error)|(note)"
