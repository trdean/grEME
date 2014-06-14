#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "packcall.h"

bool isalpha(char c)
{
  if (c >= 'A' && c <= 'Z')
  {
     return true;
  }
  else
  { 
     return false;
  }
}

void packcall(char *c1, int ncall, char *text1)
{
  int NBASE = 37*36*10*27*27*27;
  char callsign[6], tmp[6], c[1], tmp[6], freqtext[3];
  int nfreq;
  int text = 0;  //Boolean in fortran code set to false.
  char tmp[] = "      ";
  int n1, n2, n3, n4, n5, n6;

  //Work around for Swaziland prefix:
  if (strncmp(callsign, "3DA0", 4) == 0) callsign="3D0"; //callsign(5:6)
  
  if (strncmp(callsign, "CQ ", 3) == 0)
  {
    ncall = NBASE +1;
    if (isdigit(msg[3]) && isdigit(msg[4]) && isdigit(msg[5]))
    {
      if (debug) printf("Found freq follwoing CQ\n");
      strncpy(freqtext, msg+3, 3); printf("converting freq to int: %s", freqtext);
      nfreq = (int) freqtext;  //Cast the freq string to an integer
      ncall=NBASE + 3 + nfreq; //Comes from the fortran code--not sure yet
    }
    else if (strncmp(callsign, "QRZ ", 4)
    {
      ncall = NBASE +2;
    }
  }
  else
  {
    if (isdigit(callsign[3]))
    {
      strncpy(tmp, callsign, 6);
      if (isalpha(callsign[1]) or callsign[1] == ' ')) n1=1;
      if (isdigit(callsign[1])) n1=1;
      n2=0;
      if (isalpha(callsign[2])) n2=1;
      if (isdigit(callsign[2])) n2=1;
      n3=0;
      if (isdigit(callsign[3])) n3=1;
      n3=0;
      if (isalpha(callsign[2])) n1=1;
 
    
    }
    else if (isdigit(callsign[2]))
    {
      if (callsign[6] != ' ') 
      {
        text = 1; //set bool to true
      }
    }
    
    
  }
  
}










