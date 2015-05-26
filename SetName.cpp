#include "SetName.h"

#include <assert.h> 

#include "Print.h"
#include "Client.h"
#include "Utils.h"

SetName::SetName()
{
}

SetName::SetName(std::string name) :_newName(name)
{
}

SetName::~SetName()
{
}

int SetName::Execute(Client* client)
{
	print("Set client name start\n");
	client->SetName(_newName);
	return 0;
}

PtrCommandHandler SetName::Clone() const
{
	return std::make_shared<SetName>(*this);
}

size_t SetName::WriteData(std::string& bytes)
{
	size_t size = sizeof(int16_t) + sizeof(int16_t) + sizeof(uint8_t) + (_newName.size() + 1) * sizeof(char) + sizeof(uint32_t); // id + body size + body + crc32
	bytes.resize(size, ' ');
	int16_t bodySize = sizeof(uint8_t) + (_newName.size() + 1)  * sizeof(char);

	char * pbytes = &*bytes.begin();
	unsigned long offset = 0;
	WriteType(pbytes, Id, offset); // write id command
	WriteType(pbytes, bodySize, offset); // write bodySize 

	uint8_t sizeStr = _newName.size() + 1;
	assert(UCHAR_MAX > sizeStr); // assert name client < 255 
	WriteType(pbytes, sizeStr, offset); // write size new name 
	WriteType(pbytes, _newName.c_str(), offset, sizeStr); // write new name 

	uint32_t crc = crc32(StartWord, pbytes, offset);
	WriteType(pbytes, crc, offset); // write crc32

	return size;
}

int SetName::parseBody(const char * bodyBytes, unsigned long bodySize)
{
	if (bodySize <= 0)
	{
		print("SetName: Incorrect size of body command\n");
		return -1;
	}

	unsigned long offset = 0;

	uint8_t nameSize = 0;
	ReadType(nameSize, bodyBytes, offset);

	if (nameSize > 0)
	{
		char * name = new char[nameSize];
		ReadType(name, bodyBytes, offset, nameSize);

		_newName = std::string(name);

		delete[]name;
	}
	else
		_newName = "";

	return 0;
}