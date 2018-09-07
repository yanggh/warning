#ifndef  _MY_READER_H_
#define  _MY_READER_H_

#include <iostream>
#include <string>
#include <fstream>
#include "Common.h"

class  Reader
{
private:
	int fd;
public:
	Reader(const std::string dev);
	~Reader();
	Data get_data();
};
#endif
