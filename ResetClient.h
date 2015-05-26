#ifndef ResetClient_h
#define ResetClient_h

#include "ICommand.h"
#include <string>

class ResetClient : public ICommand
{
protected:
	virtual int parseBody(const char * bodyBytes, unsigned long bodySize) override;
public:
	ResetClient();
	virtual ~ResetClient();
	virtual int Execute(Client* client) override;
	virtual size_t WriteData(std::string& bytes) override;
	virtual PtrCommandHandler Clone() const override;

	static const int16_t	Id = 1;
};

#endif

