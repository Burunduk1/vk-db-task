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

void testCorrectness(commonElementsFunc modelSolution, const vector<NamedSolution> &solutions) {
	int testsN = 1e5;
	logger << "testCorrectness: start " << testsN << " tests" << endl;
	for (int i = 0; i < testsN; i++) {
		vector<int> a, b;
		int na = randomInt(10, 20);
		int nb = randomInt(10, 20);
		int c = randomInt(10, 20);
		gen(na, c, a);
		gen(nb, c, b);
		auto answer = modelSolution(a, b);
		for (auto solution : solutions) {
			auto output = solution.f(a, b);
			if (answer != output) {
				cerr << "solution '" << solution.name << "' failed" << endl;
				cerr << "test: ", debug(a, " "), debug(b);
				cerr << "output: " << output << endl; 
				cerr << "answer: " << answer << endl; 
				throw "WA";
			}
		}
	}
	logger << "testCorrectness: OK" << endl;
}
