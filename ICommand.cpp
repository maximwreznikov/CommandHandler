#include "ICommand.h"

#include "Print.h"
#include "Utils.h"

ICommand::ICommand()
{
}


ICommand::~ICommand()
{
}

int ICommand::ReadData(const char * bytes, unsigned long& offset)
{
	unsigned long startOffset = offset;
	int16_t id = 0;
	ReadType(id, bytes, offset);

	int16_t bodySize = 0;
	ReadType(bodySize, bytes, offset);

	//read command body
	char * bodyBytes = nullptr;
	if (bodySize > 0)
	{
		bodyBytes = new char[bodySize];
		ReadType(bodyBytes, bytes, offset, bodySize);
	}

	if (parseBody(bodyBytes, bodySize) < 0)
		return -2;

	//check crc
	uint32_t crc = 0;
	ReadType(crc, bytes, offset);

	uint32_t newCrc = crc32(StartWord, bytes + startOffset, offset - startOffset - sizeof(uint32_t));
	if (newCrc != crc)
	{
		print("Error: crc32 in command ", id, "\n");
		return -1;
	}

	return 0;
}