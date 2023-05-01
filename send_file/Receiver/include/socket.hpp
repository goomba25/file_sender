#include <sys/socket.h>

class Socket
{
protected:
    int sock;

public:
    Socket()
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
    }
};
