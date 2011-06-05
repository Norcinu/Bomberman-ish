#include "Profiler.h"
#include "Timer.h"

Profiler::Profiler(void) : test_name("default"), test_timer(new Timer)
{
}

Profiler::Profiler(const std::string& name) : test_name(name), test_timer(new Timer)
{
}

Profiler::~Profiler(void)
{
	delete test_timer;
}

//start of code block.
void Profiler::Start()
{
	test_timer->Reset();
}

// end of code block.
void Profiler::End()
{
	Results_t result;
	result.time_taken_ms =  test_timer->Milliseconds();
	result.time_taken_seconds = test_timer->Seconds();
	results.push_back(result);
}

// call when closing application.
void Profiler::WriteResults()
{
	double average_ms=0.0;
	for (size_t i=0; i < results.size(); ++i)
	{
		average_ms += results[i].time_taken_ms;
	}
	average_ms /= results.size();

	double average_seconds=0.0;
	for (size_t i=0; i < results.size(); ++i)
	{
		average_seconds += results[i].time_taken_seconds;
	}
	average_seconds /= results.size();
	
	printf("Writing test name : %s \n", test_name.c_str());

	std::ofstream test_output(test_name.append(".test"));
	test_output << "Test Name : " << test_name.c_str() << "\n";
	test_output << "Statistics ->" << "\n";
	test_output << "Number of tests run : " << results.size() << "\n";
	test_output << "Average time taken in milliseconds : " << average_ms << "\n";
	test_output << "Average time taken in seconds : " << average_seconds << "\n";
	test_output << "Max times taken : " << FindMaxMS() << "ms : " << FindMaxSeconds() << " Seconds."<< "\n\n";
	
	int count = 1;
	for (std::vector<Results_t>::const_iterator it = results.begin(); it!=results.end(); ++it)
	{
		test_output << "Test Number : " << count << "\n";
		test_output << "Time taken in milliseconds : " << (*it).time_taken_ms << "\n";
		test_output << "Time taken in seconds : " << (*it).time_taken_seconds << "\n";
		++count;
	}

	test_output.close();
}

double Profiler::FindMaxMS()
{
	double ms = 0;
	for (size_t i = 0; i < results.size(); ++i)
	{
		if (ms < results[i].time_taken_ms)
			ms = results[i].time_taken_ms;
	}
	return ms;
}

double Profiler::FindMaxSeconds()
{
	double seconds = 0;
	for (size_t i = 0; i < results.size(); ++i)
	{
		if (seconds < results[i].time_taken_seconds)
			seconds = results[i].time_taken_seconds;
	}
	return seconds;
}