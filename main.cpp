#include "trachtenberg.hpp"

#include <iostream>
#include <cassert>
#include <string>
#include <utility>

int main()
{
	std::cout << "Testing Trachtenberg\n";

	Trachtenberg method;

	method.multiply("11", "11");
	assert(method.result() == std::to_string(11*11));
}
