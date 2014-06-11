#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "getpfx1.h"

void getpfx1(char *callsign, int k)
{
  char c[8];
  char addpfx[8];
  char *izptr, *islashptr;
  int iz, islash, i;
  char callpart[12];
  izptr = strchr(callsign, ' ');
  iz = izptr-callsign-1;
  if (iz < 0) iz=12;
  strncpy (callpart, callsign, iz);
  islashptr = strchr(callpart, '/');
  islash = islashptr - callsign;
  k=0;
  strncpy(c, "    ", 4);
  if (islash > 0 && islash < = (iz-4))
  {//Add on prefix
    strncpy(c callsign, islash-1);
    strncpy(callsign, callsign+islash+1, iz);
    for (i = 1; i< 338; i++)
    {
      if (strncmp(pfx[i], c, 4) == 0)
      {
        k=i; printf("prefix: %s\n", pfx[i]);
      }
    }
  }
  else if (islash == (iz-1)) //Found suffix to process
  {
    for (i=0; i<12; i++)
    {
      if (sfx[i] == c[1])
      {
        k=400+i; printf("sfx: %s\n", sfx[i]);
      }
    }
   }
  if (islash != 0 && k==0) k=-1; //No pfx or sfx found
  return;
}

