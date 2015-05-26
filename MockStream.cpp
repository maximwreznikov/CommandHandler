#include "MockStream.h"

#include <assert.h> 

MockStream::MockStream()
{
}


MockStream::~MockStream()
{
}

int MockStream::OpenStream()
{
	_file.open(GetFileName(), std::ios::binary | std::ios::in);
	return 0;
}

void MockStream::CloseStream()
{
	_file.close();
}

unsigned long MockStream::ReadData(char * buffer, unsigned long maxSize)
{
	if (!_file.is_open())
		return 0;

	unsigned long curr = _file.tellg();
	_file.seekg(0, _file.end);
	unsigned long size = _file.tellg();
	_file.seekg(curr);
	size = size - curr;
	size = size > maxSize ? maxSize : size;

	// read data as a block:

	_file.read(buffer, size);
	return size;
}

int MockStream::WriteData()
{
	return 0;
}
