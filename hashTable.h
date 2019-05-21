#pragma once

#include "base.h"

// #define DEBUG

class HashTable {
private:
	unsigned cc;
	vector<unsigned> used;
	size_t n;
	vector<int> table;
	const static size_t P = 1e9 + 7; // you may use random, to make it more safe 

private:
	bool isPrime(size_t n) {
		for (size_t i = 2; i * i <= n; i++)
			if (n % i == 0)
				return 0;
		return n >= 2;
	}
	size_t position(int x) {
		size_t i = (unsigned long long)x * P % n;
		#ifdef DEBUG
		int cnt = 0;
		static int globalCnt = 0, callsCnt = 0;
		callsCnt++;
		#endif
		while (used[i] == cc && table[i] != x) {
			#ifdef DEBUG
			assert(++globalCnt <= callsCnt + 50);
			assert(++cnt <= 50); // 40 is not enough
			#endif
			if (++i == n)
				i = 0;
		}
		return i;
	}

public:
	HashTable() : cc(0) {
	}

	void build(const vector<int> &data) {
		n = 2 * (data.size() + 1);
		while (!isPrime(n))
			n++;
		table.resize(n);
		used.resize(n, 0);
		cc++;
		if (!cc) {
			cc++;
			fill(all(used), 0);
		}
		for (auto x : data) {
			auto i = position(x);
			used[i] = cc;
			table[i] = x;
		}
	}
	bool count(int x) {
		return used[position(x)] == cc;
	}
};
