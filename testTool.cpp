#include "testTool.h"

#include <algorithm>
#include <climits>

static std::mt19937 randomNumbers(239017);

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

// o << a << end
void debug(const vector<int> &a, const string &end, ostream &o) {
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

struct GenParams {
	int minLen, maxLen, c, n;
};

void testCorrectnessStress(const commonElementsFunc &modelSolution, const vector<NamedSolution> &solutions) {
	const int testsN = 1e4;
	vector<GenParams> tests = {
		{1, 6, 10, testsN},
		{10, 20, 10, testsN},
		{10, 20, 100, testsN},
		{10, 20, int(1e9), testsN},
		{1, 100, 100, testsN},
	};

	for (auto test : tests) {
		logger << "testCorrectness: start " << test.n << " tests n in [" << test.minLen << "," << test.maxLen << "], c = " << test.c << endl;
		double sum = 0;
		for (int i = 0; i < test.n; i++) {
			vector<int> a, b;
			int na = randomInt(test.minLen, test.maxLen);
			int nb = randomInt(test.minLen, test.maxLen);
			int c = test.c;
			gen(na, c, a);
			gen(nb, c, b);
			Test test = {a, b, modelSolution(a, b)};
			for (auto solution : solutions) {
				// logger << "[" << solution.name << "]" << endl;
				run(solution, test);
			}
			sum += test.answer;
		}
		logger << "testCorrectness: OK, average answer is  " << sum / test.n  << endl;
	}
	logger << "testCorrectness: END" << endl;
}

void testTL(const vector<NamedSolution> &solutions) {
	vector<GenParams> tests = {
		{int(1e6), int(1e6), int(1e6), 10},
		{int(1e6), int(1e6), int(1e9), 10},
	};
	for (auto test : tests) {
		logger << "testTL: start " << test.n << " tests n in [" << test.minLen << "," << test.maxLen << "], c = " << test.c << endl;
		for (int i = 0; i < test.n; i++) {
			vector<int> a, b;
			int na = randomInt(test.minLen, test.maxLen);
			int nb = randomInt(test.minLen, test.maxLen);
			int c = test.c;
			gen(na, c, a);
			gen(nb, c, b);
			assert(!solutions.empty());
			Test test = {a, b, solutions[0].f(a, b)};
			for (size_t i = 1; i < solutions.size(); i++) {
				// logger << "run solution '" << solution.name << "'" << endl;
				run(solutions[i], test);
			}
		}
	}
	logger << "testTL: END" << endl;
}

// |a| = (smallA ? 2|b| : 1e4)
// Returns { time(|a|, |b|) | |b| \in ns }
vector<TimeType> calcTime(bool smallA, const vector<int> &ns, const NamedSolution &solution) { 
	static const int TIME = 3e5;
	int c = INT_MAX;
	vector<int> a, b;
	vector<TimeType> result;
	for (int n : ns) {
		int aLen = (smallA ? 2 * n : int(1e4));
		int testsN = TIME / (n + aLen);
		TimeType summaryTime = 0;
		for (int test = 0; test < testsN; test++) {
			gen(aLen, c, a);
			gen(n, c, b);
			TimerNano timer;
			solution.f(a, b);
			summaryTime += timer.time();
		}
		result.push_back(summaryTime);
	}
	return result;
}

TimeType calcTime(int testsN, int na, int nb, int c, const commonElementsFunc &solution) { 
	vector<int> a, b;
	gen(na, c, a);
	gen(nb, c, b);
	TimerNano timer;
	while (testsN--)
		solution(a, b);
	return timer.time();
}
