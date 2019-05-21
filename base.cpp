#include "base.h"

ostream &logger = cout;

ostream& operator << (ostream &out, AlignedString p) {
	forn(i, p.n - p.s.size())
		out << ' ';
	out << p.s;
	return out;
}
