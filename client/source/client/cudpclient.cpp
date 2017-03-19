#include "../../include/cudpclient.h"

CUDPClient::CUDPClient(const char *ip, ushort port)
    : CAbstractNetworker(SOCK_DGRAM),
    message(NULL)
{
  init(ip, port);
}

CUDPClient::CUDPClient(ulong ip, ushort port)
    : CAbstractNetworker(SOCK_DGRAM),
    message(NULL)
{
  init(ip, port);
}


CUDPClient::CUDPClient()
    : CAbstractNetworker(SOCK_DGRAM),
    message(NULL)
{
}

CUDPClient::~CUDPClient()
{
    __closeConnection();
}

void CUDPClient::init(const char *ip, ushort port)
{
    try
   {
       resetToNull();

       message = new char[MAX_SIZE];
       __initServerAddr(_server, ip, port);
       fl_init = true;
    }

    catch (string exception)
    {
        cout << exception << endl;
    }

}

void CUDPClient::init(ulong ip, ushort port)
{

       resetToNull();

       message = new char[MAX_SIZE];
       __initServerAddr(_server, ip, port);
       fl_init = true;
}
void CUDPClient::resetToNull()
{
    delete [] message;
    message = NULL;
    bzero(&_server, sizeof(_server));
    _socket_desc = -1;
    fl_init = false;
}

void CUDPClient::start()
{
    try
    {
        __checkInit();
        __createSocket();

        //keep communicating with server
        while(1)
        {
            socklen_t len = sizeof(_server);
            __getMessage(message);
            __sendTo(_server, message);
            __clearArr(message);
            cout << "Server reply: " << endl;
            __recvFrom(message, &_server, &len);
            __clearArr(message);
        }
    }

    catch (string exception)
    {
        cout << exception << endl;
    }
}
