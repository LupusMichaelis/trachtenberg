#include <memory>
#include <string>

// https://en.wikipedia.org/wiki/Trachtenberg_system

class Trachtenberg
{
public:
	Trachtenberg();
	~Trachtenberg();

	virtual std::string const multiply(std::string a, std::string b) = 0;
	virtual char * multiply(const char* a, const char* b) = 0;
};

class TrachtenbergWikipedia
	: public Trachtenberg
{
public:
	TrachtenbergWikipedia();
	~TrachtenbergWikipedia();

	std::string const multiply(std::string a, std::string b);
	char * multiply(const char* a, const char* b);
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};

class TrachtenbergLupus
	: public Trachtenberg
{
public:
	TrachtenbergLupus();
	~TrachtenbergLupus();

	std::string const multiply(std::string a, std::string b);
	char * multiply(const char* a, const char* b);
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};
