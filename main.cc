// Slugpower main program
// Phil Endecott, July 2006.

#include "Ftdi.hh"

#include <unistd.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h> 

#define	CMD_ENABLE		"1"
#define	CMD_DISABLE		"0"


#define VENDOR_ID 		0x0403
#define PRODUCT_ID 		0x6001

#define BAUDRATE		115200
#define RELAY_MASK		0xFF
#define DISABLE_MASK		0xFF


using namespace std;

void usage(void){
    cerr << "Usage: ftdi prtID newValue\n";
    exit (1);
}

void portException(void){
    cerr << "Port id can be only between 1 to 8\n";
    exit (1);
}

void valueException(void){
    cerr << "Value can be only 0 - disable or 1 - enable\n";
    exit (1);
}

int portToMask(int portId){
    return (int)pow(2.0,portId + 0.0);
}

int main(int argc, char* argv[]){
  if (argc!=3){
    usage();
  }

  string 	newValue 		= argv[2];
  int 		portId 			= atoi(argv[1]);
  int 		newValueToWrite 	= 0;
  int 		newMask			= 0;
  uint8_t 	ftdiCurrentStatus 	= 0;
  if(portId < 1 || portId > 8){
      portException();
  }
  if(newValue!=CMD_DISABLE && newValue!= CMD_ENABLE){
      cout << "Value provided is : " << newValue << "\n";
      valueException();
  }
  
  
  try {
      portId--;									//	
      Ftdi 		ftdi(VENDOR_ID, PRODUCT_ID, BAUDRATE, RELAY_MASK);
      ftdiCurrentStatus = ftdi.read();
      newMask 		= portToMask(portId);
      printf ("Relay port status : %#1x \n", ftdiCurrentStatus);
      if (newValue==CMD_ENABLE){
	  newValueToWrite 	= (ftdiCurrentStatus | newMask);		//	current OR new
      }
      else if (newValue==CMD_DISABLE) {
	  newValueToWrite 	= (ftdiCurrentStatus & (DISABLE_MASK ^ newMask));	//	current AND ( ALL ON XOR new)
      }
      printf ("Writing : %#1x \n", newValueToWrite);
      ftdi.write( newValueToWrite);
      
  }
  catch (const char* c){
      cerr << "Error: " << c << "\n";
      exit(1);
  }
}
