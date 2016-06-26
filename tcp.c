#include "tcp.h"
#include <rte_thash.h>

int 
tcp_connect(tcp_t *tcp, const struct sockaddr *addr, socklen_t addrlen, tcp_connect_cb cb)
{
    struct sockaddr_in *inaddr;

    switch (addr->sa_family) {
    case AF_INET:
        inaddr = (struct sockaddr_in *)addr;
        //inaddr->sin_addr.s_addr
        break;
    case AF_INET6:
    default:
        return -EAFNOSUPPORT;
    }
    //rte_softrss_be();
}
