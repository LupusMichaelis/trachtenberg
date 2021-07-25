#include "trachtenberg.hpp"

#include <iostream>
#include <cassert>
#include <string>
#include <utility>

int main(int args, char *argv[])
{
	std::cout << "Testing Trachtenberg\n";

	Trachtenberg method;

	method.multiply(std::string("11"), std::string("11"));
	assert(method.result() == std::to_string(11*11));

	method.multiply("11", "11");
	assert(method.result() == std::to_string(11*11));
}
