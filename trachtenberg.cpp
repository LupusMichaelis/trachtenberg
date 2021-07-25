#include "trachtenberg.hpp"

#include <cstddef>
#include <cstring>
#include <memory>
#include <string>
#include <utility>

using std::size_t;
using std::strlen;

struct Trachtenberg::Impl
{
	size_t intermediate;
	char* solution = nullptr;
	char* answer = nullptr;
};

Trachtenberg::Trachtenberg()
	: pimpl{new Impl}
{
}

Trachtenberg::~Trachtenberg()
{
}

void Trachtenberg::multiply(std::string const& a, std::string const& b)
{
	multiply(a.c_str(), b.c_str());
}

void Trachtenberg::multiply(const char* a, const char* b)
{
	size_t large = strlen(a);
	size_t small = strlen(b);
	if (large == 0 || small == 0) {
		pimpl->answer = pimpl->solution = new char[2]{ '0', '\0' };
		return;
	}
	if (large < small) {
		std::swap(a, b);
		std::swap(large, small);
	}
	pimpl->solution = new char[large + small];
	pimpl->answer = pimpl->solution + large + small - 1;
	*pimpl->answer = '\0'; // zero terminate
	size_t digits = 0;
	const char* starta = a + large;
	const char* startb = b + small;
	pimpl->intermediate = 0;
	while (digits != small) {
		multiplystep(++digits, --starta, startb);
	}
	for (size_t d = digits; d != large; ++d) {
		multiplystep(digits, --starta, startb);
	}
	while (digits != 1) {
		multiplystep(--digits, starta, --startb);
	}
	while (pimpl->intermediate) {
		*--pimpl->answer = '0' + pimpl->intermediate % 10;
		pimpl->intermediate /= 10;
	}
}

void Trachtenberg::multiplystep(size_t digits, const char* starta, const char* startb)
{
	const char* digita = starta;
	const char* digitb = startb;
	for (size_t n = 0; n != digits; ++n) {
		--digitb;
		pimpl->intermediate += (*digita - '0') * (*digitb - '0'); // convert from ASCII string
		++digita;
	}
	*--pimpl->answer = '0' + pimpl->intermediate % 10; // convert back to string
	pimpl->intermediate /= 10;
}

std::string const Trachtenberg::result() const
{
	return pimpl->answer;
}

