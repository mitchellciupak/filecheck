#include "info.h"

//executeInfoCheck
// - Given a path, display the metadata of the file. Specifically,
int executeInfoCheck(char * filename) {

    struct stat buf = {0};
    lstat(filename, &buf);

    fprintf(stdout,"\nfilecheck: information for %s:\n",filename);
    fprintf(stdout, "======================================\n");
    fprintf(stdout,"DeviceID:           %lu\n",buf.st_dev);
    fprintf(stdout,"UserID:             %u\n",buf.st_uid);
    fprintf(stdout,"GroupID:            %u\n",buf.st_gid);
    fprintf(stdout, "======================================\n");
    fprintf(stdout,"inode:              %lu\n",buf.st_ino);
    fprintf(stdout,"Permissions:        %s\n",findPermFromFile(filename));
    fprintf(stdout,"FileType:           %s\n",findFileTypeFromFile(filename));
    fprintf(stdout,"ParentDir:          %s\n",findPathToParentDirFromFile(filename));
    fprintf(stdout,"Number Hard Links:  %lu\n",buf.st_nlink);
    fprintf(stdout, "======================================\n");
    fprintf(stdout,"Size (Bytes):       %lu\n",buf.st_size);
    fprintf(stdout,"Blocksize:          %lu\n",buf.st_blksize);
    fprintf(stdout,"Blocks Allocated (512MB per block): %lu\n",buf.st_blocks);
    fprintf(stdout, "======================================\n");
    fprintf(stdout,"DateTimeLastAcessed:       %lld.%.9ld\n",(long long) buf.st_atim.tv_sec,buf.st_atim.tv_nsec);
    fprintf(stdout,"DateTimeLastModified:      %lld.%.9ld\n",(long long) buf.st_mtim.tv_sec,buf.st_mtim.tv_nsec);
    fprintf(stdout,"DateTimeLastStatusChange:  %lld.%.9ld\n",(long long) buf.st_ctim.tv_sec,buf.st_ctim.tv_nsec);
    return RETURN_SUCCESS;
}

char * findFileTypeFromFile(char * filename){
    //TODO - does this mean read for file extention or is there something we can call
    return "NOTDONE";
}

char * findPathToParentDirFromFile(char * filename){
    //TODO - print the full path, basically pwd but cant call that
    return "NOTDONE";
}