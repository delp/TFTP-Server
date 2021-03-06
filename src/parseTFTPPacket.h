#ifndef PARSETFTPPACKET_H
#define PARSETFTPPACKET_H

#include <iostream>
#include <string>


using namespace std;

//ALL STRINGS ARE TERMINATED WITH A ZERO BYTE
struct Packet
{
  //for RRQ, WRQ
  int type;
  char* filename;
  int filename_length;
  char* mode;
  int mode_length;
  
  //for DATA and ACK
  char block_num[2];
  char* data;
  int data_length;

  //for ERROR
  char errorcode[2];
  char* errmsg;
  int errmsg_length;

};

void printPacket(Packet* p)
{
  if(p != 0)
    {
      cout << "Type: "            << p->type            << endl;
      if(p->filename != 0)
	{
	  cout << "Filename: "    << p->filename        << endl;
	}
      cout << "Filename_length: " << p->filename_length << endl;
      if(p->mode != 0)
	{
	  cout << "Mode: "        << p->mode            << endl;
	}
      cout << "Mode_length: "     << p-> mode_length    << endl;
      cout << "Block_Num: "       << p->block_num[0] << p->block_num[1]
	                                              << endl;
      if(p->data != 0)
	{
	  cout << "Data: "        << p->data            << endl;
	}
      cout << "Data_length: "     << p->data_length     << endl;
      cout << "Errorcode: "       << p->errorcode[0] << p->errorcode[1]
	                                               << endl;
      if(p->errmsg != 0)
	{
	  cout << "ErrMessage: "  << p->errmsg          << endl;
	}
      cout << "ErrMsg_Length: "   << p->errmsg_length   << endl;
      
      
    }
  else
    {
      cout << "Null packet. Not printing." << endl;
    }
}

void zeroOut(Packet* p)
{
  if(p != 0)
    {
      p -> type = 0;
      p -> filename = 0;
      p -> filename_length = 0;
      
      p -> mode = 0;
      p -> mode_length = 0;
      
      p -> block_num[0] = 0;
      p -> block_num[1] = 0;
      p -> data = 0;
      p -> data_length = 0;
      
      p -> errorcode[0] = 0;
      p -> errorcode[1] = 0;
      p -> errmsg = 0;
      p -> errmsg_length = 0; 

    }
  else { cout << "Null packet. Can't zero." << endl; }
}

void getFilename(char* data, int length, Packet* p)
{  
  //initialize an index to walk through the datagram over the filename portion
  char* bufferthing = new char[256];
  int walker = 2;
  int current_length = 0; //keep track of the length of the filename
  
  char current_byte = data[walker]; //current_byte is going to check 
  //for the 0 byte that terminates the filename
  
  while(current_byte != (char) 0)
    {
  
      bufferthing[walker-2] = data[walker];
      current_length++;
      walker++;
      current_byte = data[walker];
    }
  
  
  char* fname = new char[current_length];
  for(int i = 0; i < current_length; i++)
    {
      fname[i] = bufferthing[i];
  
    }
  
  
  p -> filename = fname;  
  p -> filename_length = current_length;

}

void getMode(char* data, int length, Packet* p)
{
  char* bufferthing = new char[30];
  int walker = 2;
  //skim past the filename;
  while(data[walker] != (char) 0)
    {
      walker++;
    }
  walker++;
  int modeIndex = walker;
  int bufferIndex = 0;
  int current_length = 0;
  char current_byte = data[walker];
  while(current_byte != (char) 0)
    {
      bufferthing[bufferIndex] = data[walker];
      current_length++;
      walker++;
      bufferIndex++;
      current_byte = data[walker];
    }

  char* modename = new char[current_length];
  for(int i = 0; i < current_length; i++)
    {
      modename[i] = bufferthing[i];
    }
  p -> mode = modename;
  p -> mode_length = current_length;
}

int getType(char* data, int length)
{
  if(length >= 1)
    {
      if(data[1] == (char) 1 ){ return 1;}
      if(data[1] == (char) 2 ){ return 2;}
      if(data[1] == (char) 3 ){ return 3;}
      if(data[1] == (char) 4 ){ return 4;}
      if(data[1] == (char) 5 ){ return 5;}
      return -2;
    }
  else
    {
      //if the size is incorrect, avoid checking data[1] and 
      //return error code
      return -1;
    }
}

void getBlockNum(char* data, int length, Packet* p)
{
  p -> block_num[0] = data[2];
  p -> block_num[1] = data[3];
}

void getData(char* data, int length, Packet* p)
{
  char* datagram = new char[length - 4];
  for(int i = 4; i < length; i++)
    {
      datagram[i-4] = data[i];
    }
  p -> data = datagram;
  p -> data_length = (length - 4 );
}

void getErrorCode(char* data, int length, Packet* p)
{
  p -> errorcode[0] = data[2];
  p -> errorcode[0] = data[3];
}

void getErrorMessage(char* data, int length, Packet* p)
{
  char* msg = new char[length - 4];
  for(int i = 4; i < (length - 1); i++)
    {
      msg[i - 4] = data[i];
    }
  p -> errmsg = msg;
  p -> errmsg_length = length - 5;  //This is minus 5
  //and not minus 4 because the length of the error
  //message should not include the terminating 0 character
  //at the end of the string
}

Packet* parseTFTPPacket(char* data, int length)
{
  
  //Make a new packet and initialize it to 0/null.
  Packet* pack = new Packet();
  zeroOut(pack);
  
  //get opcode
  pack -> type = getType(data, length);

  //if the opcode is incorrect/corrupted
  if(pack->type > 5 ||
     pack->type < 1)
    {
      cout << "Issue resolving packet opcode. Packet corrupted?" << endl;
      return 0;
    }
  
  //if the packet is an RRQ or an WRQ
  if(pack -> type == 1 ||
     pack -> type == 2)
    {
      getFilename(data, length, pack);
      getMode(data, length, pack);
    }
 
  
  //if the packet is DATA
  if(pack -> type == 3)
    {
      getBlockNum(data, length, pack);
      getData(data, length, pack);
    }
  
  //if the packet is an ACK
  if(pack -> type == 4)
    {
      getBlockNum(data, length, pack);
    }
  
  //if the packet is an ERROR
  if(pack -> type == 5)
    {
      getErrorCode(data, length, pack);
      getErrorMessage(data, length, pack);
    }
  
  return pack;
}

#endif
