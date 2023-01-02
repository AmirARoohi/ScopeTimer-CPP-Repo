#include<iostream>
#include<memory>
#include<chrono>
#include<array>
#include<cmath>


/*To call CPU clock*/
//  Windows
#ifdef _WIN32

#include <intrin.h>
uint64_t rdtsc() {
	return __rdtsc();
}

//  Linux/GCC
#else

uint64_t rdtsc() {
	unsigned int lo, hi;
	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}
#endif


/*ScopeTimer*/
/*This is a scope timer in c++, which measures the time it takes for a scope to finish in Nano-seconds & CPU cycles. 
Very straightforward and easy code, which uses the chrono library.
It has only one class (Timer). 
You need to instantiate it in the scope and it will print the time when the program goes out of that certain scope.
Syntax: { Timer TimeIt; Function(); } */ 
/* Amir A. Roohi - Dec 26th -2022 */

class Timer {

public: 
	Timer() 
	{
		m_StartTimeReference = std::chrono::high_resolution_clock::now();
		// This need to be private variable in the class, so that it's accessible in method Stop
        Tick= rdtsc(); //Initiation of the CPU clock
	}

	~Timer() 
	{
		Stop();
        // Stop will be called when the destructor is called automatically when the program goes out of scope
	}

	void Stop()
	{
		int_fast64_t Tock = rdtsc(); // Stop the CPU clock
		int_fast64_t TickTock = Tock - Tick; 
		auto FinishTimePoint = std::chrono::high_resolution_clock::now(); // Get the system high resolution clock at the stop time
	
		auto Start = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_StartTimeReference).time_since_epoch().count();
		auto Finish = std::chrono::time_point_cast<std::chrono::nanoseconds>(FinishTimePoint).time_since_epoch().count();

		auto Duration = Finish - Start;
		double MilSec = Duration * 0.000001;

		std::cout << Duration << "ns (" << MilSec << "ms)\n";
		std::cout << TickTock << " CPU cycles \n";
	}

private:

	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimeReference;
    int_fast64_t Tick;
};
