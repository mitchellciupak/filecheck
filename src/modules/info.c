#include "info.h"

//executeInfoCheck
// - Given a path, display the metadata of the file. Specifically,
int executeInfoCheck(char * filename) {
    char perm[PERM_SIZE+1];
    char mode[MODE_MAX];
    char* path = malloc(sizeof(*path) * PATH_MAX);
    struct stat* inode = malloc(sizeof(*inode));

    lstat(filename, inode);
    findPathToParentDirFromFile(filename, &path);

    findPermFromFile(inode, perm);
    findFileTypeFromFile(inode, mode);

    fprintf(stdout,"\nfilecheck: information for %s:\n", filename);
    fprintf(stdout, "======================================\n");
    fprintf(stdout,"DeviceID:           %lu\n", inode->st_dev);
    fprintf(stdout,"UserID:             %u\n", inode->st_uid);
    fprintf(stdout,"GroupID:            %u\n", inode->st_gid);
    fprintf(stdout, "======================================\n");
    fprintf(stdout,"inode:              %lu\n", inode->st_ino);
    fprintf(stdout,"Permissions:        %s\n", perm);
    fprintf(stdout,"FileType:           %s\n", mode);
    fprintf(stdout,"ParentDir:          %s\n", path);
    fprintf(stdout,"Number Hard Links:  %lu\n", inode->st_nlink);
    fprintf(stdout, "======================================\n");
    fprintf(stdout,"Size (Bytes):       %lu\n", inode->st_size);
    fprintf(stdout,"Blocksize:          %lu\n", inode->st_blksize);
    fprintf(stdout,"Blocks Allocated (512MB per block): %lu\n", inode->st_blocks);
    fprintf(stdout, "======================================\n");
    fprintf(stdout,"DateTimeLastAcessed:       %lld.%.9ld\n",(long long)  inode->st_atim.tv_sec, inode->st_atim.tv_nsec);
    fprintf(stdout,"DateTimeLastModified:      %lld.%.9ld\n",(long long)  inode->st_mtim.tv_sec, inode->st_mtim.tv_nsec);
    fprintf(stdout,"DateTimeLastStatusChange:  %lld.%.9ld\n",(long long)  inode->st_ctim.tv_sec, inode->st_ctim.tv_nsec);
    return RETURN_SUCCESS;
}

void findFileTypeFromFile(struct stat* inode, char* mode_arr){
    int mode = inode->st_mode & S_IFMT;
    if(S_ISREG(mode)) memcpy(mode_arr, "regular", MODE_MAX);
    else if(S_ISDIR(mode)) memcpy(mode_arr, "directory", MODE_MAX);
    else if(S_ISCHR(mode)) memcpy(mode_arr, "character device", MODE_MAX);
    else if(S_ISBLK(mode)) memcpy(mode_arr, "block device", MODE_MAX);
    else if(S_ISFIFO(mode)) memcpy(mode_arr, "FIFO", MODE_MAX);
    else if(S_ISLNK(mode)) memcpy(mode_arr, "symbolic link", MODE_MAX);
    else if(S_ISSOCK(mode)) memcpy(mode_arr, "socket", MODE_MAX);
    else memcpy(mode_arr, "no idea", MODE_MAX);
}

void findPathToParentDirFromFile(char * filename, char** path){
    char* full_path = malloc(PATH_MAX * sizeof(*full_path));
    int str_len;

    full_path = realpath(filename, NULL);
    char * file = strrchr(full_path, '/') + 1;
    str_len = strlen(full_path) - strlen(file);

    assert(str_len < PATH_MAX);
    if(str_len-1 == 0) strncpy(*path, "(root dir)", 12);
    else strncpy(*path, full_path, str_len-1);

    free(full_path);
}
