#include "perm.h"
#include <errno.h>

// checkPermFlag
// - return an int value according to mode for access to determine which flag or combination of flags is being called
int checkPermFlag(char * flagstring) {
    /*
    0 - error occured
    */

    if (strlen(flagstring) > 3) {
        fprintf(stderr, "filecheck: %s is of incorrect length. Run ./flagstring -h or --help for usage\n", flagstring);
        return RETURN_FAILURE;
    }

    if (0 == strcmp(flagstring, "r")){
        return R_OK; //4
    }
    else if (0 == strcmp(flagstring, "w")){
        return W_OK; //2
    }
    else if (0 == strcmp(flagstring, "x")){
        return X_OK; //1
    }
    else if ((0 == strcmp(flagstring, "rx")) | (0 == strcmp(flagstring, "xr"))){
        return (R_OK | X_OK);
    }
    else if ((0 == strcmp(flagstring, "rw")) | (0 == strcmp(flagstring, "wr"))){
        return (R_OK | W_OK);
    }
    else if ((0 == strcmp(flagstring, "wx")) | (0 == strcmp(flagstring, "xw"))){
        return (W_OK | X_OK);
    }
    else if ((0 == strcmp(flagstring, "rwx")) | (0 == strcmp(flagstring, "xrw"))){
        return (R_OK | W_OK | X_OK);
    }

    fprintf(stderr, "filecheck: %s is not r,w,rw,x,rx,wx,rwx. Run ./flagstring -h or --help for usage\n", flagstring);
    return RETURN_FAILURE;
}

//executePermCheck
// - Check the permissions of the given file path. If the current user does not have permissions for the file,
//   give the exact and precise reason why the access is denied.
int executePermCheck(char * filename, int mode) {

    if(mode == 0){
        return RETURN_FAILURE;
    }

    if(access(filename, mode) == 0){
        fprintf(stdout,"Can %s access %s\n",getModeString(mode),filename);
        return RETURN_SUCCESS;
    }
    int errsv = errno;
    fprintf(stderr,"Cannot %s access '%s'. Reason #%d: %s.\n",getModeString(mode),filename,errsv,getErrorString(errsv));
    return RETURN_FAILURE;
}

char * getModeString(int mode){

    if(mode == 4){ return "r";}
    if(mode == 2){ return "w";}
    if(mode == 1){ return "x";}
    if(mode == 6){ return "rw";}
    if(mode == 5){ return "rx";}
    if(mode == 3){ return "wx";}
    if(mode == 7){ return "rwx";}

    return "NULL ERROR OCCURED";
}

char * getErrorString(int errsv){

    if(errsv == 13){
        return "EACCES Permission denied (POSIX.1-2001)";
    }

    return "NULL ERROR OCCURED";
}