#include "shared.h"

int executeHelpStatement() {
    fprintf(stdout, "\nUSAGE: ./filecheck [one or more options] <path>\n\n");
    fprintf(stdout, "[one or more options] are listed below\n");
    fprintf(stdout, "======================================\n");

    fprintf(stdout, "-p --permcheck [r|w|x]\n");
    fprintf(stdout, "-i --info\n");
    fprintf(stdout, "-l --linkcheckj\n");
    fprintf(stdout, "-d --dispcycles\n");

    return RETURN_SUCCESS;
}