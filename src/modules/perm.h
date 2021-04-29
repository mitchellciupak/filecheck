#ifndef PERM_H
#define PERM_H

#include <unistd.h>
#include <errno.h>

#include "../shared.h"

#define MODE_MASK 0777
enum Group {owner, group, others};

int checkPermFlag(char * flagstring);
int executePermCheck(char * filename, int mode);
char * getErrorString(int errsv);
char * getModeString(int mode);
void findPermFromFile(struct stat * filename, char perm[PERM_SIZE]);

#endif