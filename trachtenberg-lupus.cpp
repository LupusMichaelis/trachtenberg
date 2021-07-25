#include "trachtenberg.hpp"

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

static
void from_string(std::vector<char> & digit_representation, std::string const & ascii_representation)
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
void to_string(std::string & ascii_representation, std::vector<char> const & digit_representation)
{
	// Where all digits are 0
	if(std::all_of
		( digit_representation.cbegin()
		, digit_representation.cend()
		, [] (auto const & value) { return 0 == value; }))
	{
		ascii_representation = "0";
		return;
	}

	// Handle leading zeroes
	auto from = std::find_if
		( digit_representation.cbegin()
		, digit_representation.cend()
		, [] (auto const & value) { return 0 != value; }
		);

	if(digit_representation.cend() == from)
		from = digit_representation.cbegin();

	ascii_representation.resize(digit_representation.size() - std::distance(digit_representation.cbegin(), from));
	std::transform
		( from
		, digit_representation.cend()
		, ascii_representation.begin()
		, [] (std::string::value_type const & raw) { return raw + '0'; }
		);
}

struct TrachtenbergLupus::Impl
{
	typedef std::vector<char> digit_vector;
	typedef digit_vector::iterator digit_iterator;

	digit_vector large;
	digit_vector small;

	digit_vector solution;
	digit_iterator solution_end;

	std::size_t intermediate;

	void multiply();
	void multiplystep(std::size_t arrow, digit_iterator starta, digit_iterator small_it);
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
	pimpl.reset(new Impl);

	if(large.length() < small.length())
		std::swap(large, small);

	from_string(pimpl->large, large);
	from_string(pimpl->small, small);

	pimpl->multiply();

	std::string result;
	to_string(result, pimpl->solution);

	return result;
}

void TrachtenbergLupus::Impl::multiply()
{
	solution.resize(large.size() + small.size());
	solution_end = std::end(solution);

	digit_iterator large_it = large.end();
	digit_iterator small_it = small.end();

	intermediate = 0;

	std::size_t first_arrow = 0;
	while(first_arrow != small.size())
	{
		++first_arrow, --large_it;
		multiplystep(first_arrow, large_it, small_it);
	}

	for(std::size_t second_arrow = first_arrow; second_arrow != large.size(); ++second_arrow)
	{
		--large_it;
		multiplystep(first_arrow, large_it, small_it);
	}

	while(first_arrow != 1)
	{
		--first_arrow, --small_it;
		multiplystep(first_arrow, large_it, small_it);
	}

	while(intermediate)
	{
		*--solution_end = intermediate % 10;
		intermediate /= 10;
	}
}

void TrachtenbergLupus::Impl::multiplystep(std::size_t pivot_arrow, digit_iterator large_it, digit_iterator small_it)
{
	for(std::size_t arrow = 0; arrow != pivot_arrow; ++arrow)
	{
		--small_it;
		intermediate += *large_it * *small_it;
		++large_it;
	}

	*--solution_end = intermediate % 10;
	intermediate /= 10;
}
