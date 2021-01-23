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
#include <algorithm>
// libraries
#include <cxxopts.hpp>

std::random_device  rand_dev;
std::mt19937        generator(rand_dev());

using Arg = std::string;
using ArgList = std::vector<std::string>;

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

int main(int argc, char** argv) {
	cxxopts::Options cl_options(argv[0]);

	size_t n = 0;
	size_t max = 0;
	size_t repetitions;	
	bool silent;

	cl_options.add_options()
		("h, help", "Show program arguments.") 
		("n, numbers", "Number of elements to generate. (required)", cxxopts::value(n))
		("m, max-value", "Maximum value to generate. m >= n. (required)", cxxopts::value(max))
		("r, repetitions", "Sample size for each algorithm.", cxxopts::value(repetitions)->default_value("1"))
		("s, silent", "Only print bench results.", cxxopts::value(silent)->default_value("false"));

	auto result = cl_options.parse(argc, argv);

	if(result.arguments().size() == 0 || result["help"].as<bool>()) {
		std::cout << cl_options.help() << std::endl;
		return 0;
	}

	if(missing_required_arguments(result, {"numbers", "max-value"}, silent)) {
		std::cout << "ERROR: Missing arguments, terminating." << std::endl;
		std::cout << cl_options.help() << std::endl;
		return 1;
	}

	if(!silent) { 
		std::cout << "Generating " << n  << " numbers, from [0, " << max << ")" << std::endl << std::endl;
	}

	return 0;
}
