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

typedef struct {
    int id;
    int isSymLink;  //0 or 1
    int SymLinkID;
    int numChildren;//0 to INT_MAX
    folder * childrenArr;
} folder;

//executeCycleCheck
// - Given a path, display all cyclic links under the path. Specifically,
//   traverse the given path recursively and display all links to a parent path.

int findLinkExample(char * path) {
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

int executeCycleCheck(char * filename) {

    folder * parent = malloc(1 * sizeof(folder));
    parent->id = 0;

    ////////// FROM HERE THIS IS A HYPOTHETICAL TEST ///////////
    parent->numChildren = 3;
    parent->childrenArr = allocateSubFolders(parent);

    checkForCycles(parent);
    printFolderStructure(parent);

    ////////// END OF HYPOTHETICAL TEST ///////////

    //populate folder strucutes all the way down

    //check for cycles

    folderfree(parent);
    return RETURN_FAILURE;
}

folder * allocateSubFolders(folder * parent){
    int i = 0;
    folder * tempArr = malloc(parent->numChildren * sizeof(folder));

    for(i = 0; i < parent->numChildren; i++){
        tempArr[i].id = parent->id + i;
        tempArr[i].numChildren = getNumChildren(tempArr[i].id);
        tempArr[i].childrenArr = allocateSubFolders(&tempArr[i]);

        if(isFolderSymLink(tempArr[i].id) == 1){
            tempArr[i].isSymLink = 1;
            tempArr[i].SymLinkID = getSymLinkID(tempArr[i].id);
        } else {
            tempArr[i].isSymLink = 0; //False
            tempArr[i].SymLinkID = -1;//Flase
        }
    }

    return tempArr;
}

//TODO - directory scanning, built curreltly for hypothetical test
int getNumChildren(int id){
    if(id == 0){return 3;} //top parent
    if((id == 1) | (id == 2) | (id == 3)) {return 2;} //top parent's imeediate children
    return 0; //else for top prarent's grand children
}

//TODO - symlink scanning, built curreltly for hypothetical test
int isFolderSymLink(int id){
    if((id == 6) | (id == 8) | (id == 9)) {return 1;}
    return 0;
}

//TODO - symlink scanning, built curreltly for hypothetical test
int getSymLinkID(int id){
    if(id == 6){return 0;} //child2's left child is a link back to root
    if(id == 9){return 0;} //child3's right child is a link back to root
    if(id == 8){return 3;} //child3's left child is a link back to child3
}

//TODO - Not currently checking for cycles (when isSymLink is 1 and SymLinkID matches an ID amongst the sub folders)
void checkForCycles(folder * parent){
    int i;

    if(parent->numChildren == 0){
        return;
    }

    for(i = 0; i<parent->numChildren;i++){
        checkForCycles(parent->childrenArr[i]);
        // fprinf(stdout,"id: %d",parent->childrenArr[i].id);
    }
}

void printFolderStructure(folder * parent){
    int i;

    // Printing Leaf Nodes
    if(parent->numChildren == 0){
        fprintf(stdout, "%d",parent->id);

        if(parent->isSymLink == 1){
            fprintf(stdout, "->%d",parent->SymLinkID);
        }

        return;
    }

    for(i = 0; i<parent->numChildren;i++){
        printFolderStructure(parent->childrenArr[i]);
        fprintf(stdout, "     ");
    }

    //Printing Parent Nodes
    fprintf(stdout, "\n %d \n",parent->id);

}

void folderfree(folder * parent){
    int i;

    if(parent->numChildren == 0){
        return;
    }

    for(i = 0; i<parent->numChildren;i++){
        folderfree(parent->childrenArr[i]);
        free(parent->childrenArr[i]);
    }

    //Free top most parent only
    if(parent->id == 0){
        free(parent);
    }

}

