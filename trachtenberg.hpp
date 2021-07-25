#include <memory>
#include <string>

// https://en.wikipedia.org/wiki/Trachtenberg_system

class Trachtenberg
{
public:
	Trachtenberg();
	~Trachtenberg();

	virtual std::string const multiply(std::string const& a, std::string const& b) = 0;
	virtual char * multiply(const char* a, const char* b) = 0;
};

class TrachtenbergWikipedia
	: public Trachtenberg
{
public:
	TrachtenbergWikipedia();
	~TrachtenbergWikipedia();

	std::string const multiply(std::string const& a, std::string const& b);
	char * multiply(const char* a, const char* b);
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};
