all: unnuun  test

unnuun:
	g++ -O3 -g -Wall -Werror -o unnuun main.cc
test:
	g++ -O3 -g -Wall -Werror -o test test.cc
clean:
	rm -f unnuun test
