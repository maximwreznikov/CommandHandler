#include "Client.h"

#include <iostream>
#include "Print.h"
#include <Windows.h>
#include <thread>

Client::Client(std::unique_ptr<DataStream> dataSource, 
			   std::unique_ptr<CommandFactory> commandFactory,
			   std::unique_ptr<CommandContainer> commandContainer) :
								_dataSource(std::move(dataSource)),
								_commandFactory(std::move(commandFactory)),
								_commands(std::move(commandContainer))
{	
}


Client::~Client()
{
}

void commandProcessing(const volatile bool& processCommand, Client * client, CommandContainer * queue)
{
	while (processCommand)
	{
		auto command = queue->PopCommand();
		if (command != nullptr)
		{
			command->Execute(client);
			command = nullptr;
		}
		print("\n===== Execute processing =====\n");
	}
}

bool AreEqual(int32_t marker, char *data)
{
	//int32_t test = 0;
	//memcpy(&test, data, sizeof(int32_t));
	return std::memcmp(&marker, data, sizeof(int32_t)) == 0;
}

void Client::RunOnline()
{
	volatile bool processCommand = true;
	std::thread commandThread(commandProcessing, std::cref(processCommand), this, _commands.get());

	char *	buffer = new char[bufferSize];
	_dataSource->OpenStream();
	print("=====  Start processing  =====\n");
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		std::chrono::milliseconds dura(1000);
		std::this_thread::sleep_for(dura);

		int length = bufferSize;

		length = _dataSource->ReadData(buffer, bufferSize);
		print("Read ", length, " bytes\n");

		unsigned long offset = 0;
		if (length > sizeof(magicalNamber))
		{
			while (offset < length - sizeof(magicalNamber))
			{
				if (AreEqual(magicalNamber, buffer + offset))
				{
					offset += sizeof(int32_t);
					auto command = _commandFactory->BuildCommand(buffer, offset);
					_commands->PushCommand(command);
				}
				else
				{
					offset++;
				}
			}
		}

		print("\n==============================\n");
	}

	delete[] buffer;
	_dataSource->CloseStream();

	processCommand = false;
	_commands->CancelAwaiting();

	commandThread.join();
	
}

void Client::SetName(const std::string& newName)
{
	_name.assign(newName);
	print("New client name - ", newName);
}

void Client::Reset()
{
	print("Reset client comleted \n");
	_name.assign("");
//TODO: maybe need clear command queue
//_commands->Clear();
}