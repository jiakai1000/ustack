#include <stdint.h>
#include <assert.h>
#include <rte_ether.h>
#include <rte_ip.h>
#include <rte_arp.h>
#include <rte_table_hash.h>
#include <rte_jhash.h>
#include <rte_rwlock.h>

#include "config.h"

//enum arp_hrd_format {
//    arp_hrd_ethernet = 1,
//};
//
struct arp_queue_entry {
    uint32_t ip;            /* target ip address */
    int nif_out;            /* output interface number */
    uint32_t ts_out;        /* last sent timestamp */

    TAILQ_ENTRY(arp_queue_entry) link;
};

//static void *arp_table;
static TAILQ_HEAD(, arp_queue_entry) list;
static rte_rwlock_t lock;

static int
process_request(struct arp_hdr *arph)
{
    return 0;
}

int
arp_input(struct rte_mbuf *m)
{
    struct arp_hdr *arph;
    int rc;

    arph = rte_pktmbuf_mtod(m, struct arp_hdr *);
    if (ust_ip_addr != rte_be_to_cpu_32(arph->arp_data.arp_tip)) {
        goto out;
    }

    switch (rte_be_to_cpu_16(arph->arp_op)) {
    default:
        rc = -EINVAL;
        break;
    case ARP_OP_REQUEST:
        rc = process_request(arph);
        break;
    case ARP_OP_REPLY:
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

int 
arp_init()
{
    //const struct rte_table_ops *ops = &rte_table_hash_key8_ext_ops;
    //struct rte_table_hash_key8_ext_params hash_params = {
    //    .n_entries = 1 << 10,
    //    .n_entries_ext = 1 << 4,
    //    //.f_hash = pipeline_test_hash,
    //    //.seed = 0,
    //    //.signature_offset = APP_METADATA_OFFSET(1),
    //    //.key_offset = APP_METADATA_OFFSET(32),
    //    .key_mask = NULL,
    //};

    //uint32_t aa = rte_jhash_1word(0x1234, 0);
    //assert(!arp_table);
    //arp_table = ops->f_create(&hash_params, 0, 1);
    //if (arp_table != NULL)
    //    return -1;

    rte_rwlock_init(&lock);

    return 0;
}
