#include "cycle.h"
#include "unistd.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "info.h"
#include "string.h"

int isLink(char* path){
    struct stat* inode = malloc(sizeof(*inode));
    lstat(path, inode);
    int mode = inode->st_mode & S_IFMT;
    return S_ISLNK(mode);
}

// Top is the directory that contains the path to be inspected.
// Path is truncated with each call, until it is the top directory.
void checkForLinks(char * path, int* a_ct){
    char* file = strrchr(path, '/');
    file = file + 1;
    char* newString = malloc((int)(file - path) * sizeof(*newString));

    if(isLink(path)){
        char* real = malloc(sizeof(*path) * PATH_MAX);
        real = realpath(path, NULL);
        if(strncmp(real, path, strlen(real))==0){
            // path has realpath in it!
            printf("Path %s is symlink to %s\n", path, real);
            *a_ct += 1;
        }
    }

    if(file-1 == path) return; // Base case!
    strncpy(newString, path, file - path - 1);
    checkForLinks(newString, a_ct);
    free(newString);
}

void recursePrint(char * path){
    char* file = strrchr(path, '/');
    file = file + 1;
    char* newString = malloc((int)(file - path) * sizeof(*newString));
    if(file-1 == path) return; // Base case!
    strncpy(newString, path, file - path - 1);
    recursePrint(newString);
    free(newString);
}

//executeCycleCheck
// - Given a path, display all cyclic links under the path. Specifically,
//   traverse the given path recursively and display all links to a parent path.
int executeCycleCheck(char * path) {
    int ct = 0;
    char* abs_path = malloc(sizeof(*abs_path) * PATH_MAX);
    // Needs absolute path to directory /a/b/c if /a is at root
    if(isLink(path)){
        char* real = malloc(sizeof(*path) * PATH_MAX);
        real = realpath(path, NULL);
        if(strncmp(real, path, strlen(real))==0){
            // path has realpath in it!
            printf("Path %s is symlink to %s\n", path, real);
            ct += 1;
        }
    }
    else{
        abs_path = realpath(path, NULL);
        checkForLinks(abs_path, &ct);
    }
    printf("%d link%s found\n", ct, ct == 1 ? "" : "s");
    free(abs_path);
    return RETURN_FAILURE;
}
