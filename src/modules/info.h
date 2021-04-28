#ifndef INFO_H
#define INFO_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../shared.h"
#include "perm.h"

int executeInfoCheck(char * filename);
char * findFileTypeFromFile(char * filename);
char * findPathToParentDirFromFile(char * filename);


#endif