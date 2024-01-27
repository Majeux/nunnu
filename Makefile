warnings = -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic \
					 -Wnull-dereference -Wlogical-op -Wduplicated-branches -Wduplicated-cond

g++compile = g++ -O3 -g $(warnings)

# targets
#
unnuun20:
	$(g++compile) -std=c++20 -o unnuun cpp20/main.cc

unnuun14:
	$(g++compile) -std=c++14 -o unnuun cpp20/main.cc

test:
	$(g++compile) -o test test.cc

clean:
	rm -f unnuun test
