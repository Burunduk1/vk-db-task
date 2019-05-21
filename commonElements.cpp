#include "base.h"
#include "hashTable.h"
#include "commonElements.h"

#include <algorithm>
#include <set>

size_t commonElementsLinear(const vector<int> &large, const vector<int> &small) {
	return count_if(all(large), [&small](int x){ return find(all(small), x) != small.end(); });
}

size_t commonElementsSort(const vector<int> &large, const vector<int> &small) {
	auto smallCopy = small;
	sort(all(smallCopy));
	return count_if(all(large), [&smallCopy](int x){ return binary_search(all(smallCopy), x); });
}

size_t commonElementsSet(const vector<int> &large, const vector<int> &small) {
	set<int> smallSet(all(small));
	return count_if(all(large), [&smallSet](int x){ return smallSet.count(x); });
}

size_t commonElementsHashTable(const vector<int> &large, const vector<int> &small) {
	HashTable<int> smallSet(small);
	return count_if(all(large), [&smallSet](int x){ return smallSet.count(x); });
}

/** The solution */
size_t commonElements(const vector<int> &a, const vector<int> &b) {
	auto f = [](const vector<int> &large, const vector<int> &small) {
		size_t n = small.size();
		static const int C1 = 5;
		static const int C2 = 20;
		if (n < C1)	return commonElementsLinear(large, small);
		if (n < C2)	return commonElementsSort(large, small);
		return commonElementsHashTable(large, small);
	};
	return a.size() < b.size() ? f(b, a) : f(a, b);
}
