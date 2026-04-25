



# Makefile for ppca-5b project

CXX = g++-13
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic
LDFLAGS = 

# Build targets
all: cheat anticheat

cheat: cheat-submit.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o cheat $<
	ln -sf cheat code

anticheat: anticheat-submit.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o anticheat $<
	ln -sf anticheat code

clean:
	rm -f cheat anticheat code *.o

.PHONY: all clean



