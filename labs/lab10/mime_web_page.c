#include <stdio.h>
#include <string.h>

#include "mime_web_page.h"

// pathname is the pathname component of a URL
// if a corresponding file exists the client is sent
// a 200 header with a mime-type based on the files suffix
// with /etc/mime.types used to convert this suffix to a mime-type
// if the pathname doesn't have a suffix or this suffix can't be found
// in  /etc/mime.types DEFAULT_MIME_TYPE is assumed
// the header is followed by the file contents
//
// if a the file can't be opened
// a 404 header is sent with no body
void mime_web_page(char *pathname, FILE *client_stream) {

    // REPLACE WITH YOUR CODE
    fprintf(client_stream, HEADER_404);
    fprintf(client_stream, "You requested %s but function mime_web_page is unimplemented\n", pathname);

}
