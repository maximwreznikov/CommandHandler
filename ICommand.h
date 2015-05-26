#ifndef ICommand_h
#define ICommand_h

#include <memory>
#include <string>

class Client;
class ICommand;
using PtrCommandHandler = std::shared_ptr<ICommand>;

/**
@brief base class for command
@detailed
*/
class ICommand
{
protected:
	static const uint32_t	StartWord = 0;
	virtual int parseBody(const char * bodyBytes, unsigned long bodySize) = 0;
public:
	ICommand();
	virtual ~ICommand();
	/**
	@brief Read data from stream
	@detailed standard implementation
	@param bytes - byte stream
	@param offset - offset on that stream
	@return -1 - crc error; -2 - parse error
			0 - ok
	*/
	virtual int ReadData(const char * bytes, unsigned long& offset);

	/**
	@brief  Write data to byte stream
	@param bytes - byte stream
	@param size - size of bytes
	@return 0 - ok
	*/
	virtual size_t WriteData(std::string& bytes) = 0;

	/**
	@brief Execute command
	@param client - byte stream
	@return < 0 - some error;
			 0 - ok
	*/
	virtual int Execute(Client * client) = 0;

	virtual PtrCommandHandler Clone() const = 0;
};

template<typename T>
void ReadType(T& ptr, const char * bytes, unsigned long& offset)
{
	memcpy(&ptr, bytes + offset, sizeof(T));
	offset += sizeof(T);
}

template<typename T>
void ReadType(T* ptr, const char * bytes, unsigned long& offset, uint8_t size)
{
	memcpy(ptr, bytes + offset, size);
	offset += size;
}

template<typename T>
void WriteType(char * bytes, T value, unsigned long& offset)
{
	memcpy(bytes + offset, &value, sizeof(T));
	offset += sizeof(T);
}

template<typename T>
void WriteType(char * bytes, T* value, unsigned long& offset, uint8_t size)
{
	memcpy(bytes + offset, value, size);
	offset += size;
}

#endif

