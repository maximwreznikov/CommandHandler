#include "ComStream.h"

#include "Print.h"


ComStream::ComStream()
{
}


ComStream::~ComStream()
{
}

int ComStream::OpenStream()
{
	_serialHandle = ::CreateFile(PortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (_serialHandle == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			print("serial port does not exist.\n");
			return -1;
		}
		print("Some other error occurred.\n");
		return -2;
	}


	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(_serialHandle, &dcbSerialParams))
	{
		print("Getting state error\n");
		return -3;
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(_serialHandle, &dcbSerialParams))
	{
		print("Error setting serial port state\n");
		return -4;
	}

	return 0;
}

void ComStream::CloseStream()
{
	::CloseHandle(_serialHandle);
}

unsigned long ComStream::ReadData(char * buffer, unsigned long maxSize)
{
	unsigned long size = 0;
	::ReadFile(_serialHandle, buffer, maxSize, &size, nullptr);

	if (size > 0) print("Stream from com:",buffer);

	return size;
}

int ComStream::WriteData()
{
	char data[] = "Hello from C++";
	DWORD dwSize = sizeof(data);
	DWORD dwBytesWritten;
	LPOVERLAPPED ov;

	BOOL iRet = ::WriteFile(_serialHandle, data, dwSize, &dwBytesWritten, NULL);

	print(dwSize, " Bytes in string. ", dwBytesWritten, " Bytes sended. \n");

	return 0;
}
