#include "base.h"
#include "commonElements.h"
#include "testTool.h"

vector<NamedSolution> slowSolutions = {
	{commonElementsLinear, "linear"},
	{commonElementsSet, "set"},
};
vector<NamedSolution> fastSolutions = {
	{commonElementsSort, "sort"},
	{commonElementsHashTable, "hashtable"},
	{commonElements, "OPT"},
};
vector<NamedSolution> solutions = []() { // c++ has no "vector + vector" =(
	vector<NamedSolution> x = fastSolutions;
	x.insert(x.end(), all(slowSolutions));
	return x;
}();

commonElementsFunc modelSolution = commonElementsLinear;

int main() {
	unitTests(solutions);
	testCorrectnessStress(modelSolution, solutions);
	testTL(fastSolutions);
}
