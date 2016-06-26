#include "config.h"

// 目前只支持1个MAC地址，即所有NIC都bond到一起
struct ether_addr ust_eth_addr;

uint32_t ust_ip_addr;
uint32_t ust_ip_mask;
uint32_t ust_ip_gw;

struct rte_mempool *ust_pktmbuf_pool;
