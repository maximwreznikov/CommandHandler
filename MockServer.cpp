#include "MockServer.h"

#include <fstream>
#include <cinttypes>
#include <vector>
#include "ICommand.h"
#include "SetName.h"
#include "ResetClient.h"

MockServer::MockServer()
{
}


MockServer::~MockServer()
{
}

void MockServer::WriteSimple(std::string fileName)
{
	int32_t magicalNumber = 0xDEADBEAF;
	std::ofstream out(fileName, std::ios::binary | std::ios::out);

	std::vector<PtrCommandHandler> test_commands = { std::make_shared<SetName>("my_client"), std::make_shared<ResetClient>(),
		std::make_shared<SetName>("321"), std::make_shared<ResetClient>(), std::make_shared<SetName>("123") };

	char * magicalBytes = new char[sizeof(int32_t)];
	memcpy(magicalBytes, &magicalNumber, sizeof(int32_t));

	for (auto command : test_commands)
	{
		std::string bytes;
		size_t size;
		size = command->WriteData(bytes);

		out.write(magicalBytes, sizeof(int32_t)); // write magic bytes
		out.write(&*bytes.begin(), size); // write command data
	}	
		
	out.close();
}
