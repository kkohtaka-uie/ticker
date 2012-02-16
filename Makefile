.PHONY: ticker

ticker: main.cc
	gcc -o $@ $< -lstdc++
