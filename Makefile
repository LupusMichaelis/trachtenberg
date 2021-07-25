.PHONY: clean

SRCS=\
	trachtenberg.cpp\
	main.cpp

OBJS=$(SRCS:.cpp=.o)

CXXFLAGS=-Wall -pedantic

trachtenberg: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

clean:
	-rm -rf $(OBJS) trachtenberg
