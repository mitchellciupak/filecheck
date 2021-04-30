#ifndef CYCLE_H
#define CYCLE_H

#include <sys/types.h>

#include "info.h"
#include "../shared.h"

struct folder {

    int isRelativeRoot;  //0 or 1
    int isSymLink;  //0 or 1
    int numChildren;//0 to INT_MAX

    struct folder * childrenArr;
    char * relativePath;
    char * canonicalPath;
};


int executeCycleCheck(char * filename);
int getNumChildren(int id);
struct folder * allocateSubFolders(struct folder * parent);
int isFolderSymLink(int id);
int getSymLinkID(int id);
void checkForCycles(struct folder * parent);
void printFolderStructure(struct folder * parent);
void folderfree(struct folder * top);
void getFolderMetadata(struct folder * curr);

//ckemmet
int findLinkExample(char * path);
void recursePrint(char * path);
// int isLink(char* path);


#endif