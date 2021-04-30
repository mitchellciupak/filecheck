#include "shared.h"
#include "test.h"
#include "args.h"
#include "modules/perm.h"
#include "modules/info.h"
#include "modules/link.h"
#include "modules/cycle.h"


int main(int argc, char **argv) {

    int ct = 0;
    int file = argc - 1;

    if (argc < 2) {
        fprintf(stderr, "filecheck: incorrect number of arguments. Run %s -h or --help for usage\n", argv[0]);
        return RETURN_FAILURE;
    }

    ct++; // The file name
    while(ct < argc - 1){
        checkFileExistance(argv[file]);

        if ((0 == strcmp(argv[ct], "-p")) | (0 == strcmp(argv[ct], "--permcheck"))){
            executePermCheck(argv[file], checkPermFlag(argv[ct + 1]));
            ct++;
        }
        else if ((0 == strcmp(argv[ct], "-i")) | (0 == strcmp(argv[ct], "--info"))){
            executeInfoCheck(argv[file]);
        }
        else if ((0 == strcmp(argv[ct], "-l")) | (0 == strcmp(argv[ct], "--linkcheck"))){
            executeLinkCheck(argv[file]);
        }
        else if ((0 == strcmp(argv[ct], "-d")) | (0 == strcmp(argv[ct], "--dispcycles"))){
            executeCycleCheck(argv[file]);
        }
        else if ((0 == strcmp(argv[ct], "-h")) | (0 == strcmp(argv[ct], "--help"))){
            executeHelpStatement();
        }
        else if (0 == strcmp(argv[1], "test")){
            test();
        }
        else {
            fprintf(stderr, "unrecognized option: %s\n", argv[ct]);
        }
        ct++;
    }
    return RETURN_FAILURE;
}