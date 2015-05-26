#include "Client.h"
#include "ComStream.h"
#include "MockStream.h"
#include "MockServer.h"
#include "ResetClient.h"
#include "SetName.h"
#include "CommandQueue.h"
#include <iostream>

void writeTestData()
{
	MockServer server;
	server.WriteSimple(MockStream::GetFileName());
	std::cout << "Press 'enter' to close" << std::endl;
	std::cin.get();
}

void runOnline()
{
	std::unique_ptr<CommandFactory> factory = std::make_unique<CommandFactory>();
	factory->RegisterCommand(ResetClient::Id, std::make_shared<ResetClient>());
	factory->RegisterCommand(SetName::Id, std::make_shared<SetName>());

	Client client(std::make_unique<MockStream>(), std::move(factory), std::make_unique<CommandQueue>());
	client.RunOnline();
	std::cout << "Press 'enter' to close" << std::endl;
	std::cin.get();
}

int main()
{
// genete test data
//	writeTestData();
	runOnline();
	return 0;
}

