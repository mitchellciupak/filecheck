#include "cycle.h"

//executeCycleCheck
// - Given a path, display all cyclic links under the path. Specifically,
//   traverse the given path recursively and display all links to a parent path.
int executeCycleCheck(char * path) {

    //Init root
    struct folder * root = malloc(1 * sizeof(struct folder));
    root->isRelativeRoot = 1;
    root->relativePath = path;
    root->canonicalPath = canonicalize_file_name(path);

    root->numChildren = getNumChildren(root->canonicalPath);
    if(root->numChildren < 1) {
        fprintf(stderr,"executeCycleCheck: '%s' is not a directory or has no subfoders or links.\n", path);
        free(root->canonicalPath);
        free(root);
        return RETURN_FAILURE;
    }

    // fprintf(stderr,"%s",getRelativePath(root->relativePath,"child1"));

    root->childrenArr = allocateSubFolders(root);


    fprintf(stderr, "CYCLE: root Con Path = %s\n",root->canonicalPath);
    fprintf(stderr, "CYCLE: root Rel Path = %s\n",root->relativePath);
    fprintf(stderr, "CYCLE: root Num Sub-Paths = %d\n",root->numChildren);





    // ////////// FROM HERE THIS IS A HYPOTHETICAL TEST ///////////
    // fprintf(stderr, "TEST: START\n");
    // root->numChildren = 3;

    // fprintf(stderr, "TEST: START ALLOC SUB\n");
    // root->childrenArr = allocateSubFolders(root);
    // fprintf(stderr, "TEST: END ALLOC SUB\n");

    // //populate folder strucutes all the way down
    // fprintf(stderr, "TEST: START CHECK\n");
    // checkForCycles(root);
    // fprintf(stderr, "TEST: END CHECK\n");

    // //check for cycles
    // // fprintf(stderr, "TEST: START PRINT\n");
    // // printFolderStructure(root);
    // // fprintf(stderr, "TEST: END PRINT\n");

    // fprintf(stderr, "TEST: END\n");
    // ////////// END OF HYPOTHETICAL TEST ///////////

    // folderfree(root);
    // fprintf(stderr, "CYCLE: END\n");

    free(root->canonicalPath);
    free(root);

    return RETURN_SUCCESS;
}

struct folder * allocateSubFolders(struct folder * parent_dir) {
    int i = 0;
    struct dirent *dir_read;

    //Allocate Array of Subfolders //TODO - free
    struct folder * subfolders = malloc(parent_dir->numChildren * sizeof(struct folder));

    //Open Parent Directory
    DIR * dir = opendir(parent_dir->canonicalPath);

    //Populate Child Directories
    while (((dir_read = readdir(dir)) != NULL) && (i<parent_dir->numChildren)) {
        fprintf(stderr, "any: %s\n",dir_read->d_name);
        if(dir_read->d_name[0] == '.') {continue;} //Ignore . and ..

        if(dir_read->d_type == DT_DIR){
            fprintf(stderr, "dir: %s\n",dir_read->d_name);
            subfolders[i].ino = dir_read->d_ino;
            subfolders[i].isRelativeRoot = 0;
            subfolders[i].isSymLink = 0;
            subfolders[i].relativePath = getRelativePath(parent_dir->relativePath,dir_read->d_name); //TODO - free
            fprintf(stderr, "6%s\n",subfolders[i].relativePath);
            subfolders[i].canonicalPath = canonicalize_file_name(subfolders[i].relativePath); //TODO - free
            fprintf(stderr, "6%s\n",subfolders[i].canonicalPath);
            subfolders[i].numChildren = getNumChildren(subfolders[i].canonicalPath);
            fprintf(stderr,"folder: %s, ino: %d, conPath: %s\n",dir_read->d_name,subfolders[i].ino,subfolders[i].canonicalPath);

            if(subfolders[i].numChildren > 0) {
                subfolders[i].childrenArr = allocateSubFolders(&subfolders[i]);
            }

            i++;
        }
        else if(dir_read->d_type == DT_LNK) {
            fprintf(stderr, "lnk: %s\n",dir_read->d_name);
            subfolders[i].ino = dir_read->d_ino;
            subfolders[i].isRelativeRoot = 0;
            subfolders[i].isSymLink = 1;
            subfolders[i].relativePath = getRelativePath(parent_dir->relativePath,dir_read->d_name); //TODO - free
            fprintf(stderr, "6%s\n",subfolders[i].relativePath);
            subfolders[i].canonicalPath = canonicalize_file_name(subfolders[i].relativePath); //TODO - free
            fprintf(stderr, "6%s\n",subfolders[i].canonicalPath);
            fprintf(stderr,"folder: %s, ino: %d, conPath: %s\n",dir_read->d_name,subfolders[i].ino,subfolders[i].canonicalPath);

            //allocate and read into
            //check if sybolic link is beneath relative root
            // if it is print it out
            // if it is not then act like it is normal
            // do i need to handle c4?

            i++;
        }
    }

    closedir(dir);
    return subfolders;
}

char * getRelativePath(char * parent_dir, char * foldername){
    int plen = strlen(parent_dir);
    int flen = strlen(foldername);

    if (parent_dir[plen-1] != '/'){
        char * relpath = calloc(0,(plen+flen+1) * sizeof(char));
        strcat(relpath,parent_dir);
        strcat(relpath,"/");
        strcat(relpath,foldername);
        return relpath;
    } else {
        char * relpath = calloc(0,(plen+flen) * sizeof(char));
        strcat(relpath,parent_dir);
        strcat(relpath,foldername);
        return relpath;
    }
}

/*
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
*/

int getNumChildren(char * path){
    int count = 0;
    struct dirent *dir_read;

    if(path == NULL){
        fprintf(stderr,"getNumChildren: path is NULL\n");
        return -1;
    }

    //Open Dir
    DIR * dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr,"getNumChildren: Cannot open as directory '%s'\n", path);
        return -1;
    }

    //Count Dir's Subfolders
    while ((dir_read = readdir(dir)) != NULL) {
        if(dir_read->d_name[0] == '.') {continue;} //Ignore . and ..

        if(dir_read->d_type == DT_DIR){
            count += 1;

        }
        else if(dir_read->d_type == DT_LNK) {
            count += 1;

        }
    }

    closedir(dir);
    return count;
}
/*

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
*/
