#include "trachtenberg.hpp"

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using std::size_t;
using std::strlen;


struct TrachtenbergLupus::Impl
{
	typedef std::vector<char> digit_vector;
	typedef std::vector<char>::iterator digit_iterator;

	digit_vector large;
	digit_vector small;

	digit_vector solution;
	digit_iterator solution_end;

	size_t intermediate;

	void multiply();
	void multiplystep(size_t digits, digit_iterator starta, digit_iterator small_it);

	static
	void from_string(digit_vector & digit_representation, std::string const & ascii_representation)
	{
		digit_representation.resize(ascii_representation.length());
		std::transform
			( ascii_representation.cbegin()
			, ascii_representation.cend()
			, digit_representation.begin()
			, [] (std::string::value_type const & ascii) { return ascii - '0'; }
			);
	}

	static
	void to_string(std::string & ascii_representation, digit_vector digit_representation)
	{
		while(digit_representation.size() > 1 && 0 == digit_representation.front())
			digit_representation.erase(digit_representation.begin());

		ascii_representation.resize(digit_representation.size());
		std::transform
			( digit_representation.cbegin()
			, digit_representation.cend()
			, ascii_representation.begin()
			, [] (std::string::value_type const & ascii) { return ascii + '0'; }
			);
	}
};

TrachtenbergLupus::TrachtenbergLupus()
	: Trachtenberg {}
	, pimpl{new Impl}
{
}

TrachtenbergLupus::~TrachtenbergLupus()
{
}

std::string const TrachtenbergLupus::multiply(std::string large, std::string small)
{
	if (large.length() == 0 || small.length() == 0)
		return "0";

	pimpl.reset(new Impl);

	if(large.length() < small.length())
		std::swap(large, small);

	Impl::from_string(pimpl->large, large);
	Impl::from_string(pimpl->small, small);

	pimpl->multiply();

	std::string result;
	Impl::to_string(result, pimpl->solution);

	return result;
}

void TrachtenbergLupus::Impl::multiply()
{
	solution.resize(large.size() + small.size());
	solution_end = std::end(solution);

	digit_iterator large_it = large.end();
	digit_iterator small_it = small.end();

	intermediate = 0;

	size_t digits = 0;
	while(digits != small.size())
		multiplystep(++digits, --large_it, small_it);

	for(size_t d = digits; d != large.size(); ++d)
		multiplystep(digits, --large_it, small_it);

	while(digits != 1)
		multiplystep(--digits, large_it, --small_it);

	while(intermediate)
	{
		*--solution_end = intermediate % 10;
		intermediate /= 10;
	}
}

void TrachtenbergLupus::Impl::multiplystep(size_t digits, digit_iterator large_it, digit_iterator small_it)
{
	for(size_t n = 0; n != digits; ++n)
	{
		--small_it;
		intermediate += *large_it * *small_it;
		++large_it;
	}

	*--solution_end = intermediate % 10;
	intermediate /= 10;
}
