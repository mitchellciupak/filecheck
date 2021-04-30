#ifndef MAIN_H
#define MAIN_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#define RETURN_FAILURE 0
#define RETURN_SUCCESS 1

#define PERM_SIZE 9

int executeHelpStatement();

struct stat;

#endif