#include <string.h>
#include <stdio.h>
#include "checkmsg.h"

void checkmsg(char* msg, char* cok, int nspecial, float flip, int debug)
/* This function looks for OOO in the message, or if it is a shorthand msg */
{
  nspecial=0;
  flip=1.0;
  cok ="   ";
  int msgindicate = 22;
  int i;
  for (i = 22; i > 0; i--)
  {
     if (debug)
     {
       printf("%d\n", i);
     }
     if (msg[i] != ' ')
     {
	if (debug) { printf ("No Space, finish loop\n"); }        
	msgindicate = i;
        i=0;
     }
  }
  //We need to check this if statement to ensure it is evaluating properly
printf(" 	 message: %s\n", msg);
  if ((msgindicate >= 11) && (strncmp(&msg[msgindicate-3], " OOO", 4)) == 0 || (strncmp(&msg[20], " OO", 3)) == 0)
  {
     cok = "OOO";
     flip = -1.0;
     if (strncmp(&msg[20], " OO", 3))
     {
 	memcpy(msg, &msg[1], 19);
     }
     else
     {
	printf("Hit else");
	memcpy(msg, &msg[0], msgindicate-4);
     }
   }
   if (strncmp(&msg[0], "ATT", 3) == 0) 
   {
	nspecial=1;
   }
   if (strncmp(&msg[0], "RO", 2) == 0) 
   {
	nspecial=2;
   }
   if (strncmp(&msg[0], "RRR", 3) == 0) 
   {
	nspecial=3;
   }
   if (strncmp(&msg[0], "73", 2) == 0) 
   {
	nspecial=4;
   }
   printf("compared: %d\nnspecial = %d\n", strncmp(&msg[0], "73", 2), nspecial);
   
}

