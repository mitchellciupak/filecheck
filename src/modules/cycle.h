#ifndef CYCLE_H
#define CYCLE_H

#include <sys/types.h>

#include "info.h"
#include "../shared.h"

struct folder {

    int ino;
    int lino;
    int isRelativeRoot;  //0 or 1
    int isSymLink;  //0 or 1
    int numChildren;//0 to INT_MAX

    struct folder * childrenArr;
    char * relativePath;
    char * canonicalPath;
};


int executeCycleCheck(char * path);
int getNumChildren(char * path);
struct folder * allocateSubFolders(struct folder * parent_dir);
void freefolderstruct(struct folder * parent);
void getRelativePath(char * parent_dir, char * foldername, char** path);

#endif