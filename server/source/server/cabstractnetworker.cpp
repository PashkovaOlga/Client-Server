#include "../../include/cabstractnetworker.h"

CAbstractNetworker::CAbstractNetworker(__socket_type type)
    :_socket_desc(-1),
     fl_init(false),
     _protocol(type)
{
}


CAbstractNetworker::~CAbstractNetworker()
{

}

void CAbstractNetworker::__createSocket(int p)
{
    _socket_desc = socket(AF_INET , _protocol , p);

    if (_socket_desc == -1)
    {
        perror(NULL);
        throw string("Error: Could not create socket");
    }

    cout << "Socket created" << endl;
}

void CAbstractNetworker::__connectToServer(sockaddr_in &_server)const
{
    if (connect(_socket_desc , (struct sockaddr *)&_server , sizeof(_server)) < 0)
    {
        perror(NULL);
        throw string("Error: Connect failed.");
    }

    cout << "Connected" << endl;
}

void CAbstractNetworker::__getMessage(char* mess) const
{
    fflush(stdin);

    cout << "\nEnter message : " << endl;

    cin.getline(mess, MAX_SIZE);

}

void CAbstractNetworker::__writeMessage (char* mess) const
{
    if( write(_socket_desc, mess, strlen(mess)+1) < 0)
    {
        perror(NULL);
        throw string("Error: Write failed");
    }


}

void CAbstractNetworker::__readAnswer(char* ans) const
{
    if( read(_socket_desc, ans, MAX_SIZE) < 0)
    {
        perror(NULL);
        throw string("Error: Read failed");
    }

    cout << "Server reply: " << endl;
    cout << ans << endl;

}

void CAbstractNetworker::__closeConnection()
{
    close(_socket_desc);
    resetToNull();

    cout << "Connection closed" << endl;
}

void CAbstractNetworker::__initServerAddr(sockaddr_in &_server, const char* ip, ushort port)
{
    if(inet_aton(ip, &_server.sin_addr) == 0)
    {
        perror(NULL);
        throw string ("Error: IP adress is wrong.");
    }
    _server.sin_family = AF_INET;
    _server.sin_port = htons( port );
}

void CAbstractNetworker::__initServerAddr(sockaddr_in &_server, ulong ip, ushort port)
{
    _server.sin_addr.s_addr = htonl(ip);
    _server.sin_family = AF_INET;
    _server.sin_port = htons( port );
}

bool CAbstractNetworker::__isInit() const
{
    return fl_init;
}

void CAbstractNetworker::__checkInit() const
{
    if(!__isInit())
    {
        throw string("Error: Object wasn't initialized.");
    }
}

void CAbstractNetworker::__bindSocket(sockaddr_in &_server) const
{
    if( bind(_socket_desc, (sockaddr*) &_server, sizeof(_server)) < 0)
    {
        perror(NULL);
        throw string("Error: Can't bind socket.");
    }

    cout << "Bind socket." << endl;
}

void CAbstractNetworker::__listen() const
{
    if(listen(_socket_desc, 5) < 0)
    {
        perror(NULL);
        throw string("Error: Can't listen.");
    }
}

int CAbstractNetworker::__accept() const
{
    int _new_desc;
    if ((_new_desc = accept(_socket_desc, NULL, NULL)) < 0)
    {
        perror(NULL);
        throw string("Error: Can't accept");
    }

    return _new_desc;
}

void CAbstractNetworker::__sendTo(sockaddr_in &_server, char* mess) const
{
    if(sendto(_socket_desc, mess, strlen(mess)+1, 0, (sockaddr*) &_server, sizeof(_server)) < 0)
    {
        perror(NULL);
        throw string("Error: Can't sendTo()");
    }

}

void CAbstractNetworker::__recvFrom(char* mess, sockaddr_in *_server, socklen_t *len, const char* str) const
{

    if(recvfrom(_socket_desc, mess, MAX_SIZE, 0, (sockaddr*)_server, len) < 0)
    {
        perror(NULL);
        throw string("Error: Can't recvFrom()");
    }

    if(str!=NULL)
    {
        cout << str << endl;
    }

    cout << mess << endl;
}

 void CAbstractNetworker::__clearArr(char* mess) const
 {
     bzero(mess, MAX_SIZE);
 }
 void CAbstractNetworker::storeDigits_Sum(std::vector<int> &nums, char* client_message) const
 {
     if(strlen (client_message))
     {
         int ind = 0;
         char ch;
         int sum = 0;
         int dig = 0;
         while ((ch = client_message[ind++]) != '\0')
         {
             if(isDigit(ch))
             {
                 dig = atoi(&ch);
                 sum += dig;
                 nums.push_back(dig);
             }
         }
         if(nums.empty())
         {
             cout << "Sequense has not digits" << endl;
             return;
         }
         cout << "Sum: " << sum << endl;
     }
     else
     {
         cout << "Sequense has not digits" << endl;
         return;
     }
 }
 void CAbstractNetworker::sort_PrintSequence_MaxMin(std::vector<int> &nums) const
 {
     if(!nums.empty())
     {
         std::sort (nums.begin(), nums.end());

         cout << "The sequence in descending order: " << endl;
         int max=0, min=0;
         std::vector<int>::reverse_iterator rit = nums.rbegin();
         max = *rit;
         for (; rit!= nums.rend(); ++rit)
         {
             cout << *rit;
         }
         cout << endl;

         min = *(--rit);

         cout << "Max= " << max << " Min= " << min << endl;
     }
 }

 bool CAbstractNetworker::isDigit(const char symbol) const
 {
     int code = (int)symbol;

     return(code>=48 && code<=57);
 }
