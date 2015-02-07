#include <iostream>
#include "parseTFTPPacket.h"


using namespace std;

int main()
{
  Packet* thing;

  char rrq[20] = { 0, 1 , 'c', 'a', 't', 's', '.', 'j', 'p', 'g',
		   0, 'n', 'e', 't', 'a', 's', 
		   'c', 'i', 'i', 0};

  //size is 20
  thing = parseTFTPPacket(rrq, 20);
  
  
  printPacket(thing);



  char* d = thing->errorcode;
  cout << d << endl;
  d[0] = 255;
  d[1] = 234;
  cout << d << endl;

  
  return 0;
}
