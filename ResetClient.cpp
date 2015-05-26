#include "ResetClient.h"

#include "Print.h"
#include "Client.h"
#include "Utils.h"

ResetClient::ResetClient()
{
}


ResetClient::~ResetClient()
{
}

size_t ResetClient::WriteData(std::string& bytes)
{
	size_t size = sizeof(int16_t) + sizeof(int16_t) + sizeof(uint32_t); // size id + size body size + crc32
	bytes.resize(size, ' ');
	int16_t bodySize = 0; //body size always = 0

	char * pbytes = &*bytes.begin();
	memcpy(pbytes, &Id, sizeof(int16_t)); // write id command
	memcpy(pbytes + sizeof(int16_t), &bodySize, sizeof(int16_t)); // write bodySize 

	uint32_t crc = crc32(StartWord, pbytes, sizeof(int16_t) + sizeof(int16_t));
	memcpy(pbytes + sizeof(int16_t) + sizeof(int16_t), &crc, sizeof(uint32_t)); // write crc32

	return size;
}

int ResetClient::parseBody(const char * bodyBytes, unsigned long bodySize)
{
	return 0;
}

int ResetClient::Execute(Client* client)
{
	print("Reset client command start \n");
	client->Reset();
	return 0;
}

PtrCommandHandler ResetClient::Clone() const
{
	return std::make_shared<ResetClient>(*this);
}
