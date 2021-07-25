#include <memory>
#include <string>

// https://en.wikipedia.org/wiki/Trachtenberg_system
class Trachtenberg
{
public:
	Trachtenberg();
	~Trachtenberg();

	void multiply(std::string const& a, std::string const& b)
	{
		multiply(a.c_str(), b.c_str());
	}

	void multiply(const char* a, const char* b);
	std::string const result() const;
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;

	void multiplystep(size_t digits, const char* starta, const char* startb);
};
