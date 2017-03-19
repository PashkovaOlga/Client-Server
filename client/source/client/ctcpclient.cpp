#include "../../include/ctcpclient.h"

CTCPClient::CTCPClient(const char *ip, ushort port)
    : CAbstractNetworker(SOCK_STREAM),
      message(NULL)
{
    init(ip, port);
}

CTCPClient::CTCPClient(ulong ip, ushort port)
    : CAbstractNetworker(SOCK_STREAM),
      message(NULL)
{
    init(ip, port);
}
CTCPClient::CTCPClient()
    : CAbstractNetworker(SOCK_STREAM),
      message(NULL)
{
}
CTCPClient::~CTCPClient()
{
    __closeConnection();
}

void CTCPClient::start()
{
    try
    {
        __checkInit();
        __createSocket();
        __connectToServer(_server);

        //keep communicating with server
        while(1)
        {
            __getMessage(message);

            __writeMessage(message);
            __clearArr(message);

            __readAnswer(message);
            __clearArr(message);
        }
    }

    catch (string exception)
    {
        cout << exception << endl;
    }
}

 void CTCPClient::init(const char *ip, ushort port)
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
 void CTCPClient::init(ulong ip, ushort port)
 {
     resetToNull();
     message = new char[MAX_SIZE];
     __initServerAddr(_server, ip, port);
     fl_init = true;
 }
 void CTCPClient::resetToNull()
 {
     delete [] message;
     message = NULL;
     bzero(&_server, sizeof(_server));
     _socket_desc = -1;
     fl_init = false;
 }
