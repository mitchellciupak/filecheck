#include "cycle.h"

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
int executeCycleCheck(char * filename) {

    folder * parent = malloc(1 * sizeof(folder));
    parent->id = 0;

    ////////// FROM HERE THIS IS A HYPOTHETICAL TEST ///////////
    parent->numChildren = 3;
    parent->childrenArr = allocateSubFolders(parent);

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

        if(isFolderSymLink(tempArr[i].id)){
            tempArr[i].isSymLink = 1;
            tempArr[i].SymLinkID = getSymLinkID(tempArr[i].id);
        } else {
            tempArr[i].isSymLink = 0; //False
            tempArr[i].SymLinkID = -1;//Flase
        }
    }

    return tempArr;
}

void folderfree(folder * top){
    int i;

    if(top->numChildren == 0){
        return;
    }

    for(i = 0; i<top->numChildren;i++){
        folderfree(top->childrenArr[i]);
        free(top->childrenArr[i]);
    }

    //Free top most
    if(top->id == 0){
        free(top);
    }

}