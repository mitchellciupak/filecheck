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
        freefolderstruct(root);
        return RETURN_FAILURE;
    }

    root->childrenArr = allocateSubFolders(root);


    // fprintf(stderr, "CYCLE: root Con Path = %s\n",root->canonicalPath);
    // fprintf(stderr, "CYCLE: root Rel Path = %s\n",root->relativePath);
    // fprintf(stderr, "CYCLE: root Num Sub-Paths = %d\n",root->numChildren);

    freefolderstruct(root);
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
            // fprintf(stderr, "dir: %s\n",dir_read->d_name);
            subfolders[i].ino = dir_read->d_ino;
            subfolders[i].isRelativeRoot = 0;
            subfolders[i].isSymLink = 0;
            subfolders[i].relativePath = getRelativePath(parent_dir->relativePath,dir_read->d_name); //TODO - free
            // fprintf(stderr, "rel ->%s\n",subfolders[i].relativePath);
            subfolders[i].canonicalPath = canonicalize_file_name(subfolders[i].relativePath); //TODO - free
            subfolders[i].numChildren = getNumChildren(subfolders[i].canonicalPath);
            // fprintf(stderr,"folder: %s, ino: %d, conPath: %s\n",dir_read->d_name,subfolders[i].ino,subfolders[i].canonicalPath);

            if(subfolders[i].numChildren > 0) {
                subfolders[i].childrenArr = allocateSubFolders(&subfolders[i]);
            }

            i++;
        }
        else if(dir_read->d_type == DT_LNK) {
            // fprintf(stderr, "lnk: %s\n",dir_read->d_name);
            subfolders[i].ino = dir_read->d_ino;
            subfolders[i].isRelativeRoot = 0;
            subfolders[i].isSymLink = 1;
            subfolders[i].relativePath = getRelativePath(parent_dir->relativePath,dir_read->d_name); //TODO - free
            // fprintf(stderr, "rel -> %s\n",subfolders[i].relativePath);
            subfolders[i].canonicalPath = canonicalize_file_name(subfolders[i].relativePath); //TODO - free
            // fprintf(stderr,"folder: %s, ino: %d, conPath: %s\n",dir_read->d_name,subfolders[i].ino,subfolders[i].canonicalPath);
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
        char * relpath = calloc(0,(plen+flen+2) * sizeof(char));
        strcat(relpath,parent_dir);
        strcat(relpath,"/");
        strcat(relpath,foldername);
        // strcat(relpath,"/n");
        return relpath;
    } else {
        char * relpath = calloc(0,(plen+flen) * sizeof(char));
        strcat(relpath,parent_dir);
        strcat(relpath,foldername);
        return relpath;
    }
}

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

void freefolderstruct(struct folder * parent) {
    int i = 0;

    free(parent->canonicalPath);
    free(parent->relativePath);

    for(i = 0; i<parent->numChildren; i++){
        freefolderstruct(parent->childrenArr[i]);
    }

    free(parent->childrenArr);

    if(parent->isRelativeRoot == 1){
        free(parent);
    }

    return;
}