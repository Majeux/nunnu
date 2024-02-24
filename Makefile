warnings = -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wnull-dereference

g++compile = clang++ -O3 -g $(warnings)

# targets
#
nunnu20:
	@echo "compiling nunnu with c++20..."
	$(g++compile) -std=c++20 -o nunnu20 cpp20/main.cc
	@echo "done.\n"

nunnu14:
	@echo "compiling nunnu with c++14..."
	$(g++compile) -std=c++14 -o nunnu14 cpp14/main.cc
	@echo "done.\n"

benchmark20:
	@echo "compiling nunnu benchmark with c++20..."
	$(g++compile) -std=c++20 -o benchmark20 cpp20/benchmark.cc
	@echo "done.\n"

benchmark14:
	@echo "compiling nunnu benchmark with c++14..."
	$(g++compile) -std=c++14 -o benchmark14 cpp14/benchmark.cc
	@echo "done.\n"

all: nunnu20 nunnu14 benchmark20 benchmark14

clean:
	rm -f nunnu20 nunnu14 benchmark20 benchmark14
