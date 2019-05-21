#pragma once

#include "base.h"

#include <chrono>

class TimerNano {
private:
	chrono::steady_clock::time_point startPoint;
public:
	void start() { 
		startPoint = chrono::steady_clock::now();
	}
	long long time() {
		auto endPoint = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<chrono::nanoseconds>(endPoint - startPoint).count();
	}
};
