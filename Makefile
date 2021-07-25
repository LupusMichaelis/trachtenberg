.PHONY: clean test

SRCS=\
	trachtenberg.cpp\
	main.cpp

OBJS=$(SRCS:.cpp=.o)

CXXFLAGS=-Wall -pedantic

test: trachtenberg
	./trachtenberg

trachtenberg: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

clean:
	-rm -rf $(OBJS) trachtenberg
