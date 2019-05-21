#pragma once

#include "base.h"

#include <chrono>

typedef long long TimeType;

class TimerNano {
private:
	chrono::steady_clock::time_point startPoint;
public:
	TimerNano() {
		start();
	}
	void start() { 
		startPoint = chrono::steady_clock::now();
	}
	TimeType time() {
		auto endPoint = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<chrono::nanoseconds>(endPoint - startPoint).count();
	}
};
