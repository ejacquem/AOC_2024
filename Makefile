
include .env

YEAR = 2024
FLAGS = -O2 -g
TEMPLATE = template.cpp

day%:
	@echo "=== Compiling day$*.cpp ==="
	c++ -std=c++17 $(FLAGS) day$*.cpp -o aoc
	@echo "=== Running day $* ==="
	/usr/bin/time -f "%E" ./aoc input.txt

clean:
	rm input.txt aoc 

init%:
	@if [ -f day$*.cpp ]; then \
		echo "day$*.cpp already exists! Aborting."; \
		exit 1; \
	else \
		cp $(TEMPLATE) day$*.cpp; \
		echo "Created day$*.cpp from $(TEMPLATE)"; \
	fi

input%:
	@echo "=== Fetching input for day $* ==="
	curl -s -H "Cookie: session=$(SESSION)" https://adventofcode.com/$(YEAR)/day/$*/input -o input.txt

.PHONY: init input