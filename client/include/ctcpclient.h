#ifndef CTCPCLIENT_H
#define CTCPCLIENT_H

#include "cabstractnetworker.h"

class CTCPClient : public CAbstractNetworker
{
public:
    CTCPClient(const char* ip, ushort port);
    CTCPClient(ulong ip, ushort port);
    CTCPClient();
    ~CTCPClient();

    void start();
    void init(const char* ip, ushort port);
    void init(ulong ip, ushort port);

private:
    CTCPClient(const CTCPClient&) ;
    CTCPClient& operator=(const CTCPClient&);

    sockaddr_in _server;
    char *message;

    void resetToNull();
    void init(...) {}
};

#endif // CTCPCLIENT_H
