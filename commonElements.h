#pragma once

#include "base.h"
#include "hashTable.h"

typedef size_t (*commonElementsFunc)(const vector<int> &a, const vector<int> &b);
struct NamedSolution {
	commonElementsFunc f;
	string name;
} ;

size_t commonElementsLinear(const vector<int> &a, const vector<int> &b);
size_t commonElementsSort(const vector<int> &a, const vector<int> &b);
size_t commonElementsSet(const vector<int> &a, const vector<int> &b);
size_t commonElementsHashTable(const vector<int> &a, const vector<int> &b);
