#ifndef CUDPSERVER_H
#define CUDPSERVER_H

#include "cabstractnetworker.h"

class CUDPServer : public CAbstractNetworker
{
public:
    CUDPServer(ulong ip, ushort port);
    CUDPServer(const char* ip, ushort port);
    CUDPServer();
    ~CUDPServer();

    void start();
    void init(ulong ip, ushort port);
    void init(const char* ip, ushort port);

private:
    CUDPServer(const CUDPServer&) ;
    CUDPServer& operator=(const CUDPServer&);

    sockaddr_in _server;
    char* message;

    void resetToNull();
    void init(...) {}

};

#endif // CUDPSERVER_H
