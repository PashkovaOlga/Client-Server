#include "../../include/cudpserver.h"

CUDPServer::CUDPServer(ulong ip, ushort port)
    : CAbstractNetworker(SOCK_DGRAM),
      message(NULL)
{
    init(ip, port);
}
CUDPServer::CUDPServer(const char *ip, ushort port)
    : CAbstractNetworker(SOCK_DGRAM),
      message(NULL)
{
    init(ip, port);
}

CUDPServer::CUDPServer()
    : CAbstractNetworker(SOCK_DGRAM),
      message(NULL)
{

}


CUDPServer::~CUDPServer()
{
    __closeConnection();
}

void CUDPServer::init(ulong ip, ushort port)
{
    resetToNull();
    __initServerAddr(_server, ip, port);
    fl_init = true;
}

void CUDPServer::init(const char *ip, ushort port)
{
    resetToNull();
    __initServerAddr(_server, ip, port);
    fl_init = true;
}
void CUDPServer::resetToNull()
{
    delete [] message;
    message = NULL;
    bzero(&_server, sizeof(_server));
    _socket_desc = -1;
    fl_init = false;
}

void CUDPServer::start()
{
    try
    {
        __checkInit();
        __createSocket();
        __bindSocket(_server);

        while (1)
        {
            char* mess = NULL;
            try
            {
                message = mess = new char[MAX_SIZE];
                sockaddr_in _client;
                socklen_t len= sizeof(_client);
                cout << "Wait ..." << endl;
                string str = "\nReceive from: ";
                __recvFrom(mess, &_client, &len, str.c_str());
                __sendTo(_client,  mess);

                std::vector<int> nums;
                storeDigits_Sum(nums, mess);
                sort_PrintSequence_MaxMin(nums);
                __clearArr(mess);
            }
            catch (string exception)
            {
                cout << exception << endl;
            }
        }

    }
    catch (string exception)
    {
        cout << exception << endl;
    }
}






