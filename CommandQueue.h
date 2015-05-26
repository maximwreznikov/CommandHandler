#ifndef SmartQueue_h
#define SmartQueue_h

#include "ICommand.h"
#include <queue>
#include <condition_variable>
#include "CommandContainer.h"

/**
@brief thread safety queue
@detailed
*/
class CommandQueue : public CommandContainer
{
private:
	volatile bool						_await;				/**< await command, when _commandQueue empty  */
	mutable std::mutex					_mutex;				/**< mutex for thread safe  */
	std::condition_variable				_condition;
	std::queue<PtrCommandHandler>		_commandQueue;
public:
	/**
	@brief Constructor
	@param await - await new command
	*/
	CommandQueue(bool await = true);
	~CommandQueue();
	virtual void PushCommand(PtrCommandHandler command) override;
	virtual PtrCommandHandler PopCommand() override;
	virtual void Clear() override;
	/**
	@brief start awaiting
	@detailed set _await = true
	*/
	virtual void StartAwaiting() override;
	/**
	@brief cancel awaiting
	@detailed set _await = false, notify _condition
	*/
	virtual void CancelAwaiting() override;

};

#endif