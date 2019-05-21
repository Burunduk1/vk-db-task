#include "base.h"
#include "commonElements.h"
#include "testTool.h"

commonElementsFunc modelSolution = commonElementsLinear;
vector<NamedSolution> solutions = {
	{commonElementsSort, "sort"},
	{commonElementsSet, "set"},
};

int main() {
	vector<int> a;
	debug(gen(10, 3, a)), cerr << endl;
	testCorrectness(commonElementsLinear, solutions);
	commonElementsFunc f[] = {commonElementsLinear, commonElementsSort, commonElementsSet};
}
