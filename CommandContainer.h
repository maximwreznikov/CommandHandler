#ifndef CommandContainer_h
#define CommandContainer_h
#include "ICommand.h"

class CommandContainer
{
public:
	CommandContainer(){}
	virtual ~CommandContainer(){}
	virtual void PushCommand(PtrCommandHandler command) = 0;
	virtual PtrCommandHandler PopCommand() = 0;
	virtual void Clear() = 0;
	virtual void CancelAwaiting() = 0;
	virtual void StartAwaiting() = 0;
};

#endif
