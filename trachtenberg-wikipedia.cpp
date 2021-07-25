#include "trachtenberg.hpp"

#include <cstddef>
#include <cstring>
#include <memory>
#include <string>
#include <utility>

struct TrachtenbergWikipedia::Impl
{
	std::size_t intermediate;
	char* solution = nullptr;
	char* answer = nullptr;

	void multiplystep(std::size_t digits, const char* starta, const char* startb);
};

TrachtenbergWikipedia::TrachtenbergWikipedia()
	: Trachtenberg {}
	, pimpl{new Impl}
{
}

TrachtenbergWikipedia::~TrachtenbergWikipedia()
{
}

std::string const TrachtenbergWikipedia::multiply(std::string a, std::string b)
{
	return multiply(a.c_str(), b.c_str());
}

char * TrachtenbergWikipedia::multiply(const char* a, const char* b)
{
	std::size_t large = std::strlen(a);
	std::size_t small = std::strlen(b);
	if (large == 0 || small == 0) {
		pimpl->answer = pimpl->solution = new char[2]{ '0', '\0' };
		return pimpl->answer;
	}
	if (large < small) {
		std::swap(a, b);
		std::swap(large, small);
	}
	pimpl->solution = new char[large + small];
	pimpl->answer = pimpl->solution + large + small - 1;
	*pimpl->answer = '\0'; // zero terminate
	std::size_t digits = 0;
	const char* starta = a + large;
	const char* startb = b + small;
	pimpl->intermediate = 0;
	while (digits != small) {
		pimpl->multiplystep(++digits, --starta, startb);
	}
	for (std::size_t d = digits; d != large; ++d) {
		pimpl->multiplystep(digits, --starta, startb);
	}
	while (digits != 1) {
		pimpl->multiplystep(--digits, starta, --startb);
	}
	while (pimpl->intermediate) {
		*--pimpl->answer = '0' + pimpl->intermediate % 10;
		pimpl->intermediate /= 10;
	}

	return pimpl->answer;
}

void TrachtenbergWikipedia::Impl::multiplystep(std::size_t digits, const char* starta, const char* startb)
{
	const char* digita = starta;
	const char* digitb = startb;
	for (std::size_t n = 0; n != digits; ++n) {
		--digitb;
		intermediate += (*digita - '0') * (*digitb - '0'); // convert from ASCII string
		++digita;
	}
	*--answer = '0' + intermediate % 10; // convert back to string
	intermediate /= 10;
}
