#include "perm.h"

// checkPermFlag
// - return an int value according to mode for access to determine which flag or combination of flags is being called
// - retutn of 0 means an incorrect value was returned and the system should be exited
int checkPermFlag(char * flagstring) {

    if (strlen(flagstring) > 3) {
        fprintf(stderr, "filecheck: %s is of incorrect length. Run ./flagstring -h or --help for usage.\n", flagstring);
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

    fprintf(stderr, "filecheck: %s is not r,w,rw,x,rx,wx, or rwx. Run ./flagstring -h or --help for usage.\n", flagstring);
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
    fprintf(stderr,"Cannot %s access '%s'. Reason #%d: %s\n",getModeString(mode),filename,errsv,getErrorString(errsv));
    return RETURN_FAILURE;
}

//getModeString
// - returns mode sting for stdout and stderr printing
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

//getErrorString
// - returns error sting for stderr printing
char * getErrorString(int errsv){

    if(errsv == 13){ return "EACCES: requested access denied to the file, or search permission is denied for one of the directories in the path prefix of pathname (POSIX.1-2001).";}
    if(errsv == 40){ return "ELOOP: Too many symbolic links were encountered in resolving pathname (POSIX.1-2001).";}
    if(errsv == 36){ return "ENAMETOOLONG: Pathname is too long (POSIX.1-2001).";}
    if(errsv == 2) { return "ENOENT: Pathname does not exist or is a dangling symbolic link (POSIX.1-2001).";}
    if(errsv == 20){ return "ENOTDIR: Not a directory (POSIX.1-2001).";}
    if(errsv == 30){ return "EROFS: Write permission was requested for a file on a read-only file system (POSIX.1-2001).";}
    if(errsv == 14){ return "EFAULT: Pathname points outside your accessible address space (POSIX.1-2001).";}
    if(errsv == 22){ return "EINVAL: Mode was incorrectly specified (POSIX.1-2001).";}
    if(errsv == 5) { return "EIO: An I/O error occurred (POSIX.1-2001).";}
    if(errsv == 12){ return "ENOMEM: Insufficient kernel memory was available (POSIX.1-2001).";}
    if(errsv == 26){ return "ETXTBSY: Write access was requested to an executable which is being executed (POSIX.1-2001).";}

    return "NULL ERROR OCCURED";
}

//TODO - fix output bug for writting to perm - it is not updating after initial update. This program is called in info.c
char * findPermFromFile(char * filename){
    char * perm[3] = {"-","-","-"};

    //Check for read
    if(access(filename, R_OK) == 0){
        perm[0] = "r";
    }

    //Check for write
    if(access(filename, W_OK) == 0){
        perm[1] = "w";
    }

    //Check for x
    if(access(filename, X_OK) == 0){
        perm[2] = "x";
    }

    return *perm;
}