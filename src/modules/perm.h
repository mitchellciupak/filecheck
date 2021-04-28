#ifndef PERM_H
#define PERM_H

#include "../shared.h"

int checkPermFlag(char * flagstring);
int executePermCheck(char * filename, int flag);

int executePermCheck_R(char * filename);
int executePermCheck_W(char * filename);
int executePermCheck_X(char * filename);
int executePermCheck_RX(char * filename);
int executePermCheck_RW(char * filename);
int executePermCheck_WX(char * filename);

#endif