#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <cassert>

using namespace std;

#define all(a) (a).begin(), (a).end() // sorry =)
#define forn(i, n) for (size_t i = 0; i < (n); i++) // sorry =)

extern ostream &logger;

struct AlignedString {
	int n;
	string s;
	AlignedString(int n, string s) : n(n), s(s) {
	}
};

ostream& operator << (ostream &out, AlignedString p);
