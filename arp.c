#include <stdint.h>
#include <rte_ether.h>
#include <rte_ip.h>

#include "config.h"

enum arp_hrd_format {
    arp_hrd_ethernet = 1,
};

enum arp_opcode {
    arp_op_request = 1,
    arp_op_reply = 2,
};

struct arphdr {
    uint16_t ar_hrd;                        /* hardware address format */
    uint16_t ar_pro;                        /* protocol address format */
    uint8_t ar_hln;                         /* hardware address length */
    uint8_t ar_pln;                         /* protocol address length */
    uint16_t ar_op;                         /* arp opcode */

    struct ether_addr ar_sha;       /* sender hardware address */
    uint32_t ar_sip;                        /* sender ip address */
    struct ether_addr ar_tha;       /* targe hardware address */
    uint32_t ar_tip;                        /* target ip address */

    uint8_t pad[18];
} __attribute__((packed));

struct arp_queue_entry {
    uint32_t ip;            /* target ip address */
    int nif_out;            /* output interface number */
    uint32_t ts_out;        /* last sent timestamp */

    TAILQ_ENTRY(arp_queue_entry) arp_link;
};

static int
process_request(struct arphdr *arph)
{
    return 0;
}

int
arp_input(struct rte_mbuf *m)
{
    struct arphdr *arph;
    int rc;

    arph = rte_pktmbuf_mtod(m, struct arphdr *);
    if (ust_ip_addr != be32toh(arph->ar_tip)) {
        goto out;
    }

    switch (be16toh(arph->ar_op)) {
    default:
        break;
    case arp_op_request:
        rc = process_request(arph);
        break;
    case arp_op_reply:
        break;
    }

out:
    rte_pktmbuf_free(m);
    return rc;
}

int
arp_output(struct rte_mbuf *mbuf)
{
    return 0;
}


