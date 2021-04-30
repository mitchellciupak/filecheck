#ifndef CYCLE_H
#define CYCLE_H

#include "../shared.h"

int executeCycleCheck(char * filename);
int getNumChildren(int id);
int isFolderSymLink(int id);
int getSymLinkID(int id);
void checkForCycles(folder * parent);
void printFolderStructure(folder * parent);
void folderfree(folder * top)

#endif