#include <iostream>
#include "../include/ctcpclient.h"
#include "../include/cudpclient.h"

using namespace std;

int main()
{
      cout << "Type symbol 'U' to run UDP Client or 'T' to run TCP Client." << endl;
      cout << "'U' or 'T':" ;
      char p;
      cin >> p;
      cout << endl;

      if((p == 'u') || (p == 'U'))
      {
          cout << "UDP Client run."  << endl;
          CUDPClient ucl("127.0.0.1", 51000);
           ucl.start();
      }
      else if((p == 't') || (p == 'T'))
      {
          cout << "TCP Client run."  << endl;
          CTCPClient cl("127.0.0.1", 51000);
          cl.start();
      }
      else
      {
          cout << "Wrong symbol." << endl;
      }


    return 0;
}
