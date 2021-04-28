#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "args.h"

#define RETURN_FAILURE 0
#define RETURN_SUCCESS 1

// https://engineering.purdue.edu/~ee469/labs_2021/lab5_regular.html

int checkPermFlag(char * flagstring);
int executePermCheck(char * filename, int flag);

int main(int argc, char **argv) {

    if (argc < 2 || argc > 4) {
        fprintf(stderr, "filecheck: inorrect number of arguments. Run %s -h or --help for usage\n", argv[0]);
    }
    else if ((0 == strcmp(argv[1], "-p")) | (0 == strcmp(argv[1], "--permcheck"))){
        checkFileExistance(argv[3]);
        return executePermCheck(argv[3], checkPermFlag(argv[2]));
    }
    else if ((0 == strcmp(argv[1], "-i")) | (0 == strcmp(argv[1], "--info"))){
        checkFileExistance(argv[2]);
    }
    else if ((0 == strcmp(argv[1], "-l")) | (0 == strcmp(argv[1], "--linkcheck"))){
        checkFileExistance(argv[3]);
    }
    else if ((0 == strcmp(argv[1], "-d")) | (0 == strcmp(argv[1], "--dispcycles"))){
        checkFileExistance(argv[3]);
    }
    else if ((0 == strcmp(argv[1], "-h")) | (0 == strcmp(argv[1], "--help"))){
        checkFileExistance(argv[3]);
    }
    else if (0 == strcmp(argv[1], "test")){
        checkFileExistance(argv[3]);
    }
    else {
        fprintf(stderr, "unrecognized option: %s\n", argv[1]);
    }
    return RETURN_FAILURE;
}

// checkPermFlag
// - return an int value to determine which flag or combination of flags is being called
int checkPermFlag(char * flagstring) {
    /*
    0 - error occured
    1 - r
    2 - w
    3 - x
    4 - [rx|xr]
    5 - [rw|wr]
    6 - [wx|xw]
    */

    if (strlen(flagstring) > 2) {
        fprintf(stderr, "filecheck: %s is of incorrect length. Run ./flagstring -h or --help for usage\n", flagstring);
        exit(0);
    }

    if (0 == strcmp(flagstring, "r")){
        return 1;
    }
    else if (0 == strcmp(flagstring, "w")){
        return 2;
    }
    else if (0 == strcmp(flagstring, "x")){
        return 3;
    }
    else if ((0 == strcmp(flagstring, "rx")) | (0 == strcmp(flagstring, "xr"))){
        return 4;
    }
    else if ((0 == strcmp(flagstring, "rw")) | (0 == strcmp(flagstring, "wr"))){
        return 5;
    }
    else if ((0 == strcmp(flagstring, "wx")) | (0 == strcmp(flagstring, "xw"))){
        return 6;
    }

    return RETURN_FAILURE;
}

//executePermCheck
// - Check the permissions of the given file path. If the current user does not have permissions for the file,
//   give the exact and precise reason why the access is denied.
int executePermCheck(char * filename, int flag) {

    if (flag == 1) {
         return RETURN_SUCCESS;
    }

    return RETURN_FAILURE;
}