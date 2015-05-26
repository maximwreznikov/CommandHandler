#ifndef MockServer_h
#define MockServer_h
#include <string>

class MockServer
{
public:
	MockServer();
	~MockServer();
	void WriteSimple(std::string fileName);
};

#endif
