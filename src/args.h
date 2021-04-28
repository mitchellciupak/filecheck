#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>
#include <unistd.h>
#include "shared.h"

int find_arg(int argc, char* argv[], char *arg);
int find_int_arg(int argc, char **argv, char *arg, int def);

float find_float_arg(int argc, char **argv, char *arg, float def);
char *find_char_arg(int argc, char **argv, char *arg, char *def);

void checkFileExistance(char * filename);
bool isFileExist(char * filename);

#endif
