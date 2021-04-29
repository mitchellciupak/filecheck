#ifndef INFO_H
#define INFO_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#include "../shared.h"
#include "perm.h"

int executeInfoCheck(char * filename);
void findFileTypeFromFile(struct stat* inode, char* mode_arr);
void findPathToParentDirFromFile(char * filename, char** path);


#endif