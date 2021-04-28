#include "perm.h"

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
         return executePermCheck_R(filename);
    }
    else if (flag == 2) {
         return executePermCheck_W(filename);
    }
    else if (flag == 3) {
         return executePermCheck_W(filename);
    }
    else if (flag == 4) {
         return executePermCheck_W(filename);
    }
    else if (flag == 5) {
         return executePermCheck_W(filename);
    }
    else if (flag == 6) {
         return executePermCheck_W(filename);
    }

    return RETURN_FAILURE;
}

//TODO - write these once you find out what liberaries to use
int executePermCheck_R(char * filename) {return EXIT_SUCCESS;}
int executePermCheck_W(char * filename) {return EXIT_SUCCESS;}
int executePermCheck_X(char * filename) {return EXIT_SUCCESS;}
int executePermCheck_RX(char * filename) {return EXIT_SUCCESS;}
int executePermCheck_RW(char * filename) {return EXIT_SUCCESS;}
int executePermCheck_WX(char * filename) {return EXIT_SUCCESS;}