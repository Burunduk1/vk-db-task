#include "base.h"
#include "commonElements.h"
#include "testTool.h"

vector<NamedSolution> solutions = {
	{commonElementsLinear, "linear"},
	{commonElementsSort, "sort"},
	{commonElementsSet, "set"},
	{commonElementsHashTable, "hashtable"},
};
commonElementsFunc modelSolution = commonElementsLinear;

int main() {
	vector<int> a;
	debug(gen(10, 3, a)), cerr << endl;
	unitTests(solutions);
	testCorrectnessStress(modelSolution, solutions);
}
