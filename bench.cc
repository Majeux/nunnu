// program headers
#include "unnu.h"
// std headers
#include <cstddef>
#include <cstdio>
#include <ostream>
#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <algorithm>
// libraries
#include <cxxopts.hpp>

std::random_device  rand_dev;
std::mt19937        generator(rand_dev());

// cxx arguments
using Arg = std::string;
using ArgList = std::vector<std::string>;

// chrono
using Clock = std::chrono::steady_clock;
using Duration = std::chrono::duration<long, std::ratio<1, 1000000000>>;

bool missing_required_arguments(const cxxopts::ParseResult& result, const ArgList& required, bool silent) {
	bool missing = false;

	for(Arg a : required) {
		if(result[a].count() == 0) {
			if(!silent)
				std::cout << "Argument \'" << a << "\' is required but not provided." << std::endl;

			missing = true;
		}
	}
	
	return missing;
}

// functions to run
enum Function {
	NAIVE, VEC_ALLOC, VEC_PREALLOC, UNNU_OLD, UNNU, N_FUNCTIONS
};

std::string f_name(Function f) {
	switch(f) {
		case NAIVE:
			return "naive";
		case VEC_ALLOC:
			return "vec_alloc";
		case VEC_PREALLOC:
			return "vec_prealloc";
		case UNNU_OLD:
			return "unnu_old";
		case UNNU:
			return "unnu";
		case N_FUNCTIONS:
		default:
			return "unknown";
	}
}

auto run_naive(size_t n, size_t max) {
    auto t1 = Clock::now();

    std::set<uint_fast32_t> s;
	
	for(size_t i = 0; i < n; i++) {
		while( s.insert(generator()%max).second == false ) { }
	}

    auto t2 = Clock::now();

    return t2-t1;
}

auto run_vec_alloc(size_t n, size_t max) {
    auto t1 = Clock::now();

    std::vector<uint_fast32_t> v;
    v.reserve(n);

    for(size_t i = 0; i < max; i++) 
		v.push_back(i);
    
	std::shuffle(v.begin(), v.end(), generator);
    auto t2 = Clock::now();

    return t2-t1;
}

auto run_vec_prealloc(size_t n, size_t max) {
    std::vector <uint_fast32_t> v;
    v.reserve(n);

    for(size_t i = 0; i < max; i++) 
		v.push_back(i);

    auto t1 = Clock::now();
    std::shuffle(v.begin(), v.end(), generator);
    auto t2 = Clock::now();

    return t2-t1;
}

auto run_unnu(size_t n, size_t max) {
    auto t1 = Clock::now();
    std::set<uint_fast32_t> s = Unnu::n_unique_from(generator, n, max);
    auto t2 = Clock::now();

    return t2-t1;
}

auto run_unnuOLD(size_t n, size_t max) {
    auto t1 = Clock::now();
    std::set<uint_fast32_t> s = Unnu::n_unique_fromOLD(generator, n, max);
    auto t2 = Clock::now();

    return t2-t1;
}

// benchmark
Duration TimeZero = Duration::zero();

Duration run_bench(Function f, size_t n, size_t max) {
	switch(f) {
		case NAIVE:
			return run_naive(n, max);
		case VEC_ALLOC:
			return run_vec_alloc(n, max);
		case VEC_PREALLOC:
			return run_vec_prealloc(n, max);
		case UNNU_OLD:
			return run_unnuOLD(n, max);
		case UNNU:
			return run_unnu(n, max);
		case N_FUNCTIONS:
		default:
			std::cout << "ERROR: \'" << f_name(f) << "\' is not a valid function, produces invalid results" << std::endl;
			return TimeZero;
	}
}

void printline(std::ostream &os, bool silent, const std::string &name, const Duration &time) {
	if(silent) {
		os << ", " << time.count();
		return;
	}

	os << std::left << std::setw(15) << name 
	   << "| " <<std::left << std::setw(15) <<  time.count() << std::endl;
}

int main(int argc, char** argv) {
	cxxopts::Options cl_options(argv[0]);

	size_t n = 0;
	size_t max = 0;
	size_t repetitions;	
	bool silent;
	bool super_silent;

	cl_options.add_options()
		("h, help", "Show program arguments.") 
		("n, numbers", "Number of elements to generate. (required)", cxxopts::value(n))
		("m, max-value", "Maximum value to generate. m >= n. (required)", cxxopts::value(max))
		("r, repetitions", "Sample size for each algorithm.", cxxopts::value(repetitions)->default_value("1"))
		("s, silent", "Print only a line of results and values.", cxxopts::value(silent)->default_value("false"))
		("S, super-silent", "Print only a line of values.", cxxopts::value(super_silent)->default_value("false"));

	auto result = cl_options.parse(argc, argv);

	if(result.arguments().size() == 0 || result["help"].as<bool>()) {
		std::cout << cl_options.help() << std::endl;
		return 0;
	}

	if(super_silent)
		silent = true;

	if(missing_required_arguments(result, {"numbers", "max-value"}, silent)) {
		std::cout << "ERROR: Missing arguments, terminating." << std::endl;
		std::cout << cl_options.help() << std::endl;
		return 1;
	}

	if(!silent) { 
		std::cout << "Generating " << n  << " numbers, from [0, " << max << ")" << std::endl;
		std::cout << "Averaging over " << repetitions << " results." << std::endl << std::endl;
	}

	// running benchmarks
	std::array<Duration, Function::N_FUNCTIONS> results;

	for(int f = Function::NAIVE; f < Function::N_FUNCTIONS; f++) {
		results[f] = TimeZero;

		for(size_t i = 0; i < repetitions; i++) {
			results[f] += run_bench(static_cast<Function>(f), n, max);	
		}
	}

	if(silent) {
		if(!super_silent) {
			std::cout << "n, max";
			for(int i = Function::NAIVE; i < Function::N_FUNCTIONS; i++)
				std::cout << ", " << f_name(static_cast<Function>(i));
			std::cout << std::endl;
		}
		std::cout << n << ", " << max;
	}
	else {
		std::cout << std::left << std::setw(15) << "function"
		<< std::setw(15) << "| average duration" << std::endl;
	}

	int i = 0;
	for(Duration &d : results) {
		printline(std::cout, silent, f_name(static_cast<Function>(i)), d);	
		i++;
	}

	std::cout << std::endl;

	return 0;
}
