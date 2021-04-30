#include "cycle.h"

//executeCycleCheck
// - Given a path, display all cyclic links under the path. Specifically,
//   traverse the given path recursively and display all links to a parent path.
int executeCycleCheck(char * filename) {

    struct folder * parent = malloc(1 * sizeof(struct folder));
    parent->canonicalPath = canonicalize_file_name(filename);
    parent->id = 0;
    fprintf(stderr, "CYCLE: Parent Con Path = %s\n",parent->canonicalPath);


    ////////// FROM HERE THIS IS A HYPOTHETICAL TEST ///////////
    fprintf(stderr, "TEST: START\n");
    parent->numChildren = 3;

    fprintf(stderr, "TEST: START ALLOC SUB\n");
    parent->childrenArr = allocateSubFolders(parent);
    fprintf(stderr, "TEST: END ALLOC SUB\n");

    //populate folder strucutes all the way down
    fprintf(stderr, "TEST: START CHECK\n");
    checkForCycles(parent);
    fprintf(stderr, "TEST: END CHECK\n");

    //check for cycles
    // fprintf(stderr, "TEST: START PRINT\n");
    // printFolderStructure(parent);
    // fprintf(stderr, "TEST: END PRINT\n");

    fprintf(stderr, "TEST: END\n");
    ////////// END OF HYPOTHETICAL TEST ///////////

    folderfree(parent);
    fprintf(stderr, "CYCLE: END\n");
    return RETURN_FAILURE;
}

struct folder * allocateSubFolders(struct folder * parent){
    int i = 0; //counter for the loop
    int idx = 0; //index for the array

    fprintf(stderr, "ALLOCSUB: START FROM PARENT ID = %d\n",parent->id);

    struct folder * tempArr = malloc(parent->numChildren * sizeof(struct folder));

    for(i = 0; i < parent->numChildren; i++){

        //Update Current Folder Metadata
        tempArr[i].id = parent->id + i + 1;
        getFolderMetadata(&tempArr[i]);

        // fprintf(stderr, "ALLOCSUB: index = %d, numchild = %d\n",tempArr[idx].id,tempArr[idx].numChildren);

        if(tempArr[idx].numChildren >= 1){
            tempArr[idx].childrenArr = allocateSubFolders(&tempArr[idx]);
        }

        // fprintf(stderr, "ALLOCSUB: FOLDER NODE: id = %d, numChildren = %d, isSymLink = %d, symlinkID = %d\n",tempArr[idx].id,tempArr[idx].numChildren,tempArr[idx].isSymLink,tempArr[idx].SymLinkID);
    }

    fprintf(stderr, "ALLOCSUB: END\n");

    return tempArr;
}

void getFolderMetadata(struct folder * curr){

    curr->numChildren = getNumChildren(curr->id);

    // canonicalize_file_name()


    if(isFolderSymLink(curr->id) == 1){
        curr->isSymLink = 1;
        curr->SymLinkID = getSymLinkID(curr->id);
    } else {
        curr->isSymLink = 0; //False
        curr->SymLinkID = -1;//Flase
    }

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

// Same as isFolderSymLink
int isLink(char* path){
    struct stat* inode = malloc(sizeof(*inode));
    lstat(path, inode);
    int mode = inode->st_mode & S_IFMT;
    return S_ISLNK(mode);
}

//TODO - symlink scanning, built curreltly for hypothetical test
int getSymLinkID(int id){
    if(id == 6){return 0;} //child2's left child is a link back to root
    if(id == 9){return 0;} //child3's right child is a link back to root
    if(id == 8){return 3;} //child3's left child is a link back to child3

    return -1;
}

//TODO - Not currently checking for cycles (when isSymLink is 1 and SymLinkID matches an ID amongst the sub folders)
void checkForCycles(struct folder * parent){
    int i;

    if(parent->numChildren == 0){
        return;
    }

    for(i = 0; i<parent->numChildren;i++){
        checkForCycles(&parent->childrenArr[i]);
        fprintf(stdout,"id: %d, islink: %d, linkID: %d",parent->childrenArr[i].id,parent->childrenArr[i].isSymLink, parent->childrenArr[i].SymLinkID);
    }

    return;
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

void printFolderStructure(struct folder * parent){
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
        printFolderStructure(&parent->childrenArr[i]);
        fprintf(stdout, "     ");
    }

    //Printing Parent Nodes
    fprintf(stdout, "\n %d \n",parent->id);

}

void folderfree(struct folder * parent){
    int i;

    if(parent->numChildren == 0){
        return;
    }

    for(i = 0; i<parent->numChildren;i++){
        folderfree(&parent->childrenArr[i]);
        free(&parent->childrenArr[i]);
    }

    //Free top most parent only
    if(parent->id == 0){
        free(parent);
    }

    return;

}

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
