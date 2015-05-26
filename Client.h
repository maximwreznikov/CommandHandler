#ifndef Client_h
#define Client_h
#include "DataStream.h"
#include <memory>
#include <string>
#include "MockStream.h"
#include "CommandContainer.h"
#include "CommandQueue.h"
#include "CommandFactory.h"

/**
@brief our client
@detailed
@notify supposed that all command have size < than bufferSize, 
and no hanging command(server know our buffer size and not write command with start in one buffer, and end in another buffer)
*/

class Client
{
private:
	const unsigned long						bufferSize = 255;				/**< buffer size */
	const int32_t							magicalNamber = 0xDEADBEAF;		/**< magic number, start command */
	
	std::string								_name;							/**< client name */

	std::unique_ptr<DataStream>				_dataSource;					/**< data source */
	std::unique_ptr<CommandFactory>			_commandFactory;				/**< command factory */
	std::unique_ptr<CommandContainer>		_commands;							/**< thread safe command queue */
	
public:
	Client(std::unique_ptr<DataStream> dataSource, 
		   std::unique_ptr<CommandFactory> commandFactory,
		   std::unique_ptr<CommandContainer> commandContainer);

	~Client();
	/**
	@brief Main function for processing command
	*/
	void RunOnline();
	void SetName(const std::string& newName);
	void Reset();
};

#endif
