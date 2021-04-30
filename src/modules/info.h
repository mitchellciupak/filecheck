#ifndef INFO_H
#define INFO_H

#define PATH_MAX 4096
#define MODE_MAX 20

#include <sys/types.h>
#include <assert.h>

#include "../shared.h"
#include "perm.h"

int executeInfoCheck(char * filename);
void findFileTypeFromFile(struct stat* inode, char* mode_arr);
void findPathToParentDirFromFile(char * filename, char** path);


#endif
