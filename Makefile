
include .env

YEAR = 2024
FLAGS = -O2 -g
TEMPLATE = template.cpp

DEBUG=0
FLAGS += -DDEBUG=$(DEBUG)

all: day$(DAY).cpp
	@echo "=== Compiling day$(DAY).cpp ==="
	c++ -std=c++17 $(FLAGS) day$(DAY).cpp -o aoc
	@echo "=== Running day $(DAY) ==="
	/usr/bin/time -f "%E" ./aoc input.txt
# 	time ./aoc input.txt

clean:
	rm input.txt aoc 

day%.cpp:
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

set-%:
	@if grep -q "^$*=" .env; then \
		sed -i "s/^$*=.*/$*=$${$*}/" .env; \
	else \
		echo "$*=$${$*}" >> .env; \
	fi

.PHONY: init input