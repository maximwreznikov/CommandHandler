#ifndef MockStream_h
#define MockStream_h
#include "DataStream.h"
#include <string>
#include <fstream>

/**
@brief mock class - read data from test file
@detailed
*/
class MockStream : public DataStream
{
	std::ifstream				_file;
public:
	static  std::string			GetFileName() { return "test_data"; }			/**< file with test set of command */

	MockStream();
	virtual ~MockStream();
	/**
	@brief Open file
	@return 0, if ok; negative, if some error occured
	*/
	virtual int OpenStream() override;
	virtual void CloseStream() override;
	virtual unsigned long ReadData(char * buffer, unsigned long maxSize) override;
	virtual int WriteData() override;
};



#endif

