#pragma once

#include "base.h"

vector<int>& gen(int n, int C, vector<int> &a);
void debug(const vector<int> &a, const string &end = "\n", ostream &o = cerr);

void unitTests(const vector<NamedSolution> &solutions);
void testCorrectnessStress(const commonElementsFunc &modelSolution, const vector<NamedSolution> &solutions);
