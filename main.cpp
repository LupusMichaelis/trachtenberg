#include "trachtenberg.hpp"

#include <iostream>
#include <cassert>
#include <string>
#include <utility>
#include <vector>

int main(int args, char *argv[])
{
	std::cout << "Testing Trachtenberg\n";

	TrachtenbergWikipedia method;

	std::vector<std::pair<int, int>> test_data
		{ {11, 11}
		, {155, 11}
		, {155, 1024}
		};

	for(const auto &pair: test_data)
	{
		assert(method.multiply(std::to_string(pair.first), std::to_string(pair.second))
				== std::to_string(pair.first * pair.second));

		// XXX Arbitrary size, as this is to be removed eventually. Good enough for testing.
		char first[1024];
		char second[1024];
		std::sprintf(first, "%d", pair.first);
		std::sprintf(second, "%d", pair.second);

		assert(method.multiply(first, second) == std::to_string(pair.first * pair.second));
	}
}
