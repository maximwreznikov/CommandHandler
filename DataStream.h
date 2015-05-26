#ifndef DataSource_h
#define DataSource_h

/**
@brief base interface for data source
@detailed
*/
class DataStream
{
public:
	DataStream();
	virtual ~DataStream();
	/**
	@brief Open some stream
	@return 0 - ok; negative - some error occured
	*/
	virtual int OpenStream() = 0;

	/**
	@brief Close some stream
	*/
	virtual void CloseStream() = 0;

	/**
	@brief Read data from some stream
	@param buffer - buffer to read
	@param maxSize - size of buffer
	@return size of read bytes
	*/
	virtual unsigned long ReadData(char * buffer, unsigned long maxSize) = 0;
	virtual int WriteData() = 0;
};


#endif

