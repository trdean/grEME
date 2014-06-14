#ifndef GETPFX1_H_
#define GETPFX1_H_

void getpfx1(char *callsign, int k);
#define NZ = 338;
#define NZ2 = 12;
extern const char sfx[12];
  //Use pfx as a placeholder so 1 starts with 1A to align with fortran version.
extern const char* pfx[339];

#endif
