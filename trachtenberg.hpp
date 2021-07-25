#include <memory>
#include <string>

// https://en.wikipedia.org/wiki/Trachtenberg_system
class Trachtenberg
{
public:
	Trachtenberg();
	~Trachtenberg();

	std::string const multiply(std::string const& a, std::string const& b);
	char * multiply(const char* a, const char* b);
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};
