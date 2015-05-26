#ifndef ComInterface_h
#define ComInterface_h

#include "DataStream.h"

#include <Windows.h>

/**
@brief class for read data from com port
@detailed
*/
class ComStream : public DataStream
{
private:
	const LPCTSTR	PortName = L"COM1";
	HANDLE			_serialHandle;
public:
	ComStream();
	virtual ~ComStream();
	/**
	@brief Open com port
	@return 0, if ok, negative, if some error occured
	*/
	virtual int OpenStream() override;
	virtual void CloseStream() override;
	/**
	@brief Read data from com port
	@param buffer - buffer to read
	@param maxSize - size of buffer
	@return size of read bytes
	*/
	virtual unsigned long ReadData(char * buffer, unsigned long maxSize) override;
	virtual int WriteData() override;
};

#endif