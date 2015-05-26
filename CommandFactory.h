#ifndef CommandFactory_h
#define CommandFactory_h

#include "ICommand.h"
#include <map>

/**
@brief factory for command
@detailed
*/
class CommandFactory
{
private:
	std::map<int16_t, PtrCommandHandler> _commandTemplates;					/**< template for handle command */
public:
	CommandFactory();
	~CommandFactory();
	/**
	@brief Register command in template dictionary
	@param type - 2 byte type command
	@param commandHandler - template for command handler 
	@return -1, if such command already exist; 
			 0, if ok
	*/
	int RegisterCommand(int16_t type, PtrCommandHandler commandHandler);
	
	/**
	@brief Create command
	@param bytes - stream with command data
	@param offset - current position in stream
	@return nullptr, if unknown command
	*/
	PtrCommandHandler BuildCommand(const char * bytes, unsigned long& offset);
};

#endif