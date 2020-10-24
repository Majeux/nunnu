all: unnuun  test

unnuun:
	g++ -O3 -g -Wall -o unnuun main.cc
test:
	g++ -O3 -g -Wall -o test test.cc
clean:
	rm -f unnuun test
