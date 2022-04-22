all: guesser

guesser: tidy
	g++ ./src/main.cpp -o ./bin/guesser

tidy:
	clang-tidy-12 -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus* ./src/main.cpp --

clean:
	rm ./bin/guesser

run: guesser
	./bin/guesser