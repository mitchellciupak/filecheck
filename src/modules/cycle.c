#include "cycle.h"

typedef struct {
    int isTopParentDir;//0 or 1
    int isSymLink;  //0 or 1
    int numChildren;//0 to INT_MAX
    folder * childrenArr;
} folder;

//executeCycleCheck
// - Given a path, display all cyclic links under the path. Specifically,
//   traverse the given path recursively and display all links to a parent path.
int executeCycleCheck(char * filename) {

    folder * parent = malloc(1 * sizeof(folder));

    //populate folder strucutes all the way down

    //check for cycles

    folderfree(parent);
    return RETURN_FAILURE;
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
    if(top->isTopParentDir == 1){
        free(top);
    }

}