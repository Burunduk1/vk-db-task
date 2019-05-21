flags = -std=c++17 -O3 -Wall -Wextra

main: main.cpp testTool.cpp commonElements.cpp *.h
	g++ $(flags) main.cpp testTool.cpp commonElements.cpp -o main #2>&1 | grep -iE "(warning)|(error)|(note)"

mainTest: mainTest.cpp testTool.cpp commonElements.cpp *.h
	g++ $(flags) main.cpp testTool.cpp commonElements.cpp -o main 
