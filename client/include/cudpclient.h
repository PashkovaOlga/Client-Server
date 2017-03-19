#ifndef CUDPCLIENT_H
#define CUDPCLIENT_H

#include "cabstractnetworker.h"

class CUDPClient : public CAbstractNetworker
{
public:
    CUDPClient();
    CUDPClient(const char* ip, ushort port);
    CUDPClient(ulong ip, ushort port);
    ~CUDPClient();

    void start();
    void init(const char* ip, ushort port);
    void init(ulong ip, ushort port);

private:
    CUDPClient(const CUDPClient&) ;
    CUDPClient& operator=(const CUDPClient&);

    sockaddr_in _server;
    char *message;

    void resetToNull();
    void init(...) {}

};
#endif // CUDPCLIENT_H
