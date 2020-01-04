all: find compile

compile:
	g++ -std=c++14 @sources.txt -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread

find:
	find -name "*.cpp" > sources.txt

run:
	./a.out fly.txt

runFunc:
	./a.out fly_with_func.txt