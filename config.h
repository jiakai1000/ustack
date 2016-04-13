#ifndef __CONFIG_H
#define __CONFIG_H

#include <stdint.h>
#include <rte_ether.h>

extern struct ether_addr ust_eth_addr;

extern uint32_t ust_ip_addr;
extern uint32_t ust_ip_mask;
extern uint32_t ust_ip_gw;

extern struct rte_mempool *ust_pktmbuf_pool;

#endif
