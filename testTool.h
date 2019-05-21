#pragma once

#include "base.h"

vector<int>& gen(int n, int C, vector<int> &a);
void debug(const vector<int> &a, const string &end = "\n", ostream &o = cerr);

void testCorrectness(commonElementsFunc modelSolution, const vector<NamedSolution> &solutions);
