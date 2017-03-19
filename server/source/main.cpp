#include <iostream>

#include "../include/ctcpserver.h"
#include "../include/cudpserver.h"

using namespace std;

int main()
{
      cout << "Type symbol 'U' to run UDP Server or 'T' to run TCP Server." << endl;
      cout << "'U' or 'T':" ;
      char p;
      cin >> p;
      cout << endl;

      if((p == 'u') || (p == 'U'))
      {
         cout << "UDP Server run."  << endl;
         CUDPServer userv((ulong)INADDR_ANY, 51000);
         userv.start();
      }
      else if((p == 't') || (p == 'T'))
      {
          cout << "TCP Server run."  << endl;
          CTCPServer se((ulong)INADDR_ANY, 51000);
          se.start();
      }
      else
      {
          cout << "Wrong symbol." << endl;
      }
    return 0;
}

