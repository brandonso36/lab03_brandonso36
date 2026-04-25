all:
	g++ -Wall -std=c++17 intbst.cpp testbst.cpp -o testbst

clean:
	rm -f testbst