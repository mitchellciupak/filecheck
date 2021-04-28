#include "link.h"

//executeLinkCheck
// - Given a path, check if the file has any hard links (you don't need to know the path) but just whether
//   a hard link exists or not.
int executeLinkCheck(char * filename) {

    struct stat buf = {0};
    lstat(filename, &buf);

    if(buf.st_nlink > 0){
        fprintf(stdout,"filecheck: %s has %lu hard links.\n",filename,buf.st_nlink);
        return RETURN_SUCCESS;
    }

    fprintf(stdout,"filecheck: %s has no hard links.\n",filename);
    return RETURN_SUCCESS;
}