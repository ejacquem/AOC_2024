
include .env

DAY = 7
YEAR = 2024
FLAGS = -O2 -g
TEMPLATE = template.cpp

all:
	@echo "=== Compiling day$(DAY).cpp ==="
	c++ -std=c++17 $(FLAGS) day$(DAY).cpp -o aoc
	@echo "=== Running day $(DAY) ==="
	/usr/bin/time -f "%E" ./aoc input.txt
# 	time ./aoc input.txt

clean:
	rm input.txt aoc 

init:
	@if [ -f day$(DAY).cpp ]; then \
		echo "day$(DAY).cpp already exists! Aborting."; \
		exit 1; \
	else \
		cp $(TEMPLATE) day$(DAY).cpp; \
		echo "Created day$(DAY).cpp from $(TEMPLATE)"; \
	fi

input:
	@echo "=== Fetching input for day $(DAY) ==="
	curl -s -H "Cookie: session=$(SESSION)" https://adventofcode.com/$(YEAR)/day/$(DAY)/input -o input.txt

.PHONY: init input