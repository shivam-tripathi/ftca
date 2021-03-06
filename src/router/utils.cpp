#include "utils.h"

Packet Pack::get_default_packet () {
    return packet;
}

void *sockaddr_to_in(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa) -> sin_addr);
    }
    else {
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }
}

int hostname_to_ip(char * hostname , char* ip) {
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL) {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++) {
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }
    return 1;
}

int setnonblock (int fd) {
    int flags;

    flags = fcntl(fd, F_GETFL);
    if (flags < 0) {
        return flags;
    }

    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0) {
        return -1;
    }
    return 0;
}