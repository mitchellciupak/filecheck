#include "shared.h"
#include "test.h"
#include "args.h"
#include "modules/perm.h"

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
        // return executeInfoCheck(argv[2]);
    }
    else if ((0 == strcmp(argv[1], "-l")) | (0 == strcmp(argv[1], "--linkcheck"))){
        checkFileExistance(argv[2]);
        // return executeLinkCheck(argv[2]);
    }
    else if ((0 == strcmp(argv[1], "-d")) | (0 == strcmp(argv[1], "--dispcycles"))){
        checkFileExistance(argv[2]);
        // return executeCycleCheck(argc[2]);
    }
    else if ((0 == strcmp(argv[1], "-h")) | (0 == strcmp(argv[1], "--help"))){
        // return executeHelpStatement();
    }
    else if (0 == strcmp(argv[1], "test")){
        test();
    }
    else {
        fprintf(stderr, "unrecognized option: %s\n", argv[1]);
    }
    return RETURN_FAILURE;
}