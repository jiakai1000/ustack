#ifndef __USTACK_TCP_H
#define __USTACK_TCP_H

#include <stdint.h>
#include <sys/socket.h>
#include <rte_mbuf.h>


typedef struct tcp_s tcp_t;
typedef int(*tcp_connect_cb)(tcp_t *tcp);
typedef int(*tcp_listen_cb)(tcp_t *tcp);
typedef int(*tcp_recv_cb)(tcp_t *tcp, struct rte_mbuf *mbuf);
typedef int(*tcp_sent_cb)(tcp_t *tcp, struct rte_mbuf *mbuf);

typedef enum {
    TCP_SYN,
} tcp_state_t;

struct tcp_s {
    union {
        tcp_connect_cb connect_cb;
        tcp_listen_cb listen_cb;
    };
    tcp_sent_cb sent_cb;
    tcp_recv_cb recv_cb;

    tcp_state_t state;
};

int tcp_init(tcp_t *tcp, tcp_sent_cb sent_cb, tcp_recv_cb recv_cb);
int tcp_connect(tcp_t *tcp, const struct sockaddr *addr, socklen_t addrlen, tcp_connect_cb cb);
int tcp_listen(tcp_t *tcp);
int tcp_close(tcp_t *tcp);


#endif
