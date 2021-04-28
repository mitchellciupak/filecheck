#ifndef PERM_H
#define PERM_H

#include <unistd.h>
#include <errno.h>

#include "../shared.h"

int checkPermFlag(char * flagstring);
int executePermCheck(char * filename, int mode);
char * getErrorString(int errsv);
char * getModeString(int mode);
char * findPermFromFile(char * filename);

#endif