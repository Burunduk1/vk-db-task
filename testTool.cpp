#include "base.h"
#include "commonElements.h"

static std::mt19937 randomNumbers(239017);
static ostream &logger = cout;

// [L, R]
size_t randomInt(size_t L, size_t R) {
	return L + randomNumbers() % (R - L + 1);
}

// generates n integers in [1, C]
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
	int testsN = 1e5;
	logger << "testCorrectness: start " << testsN << " tests" << endl;
	for (int i = 0; i < testsN; i++) {
		vector<int> a, b;
		int na = randomInt(10, 20);
		int nb = randomInt(10, 20);
		int c = randomInt(10, 20);
		gen(na, c, a);
		gen(nb, c, b);
		Test test = {a, b, modelSolution(a, b)};
		for (auto solution : solutions) {
			run(solution, test);
		}
	}
	logger << "testCorrectness: OK" << endl;
}

