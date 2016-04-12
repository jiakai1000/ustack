#include <rte_ether.h>

int
arp_input(struct rte_mbuf *mbuf);
int
ipv4_input(struct rte_mbuf *mbuf);

int
eth_input(struct rte_mbuf *m)
{
    struct ether_hdr *eth;
    uint16_t type;
    int rc;
    
    eth = rte_pktmbuf_mtod(m, struct ether_hdr *);
    type = be16toh(eth->ether_type);

    if (!rte_pktmbuf_adj(m, sizeof(struct ether_hdr))) {
        return -EINVAL;
    }
    switch (type) {
    default:
        rc = -EINVAL;
        break;
    case ETHER_TYPE_IPv4:
        rc = ipv4_input(m);
        break;
    case ETHER_TYPE_ARP:
        rc = arp_input(m);
        break;
    }

    return rc;
}