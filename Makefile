all: unnuun test bench

unnuun:
	g++ -O3 -g -Wall -o unnuun main.cc
test:
	g++ -O3 -g -Wall -o test test.cc
bench:
	g++ -O3 -g -Wall -o bench bench.cc
clean:
	rm -f unnuun test bench
