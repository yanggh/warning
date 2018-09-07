#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "MyReader.h"
#include "wraptermios.h"
#include "JsonConf.h"
#include "Common.h"

using namespace std;

ssize_t Readn(int fd, void *vptr, size_t n)
{
    size_t  nleft;
    ssize_t nread;
    char    *ptr;

    ptr = (char*)vptr;
    nleft = n;

    while (nleft > 0)
    {
        if ( (nread = read(fd, ptr, nleft)) < 0)
	{
            if (errno == EINTR)
                nread = 0;      /* and call read() again */
            else
                return(-1);
        }
	    else if (nread == 0)
            break;              /* EOF */

        nleft -= nread;
        ptr   += nread;
    }
    return(n - nleft);      /* return >= 0 */
}

Reader::Reader(const string dev)
{
    fd = Tty_open_easy(dev.c_str());

    Tty_raw(fd);
    Tty_set_speed(fd, 230400);
    Tty_set_parity(fd, 8, 1, 'N');
    Tty_set_icanon(fd, 0, 0);
}

Reader::~Reader()
{
    close(fd);
}

Data Reader::get_data()
{
	Data d;
	uint8_t len = 0;
	uint8_t check = 0;

	read(fd, &d.type, 1);
	read(fd, &len, 1);
	read(fd, &check, 1);

	string &data = d.data;

	const int BUFSIZE = 1024;
	char  buff[BUFSIZE] = {0};

	ssize_t nread = Readn(fd, buff, len);
	if(nread == len)
	{
		data.assign(buff, len);
	}

	return move(d);
}
