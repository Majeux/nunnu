warnings = -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic \
					 -Wnull-dereference -Wlogical-op -Wduplicated-branches -Wduplicated-cond

g++compile = g++ -O3 -g $(warnings)

# targets
#
all: unnuun  test

unnuun:
	$(g++compile) -o unnuun main.cc

unnuun20:
	$(g++compile) -o unnuun main.cc

test:
	$(g++compile) -o test test.cc

clean:
	rm -f unnuun test
