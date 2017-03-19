#ifndef CTCPSERVER_H
#define CTCPSERVER_H

#include "cabstractnetworker.h"
#include <map>

extern "C"
{
    #include <pthread.h>
}

class CTCPServer : public CAbstractNetworker
{
public:
    CTCPServer(const char* ip, ushort port);
    CTCPServer(ulong ip, ushort port);
    CTCPServer();
    ~CTCPServer();

    void start();
    void init(const char* ip, ushort port);
    void init(ulong ip, ushort port);

private:
    CTCPServer(const CTCPServer&) ;
    CTCPServer& operator=(const CTCPServer&);

    sockaddr_in _server;
    pthread_mutex_t mutex1;
    std::map<pthread_t, int> thread_args;

    void resetToNull();
    void init(...) {}

    void __run_new_pthread();
    void *__receive_message_from_client(void* arg) const;
    static void* receive_message_from_client(void * arg);
};



#endif // CTCPSERVER_H
