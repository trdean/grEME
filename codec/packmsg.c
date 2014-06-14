#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "packmsg.h"
#include "getpfx1.h"

void upcase(char *msg, int length)
{
  int i;
  for (i=0; i<length; i++)
  {
    if (msg[i] > 96)
    {
       msg[i] = msg[i] - 32;
    }
  }
}

void packmsg(char *msg, int *dat)
{
  int debug = 1;
  //char msg[22];
  int msgsize = strlen(msg);
  int i, firstspace, secondspace, thirdspace, k1, k2;
  //strncpy(msg, message, 22);
  char c1[12] = " ", c2[12] = " ", c3[4]=" ", grid6[6], dxcc[3];
  char *spc;

  if (debug)
  {
    printf("Begin message pack\n");
    printf("Message: %s\n", msg);
  }
  
  /*Upcase the message*/
  upcase(msg, 22);
  if (debug)
  {
    printf("Upcased message: %s\n", msg);
  }
  /*Determine if msg is CQ and if freq is present */
  if (strncmp(msg, "CQ ", 3) == 0)
  {
    if (debug) printf("Msg is CQ\n");
    if (isdigit(msg[3]) && isdigit(msg[4]) && isdigit(msg[5]))
    {
      if (debug) printf("Found freq follwoing CQ\n");
      firstspace = 6;
    }
    else
    {
      firstspace = 2;
    }
  }
  else /* find the next space in the msg */
  {
    spc = strchr(msg, ' ');
    firstspace = spc-msg;
  }
  strncpy(c1, msg, firstspace);
  spc = strchr(msg+firstspace+1, ' ');

  if (spc != NULL)
  {
    secondspace = spc-msg+1;
    if (debug) printf("2nd space is at %d, 1st is %d", secondspace, firstspace);
    strncpy(c2, msg + firstspace+1, secondspace-firstspace -2);
    spc = strchr(msg+secondspace+1, ' '); //Get 3rd space if any
    thirdspace = spc-msg;
    if (spc != NULL)
    {
      strncpy(c3, msg+secondspace, thirdspace); printf("C");
    }
    else //No third space copy rest of string to c3
    {
      strncpy(c3, msg+secondspace, msgsize-secondspace-1); printf("B");
       printf("xx%dxx%dx%sx", secondspace, msgsize, c3);
      thirdspace = -1;
    }
  }
  else //No second space copy rest of mesage to second string
  {
     strncpy(c2, msg+firstspace+1, msgsize-firstspace-2); printf("A");
     thirdspace = -1; secondspace = -1;
  }
  strncpy(c1, msg, firstspace);
  if (debug)
  {
    printf("first space is at '%d', second is '%d', zthird is '%d'\n", firstspace, secondspace, thirdspace);
    printf("first string: '%s', second '%s', third '%s'\n", c1, c2, c3);
  }
  if ((secondspace > -1) && strncmp(c3, "OOO", 3)==0) //Strip out the OOO flag
  {
     strncpy(c3, "    ", 4);
     if (debug) printf("Found OOO\n"); 
  }

  getpfx1(c1, k1);
  //printf("C1 = %s, k1= %d\n", c1, k1);
  packcall(c1,nc1,text1);
/* call getpfx1(c1,k1)
      call packcall(c1,nc1,text1)
      call getpfx1(c2,k2)
      call packcall(c2,nc2,text2) */
}
















