#include "CommandQueue.h"


CommandQueue::CommandQueue(bool await) :_await(true),
									    _mutex(),
									    _condition(),
									    _commandQueue()
{
}

CommandQueue::~CommandQueue()
{
}

void CommandQueue::PushCommand(PtrCommandHandler command)
{
	if (command == nullptr)
		return;

	std::unique_lock<std::mutex> lock(_mutex);
	_commandQueue.push(command);
	lock.unlock();
	_condition.notify_one();
}

PtrCommandHandler CommandQueue::PopCommand()
{
	std::unique_lock<std::mutex> lock(_mutex);
	while (_commandQueue.empty() && _await)
	{
		_condition.wait(lock);
	}

	if (_commandQueue.empty())
		return nullptr;
	
	PtrCommandHandler command = _commandQueue.front();
	_commandQueue.pop();

	return command;
}

void CommandQueue::Clear()
{
	std::lock_guard<std::mutex> lock(_mutex);
	std::queue<PtrCommandHandler> empty;
	std::swap(_commandQueue, empty);
}

void CommandQueue::StartAwaiting()
{
	_await = true;
}

void CommandQueue::CancelAwaiting()
{
	_await = false;
	_condition.notify_one();
}
