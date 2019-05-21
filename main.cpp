#include "base.h"
#include "commonElements.h"
#include "testTool.h"

vector<NamedSolution> solutions = {
	{commonElementsSort, "sort"},
	{commonElementsSet, "set"},
	{commonElementsHashTable, "hashtable"},
	{commonElementsLinear, "linear"},
	{commonElements, "OPT"},
};

int main() {
	struct Data {
		NamedSolution solution;
		vector<TimeType> times;
	};

	auto experiment = [&](bool smallA, const vector<int> &ns) {
		vector<Data> data;
		for (auto &solution : solutions) {
			data.push_back({solution, calcTime(smallA, ns, solution)});
		}
		logger.precision(9);
		logger << "|a| is " << (smallA ? "small" : "large") << ", times are around " << data[0].times[0] / 1e9 << endl;
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
		logger << endl;
	};

	// bool smallA = true;
	// vector<int> ns(12);
	// forn(i, ns.size())
	// 	ns[i] = i + 1;
	// experiment(smallA, ns);
	// forn(i, ns.size())
	// 	ns[i] = 1 << i;
	// experiment(smallA, ns);
	// smallA = false;
	// experiment(smallA, ns);

	auto opsInOneSec = [](int testsN, int na, int nb) {
		logger << "OPT: for |b| = " << nb << " is " << (double)testsN * (na + nb) << " operations in " << 1e-9 * calcTime(testsN, na, nb, 1e9, commonElements) << " seconds" << endl;
	};
	opsInOneSec(2.1e7, 10, 10);
	opsInOneSec(4.2e4, 1000, 1000);
}
