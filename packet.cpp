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
  return 0;
}
