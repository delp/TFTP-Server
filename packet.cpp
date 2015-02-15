#include <iostream>
#include "parseTFTPPacket.h"
#include "packetFormer.h"

using namespace std;

int main()
{
  Packet* readPack;
  Packet* writePack;
  Packet* dataPack;
  Packet* ackPack;
  Packet* errorPack;

  char rrq[20] = { 0, 1 , 'c', 'a', 't', 's', '.', 'j', 'p', 'g',
		   0, 'n', 'e', 't', 'a', 's', 
		   'c', 'i', 'i', 0};

  char wrq[20] = { 0, 2 , 'c', 'a', 't', 's', '.', 'j', 'p', 'g',
		   0, 'n', 'e', 't', 'a', 's', 
		   'c', 'i', 'i', 0};
		   
		   char data[20];
    data[0] = 0;
    data[1] = 3;
    data[2] = 0;
    data[3] = 1;
    for(int i = 4; i < 20; i++)
      {
	data[i] = i + 10;
      }
    
    char ack[4] = { 0, 4, 0, 1};
    
    char error[10] = {0, 5, 6, 9, 'w', 'o', 'o', 'p', 's', 0};
    
    //size is 20
    readPack = parseTFTPPacket(rrq, 20);
    printPacket(readPack);
    writePack = parseTFTPPacket(wrq, 20);
    printPacket(writePack);
    dataPack = parseTFTPPacket(data, 20);
    printPacket(dataPack);
    ackPack = parseTFTPPacket(ack, 4);
    printPacket(ackPack);
    errorPack = parseTFTPPacket(error, 10);
    printPacket(errorPack);
    
  return 0;
}
