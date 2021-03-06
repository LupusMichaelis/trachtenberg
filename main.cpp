#include "trachtenberg.hpp"
#include "trachtenberg-inline.hpp"

#include <cassert>
#include <boost/format.hpp>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void test_method(Trachtenberg & method, std::pair<long, long> const & pair);

int main(int args, char *argv[])
{
	std::cout << "Testing Trachtenberg\n";

	TrachtenbergWikipedia wikipedia;
	TrachtenbergLupus lupus;
	TrachtenbergInline inlinable;

	std::vector<std::pair<long, long>> test_data
		{ {11, 11}
		, {155, 11}
		, {155, 1024}
		, {0, 100}
		, {100, 0}
		, {0, 0}
		, {5, 5}
		, {2, 3}
		, {100, 10}
		, {123, 1025}
		, {124, 1025}
		, {1025, 124}
		, {999999, 9999}
		, {999999, 99999999}
		};

	for(const auto &pair: test_data)
		for(const auto & method:
			{ std::ref<Trachtenberg>(wikipedia)
			, std::ref<Trachtenberg>(lupus)
			, std::ref<Trachtenberg>(inlinable)
			,
			})
			test_method(method, pair);
}

void test_method(Trachtenberg & method, std::pair<long, long> const & pair)
{
	std::cout << boost::format("%d * %d = %d Expected: %d \n")
		% pair.first
		% pair.second
		% method.multiply(std::to_string(pair.first), std::to_string(pair.second))
		% (pair.first * pair.second)
		;
	assert(method.multiply(std::to_string(pair.first), std::to_string(pair.second))
			== std::to_string(pair.first * pair.second));

	// XXX Arbitrary size, as this is to be removed eventually. Good enough for testing.
	char first[1024];
	char second[1024];
	std::sprintf(first, "%ld", pair.first);
	std::sprintf(second, "%ld", pair.second);

	assert(method.multiply(first, second) == std::to_string(pair.first * pair.second));
}
