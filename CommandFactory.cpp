#include "CommandFactory.h"

#include "Print.h"

CommandFactory::CommandFactory()
{
}


CommandFactory::~CommandFactory()
{
}

int CommandFactory::RegisterCommand(__int16 type, PtrCommandHandler commandHandler)
{
	if (_commandTemplates[type] != nullptr) return -1;

	_commandTemplates[type] = commandHandler;
	return 0;
}

PtrCommandHandler CommandFactory::BuildCommand(const char * bytes, unsigned long& offset)
{
	int16_t id = 0;
	memcpy(&id, bytes + offset, sizeof(int16_t));

	PtrCommandHandler commandTemplate = _commandTemplates[id];
	if (commandTemplate == nullptr)
	{
		print("Unknown command");
		return nullptr;
	}

	PtrCommandHandler newCommandPtr = commandTemplate->Clone();

	if(newCommandPtr->ReadData(bytes, offset) < 0)
		return nullptr;
	
	return newCommandPtr;
}
