#ifndef SetName_h
#define SetName_h

#include "ICommand.h"
#include <string>

class SetName : public ICommand
{
private:
	std::string				_newName;
protected:
	virtual int parseBody(const char * bodyBytes, unsigned long bodySize) override;
public:
	SetName();
	SetName(std::string name);
	virtual ~SetName();
	virtual int Execute(Client* client) override;
	virtual size_t WriteData(std::string& bytes) override;
	virtual PtrCommandHandler Clone() const override;

	static const int16_t	Id = 2;
};

#endif

