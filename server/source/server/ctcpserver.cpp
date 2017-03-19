#include "../../include/ctcpserver.h"

CTCPServer::CTCPServer(const char* ip, ushort port)
    : CAbstractNetworker(SOCK_STREAM)
{
    init(ip, port);
}
CTCPServer::CTCPServer(ulong ip, ushort port)
    : CAbstractNetworker(SOCK_STREAM)
{
    init(ip, port);
}
CTCPServer::CTCPServer()
    : CAbstractNetworker(SOCK_STREAM)
{

}


CTCPServer::~CTCPServer()
{
    pthread_mutex_destroy(&mutex1);

    __closeConnection();
}

void CTCPServer::start()
{
    try
    {
        __checkInit();
        __createSocket();
        __bindSocket(_server);
        __listen();

        while (1)
        {
            cout << "Wait new client..." << endl;
            //for new client run new pthread
            __run_new_pthread();

        }

    }

    catch (string exception)
    {
        cout << exception << endl;
    }
}

void CTCPServer::__run_new_pthread()
{
    pthread_mutex_lock( &mutex1 );

    int sock_desc = __accept();
    pthread_t pid;
    thread_args.insert ( pair<pthread_t, int>(pid, sock_desc));
    std::map<pthread_t, int>::iterator it = thread_args.find(pid);
    pthread_t * p_pthread = (pthread_t *)&(it->first);

    int result = pthread_create(p_pthread, NULL,  receive_message_from_client, (void*)this);
    if (result != 0) {
        perror("Creating the thread: ");
    }
}

void CTCPServer::init(ulong ip, ushort port)
{
    resetToNull();
    __initServerAddr(_server, ip, port);
    fl_init = true;
}
void CTCPServer::init(const char* ip, ushort port)
{
    try
    {
        resetToNull();
        __initServerAddr(_server, ip, port);
        fl_init = true;
    }
    catch (string exception)
    {
        cout << exception << endl;
    }
}
void CTCPServer::resetToNull()
{
    bzero(&_server, sizeof(_server));
    _socket_desc = -1;
    thread_args.clear();
    mutex1 = PTHREAD_MUTEX_INITIALIZER;

    fl_init = false;
}

void *CTCPServer::__receive_message_from_client(void* arg) const
{
    pthread_t self;
    self = pthread_self();
    cout << "Create new pthread " << self << endl;

    CTCPServer* serv = (CTCPServer*)arg;
    std::map<pthread_t, int>::iterator it = serv->thread_args.find(self);
   int client_sock = it->second;
   pthread_mutex_unlock( &(serv->mutex1) );

    int read_size = 0;
    char* client_message = new char [MAX_SIZE];

    cout << "Wait..." << endl;
    //Receive a message from client
    while( (read_size = read(client_sock , client_message , MAX_SIZE)) > 0 )
    {
        cout << "\nReceive from: " << endl;
        cout << client_message  << endl;

        //Send the message back to client
        write(client_sock , client_message , strlen(client_message)+1);

        //-------------------
        std::vector<int> nums;
        storeDigits_Sum(nums, client_message);
        sort_PrintSequence_MaxMin(nums);
        //------------------

        __clearArr(client_message);
        cout << "Wait..." << endl;
    }

    if(read_size == 0)
    {
        cout << "Client disconnected" << endl;
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("Read failed: ");
    }

    close(client_sock);

    delete [] client_message;

    pthread_mutex_lock( &(serv->mutex1) );
    serv->thread_args.erase(self);
    pthread_mutex_unlock( &(serv->mutex1) );

    cout << "Pthread Exit " << self << endl;
    pthread_exit(NULL);
}


void* CTCPServer::receive_message_from_client(void * arg)
{
    CTCPServer* serv = (CTCPServer*)arg;

    return serv->__receive_message_from_client(arg);
}
