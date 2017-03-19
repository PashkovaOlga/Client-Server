#ifndef CABSTRACTNETWORKER_H
#define CABSTRACTNETWORKER_H

extern "C"
{
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <stdio.h>
}

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class CAbstractNetworker
{
public:
    CAbstractNetworker(__socket_type type);
    virtual ~CAbstractNetworker();

    virtual void start() = 0;
    virtual void init(...)  = 0;

private:
    CAbstractNetworker(const CAbstractNetworker&) ;
    CAbstractNetworker& operator=(const CAbstractNetworker&);

    virtual void resetToNull() = 0;
    bool __isInit() const;

protected:
    /**
     * @brief _socket_desc - socket descriptor
     */
    int _socket_desc;

    /**
     * @brief MAX_SIZE - maximum message size
     */
    static const int MAX_SIZE = 65000;

    bool fl_init;
    __socket_type _protocol;

    void __createSocket(int p=0);
    void __connectToServer(sockaddr_in &_server)const;
    void __initServerAddr(sockaddr_in &_server, const char *ip, ushort port);
    void __initServerAddr(sockaddr_in &_server, ulong ip, ushort port);
    void __getMessage  (char *mess) const;
    void __writeMessage(char* mess) const;
    void __readAnswer (char* ans) const;
    void __closeConnection();
    void __checkInit() const;
    void __bindSocket(sockaddr_in &_server) const;
    void __listen() const;
    int  __accept() const;
    void __sendTo(sockaddr_in &_server, char* mess) const;
    void __recvFrom(char* mess, sockaddr_in *_server=NULL, socklen_t* len=NULL, const char *str=NULL) const;
    void __clearArr(char* mess) const;


    bool isDigit(const char symbol) const;
    void storeDigits_Sum(std::vector<int> &nums, char* client_message) const;
    void sort_PrintSequence_MaxMin(std::vector<int> &nums) const;


};

#endif // CABSTRACTNETWORKER_H
