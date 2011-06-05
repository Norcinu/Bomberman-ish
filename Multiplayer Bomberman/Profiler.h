#ifndef PROFILER_H
#define PROFILER_H

#include <fstream>
#include <vector>

struct Results_t
{
	double time_taken_ms;
	double time_taken_seconds;
};

class Timer;

class Profiler
{
public:
	Profiler(void);
	Profiler(const std::string& name);
	~Profiler(void);

	std::string GetName() const { return test_name; }
	void SetName(const std::string& name) { test_name = name; }

	void Start();
	void End();
	void WriteResults();

private:
	double FindMaxMS();
	double FindMaxSeconds();

private:
	std::vector<Results_t> results;
	std::string test_name;
	Timer *test_timer; // bad idea?
};

#endif
