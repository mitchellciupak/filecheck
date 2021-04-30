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