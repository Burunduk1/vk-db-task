#include "base.h"
#include "commonElements.h"
#include "timer.h"

static std::mt19937 randomNumbers(239017);
static ostream &logger = cout;

// [L, R]
size_t randomInt(size_t L, size_t R) {
	return L + randomNumbers() % (R - L + 1);
}

// Generates n integers in [1, C]
// Can produce duplicates, but it does not matter when we test correctness/speed.
vector<int>& gen(int n, int C, vector<int> &result) {
	uniform_int_distribution<int> dist(1, C);
	result.resize(n);
	for (int &x : result)
		x = dist(randomNumbers);
	return result;
}

void debug(const vector<int> &a, const string &end = "\n", ostream &o = cerr) {
	o << '[';
	if (!a.empty()) {
		o << a[0];
		for (size_t i = 1; i < a.size(); i++)
			o << ", " << a[i];
	}
	o << "]" << end;
}

struct Test {
	vector<int> a, b;
	size_t answer;
};

void run(const NamedSolution &solution, const Test &test) {
	auto output = solution.f(test.a, test.b);
	if (test.answer != output) {
		cerr << "solution '" << solution.name << "' failed" << endl;
		cerr << "test: ", debug(test.a, " "), debug(test.b);
		cerr << "output: " << output << endl; 
		cerr << "answer: " << test.answer << endl; 
		throw "WA";
	}
}

void unitTests(const vector<NamedSolution> &solutions) {
	vector<Test> tests = {
		{{1, 2, 3}, {1}, 1},
		{{1, 2, 3}, {0, 4}, 0},
		{{1, 2, 3}, {4, 2, 5, 1}, 2},
		{{}, {}, 0},
		{{}, {1}, 0},
		{{1}, {}, 0},
		{{1}, {1}, 1},
		{{1}, {2}, 0},
		{{1, 2, 3}, {1, 2, 3}, 3},
		{{1, 2, 3, 4, 5, 6, 7}, {1, 4, 7}, 3},
		{{1, 2, 3, 4, 5, 6, 7}, {2, 4, 6}, 3},
		{{1, 2, 3, 4, 5, 6, 7}, {3, 4, 5}, 3},
		{{2, 4, 6}, {1, 2, 3, 4, 5, 6, 7}, 3},
		{{0, 2, 4, 6, 8, 10}, {0, 3, 6, 9, 12}, 2},
	};
	logger << "unitTests: start " << tests.size() << " tests" << endl;
	for (auto &test : tests) {
		for (auto solution : solutions) {
			run(solution, test);
		}
	}
	logger << "unitTests: OK" << endl;
}

void testCorrectnessStress(const commonElementsFunc &modelSolution, const vector<NamedSolution> &solutions) {
	struct GenParams {
		int minLen, maxLen, c;
	};
	vector<GenParams> tests = {
		{1, 6, 10},
		{10, 20, 10},
		{10, 20, 100},
		{100, 10, 100},
	};

	for (auto test : tests) {
		int testsN = 1e4;
		logger << "testCorrectness: start " << testsN << " tests n in [" << test.minLen << "," << test.maxLen << "], c = " << test.c << endl;
		double sum = 0;
		for (int i = 0; i < testsN; i++) {
			vector<int> a, b;
			int na = randomInt(test.minLen, test.maxLen);
			int nb = randomInt(test.minLen, test.maxLen);
			int c = test.c;
			gen(na, c, a);
			gen(nb, c, b);
			Test test = {a, b, modelSolution(a, b)};
			for (auto solution : solutions) {
				run(solution, test);
			}
			sum += test.answer;
		}
		logger << "testCorrectness: OK, average answer is  " << sum / testsN  << endl;
	}
	logger << "testCorrectness: END" << endl;
}

// Returns { time1(i)/time2(i) | i=1..n }
vector<double> compareSpeed(int n, const commonElementsFunc &solution1, const commonElementsFunc &solution2) { 
}
