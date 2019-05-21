#include "base.h"
#include "commonElements.h"
#include "testTool.h"

vector<NamedSolution> slowSolutions = {
	{commonElementsLinear, "linear"},
};
vector<NamedSolution> fastSolutions = {
	{commonElementsSort, "sort"},
	{commonElementsSet, "set"},
	{commonElementsHashTable, "hashtable"},
};
vector<NamedSolution> solutions = []() { // c++ has no "vector + vector" =(
	vector<NamedSolution> x = fastSolutions;
	x.insert(x.end(), all(slowSolutions));
	return x;
}();

commonElementsFunc modelSolution = commonElementsLinear;

int main() {
	// unitTests(solutions);
	// testCorrectnessStress(modelSolution, solutions);
	// testTL(fastSolutions);

	struct Data {
		NamedSolution solution;
		vector<TimeType> times;
	};

	auto experiment = [&](const vector<int> &ns) {
		vector<Data> data;
		for (auto &solution : solutions) {
			data.push_back({solution, calcTime(ns, solution)});
		}
		logger.precision(9);
		logger << "times are around " << data[0].times[0] / 1e9 << endl;
		logger.precision(3);
		logger << fixed;
		logger << AlignedString(10, "n") << ": ";
		for (int n : ns)
			logger << AlignedString(5, to_string(n)) << " ";
		logger << endl;
		for (auto &p : data) {
			logger << AlignedString(10, p.solution.name) << ": ";
			forn(j, ns.size())
				logger << (double)p.times[j] / data[0].times[j] << " ";
			logger << endl;
		}
	};

	vector<int> ns(12);
	forn(i, ns.size())
		ns[i] = 1 << i;
	experiment(ns);
	experiment(ns);
	logger << endl;
	forn(i, ns.size())
		ns[i] = i + 1;
	experiment(ns);
	experiment(ns);
}
