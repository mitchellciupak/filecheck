#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "args.h"

// https://engineering.purdue.edu/~ee469/labs_2021/lab5_regular.html

int main(int argc, char **argv) {
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "filecheck: inorrect number of arguments. Run %s -h or --help for usage\n", argv[0]);
    } else if ((0 == strcmp(argv[1], "-p")) | (0 == strcmp(argv[1], "--permcheck"))){
        checkFileExistance(argv[3]);
        //TODO - add flag check
        test();
    } else if ((0 == strcmp(argv[1], "-i")) | (0 == strcmp(argv[1], "--info"))){
        checkFileExistance(argv[2]);
    } else if ((0 == strcmp(argv[1], "-l")) | (0 == strcmp(argv[1], "--linkcheck"))){
        checkFileExistance(argv[3]);
    } else if ((0 == strcmp(argv[1], "-d")) | (0 == strcmp(argv[1], "--dispcycles"))){
        checkFileExistance(argv[3]);
    } else if ((0 == strcmp(argv[1], "-h")) | (0 == strcmp(argv[1], "--help"))){
        checkFileExistance(argv[3]);
    } else if (0 == strcmp(argv[1], "test")){
        checkFileExistance(argv[3]);
    } else {
        fprintf(stderr, "unrecognized option: %s\n", argv[1]);
    }
    return 0;
}