/* Encoder for JT65 protocol */

#include <string.h>
#include <stdio.h>
#include "packmsg.h"
#include "checkmsg.h"
#include "getpfx1.h"

main()
{
  char msg[22]; //22 is apparently what JT65 uses
  char decoded;
  char cok[3] = "   ";
  int dgen[12], sent[63];
  int debug = 1;
  int nspecial = -1;
  float flip = 1.0;
  printf("Enter message to be encoded:\n");
  fgets(msg, 22, stdin);
  printf("Message to encode is: \n%s", msg);
  checkmsg(msg, cok, nspecial, flip, debug);
  packmsg(msg, dgen);
  printf("Status:\n Message: %s\n COK: %s\n NSPECIAL: %d\n Flip: %f\n", msg, cok, nspecial, flip);
  printf("Completed");
}


