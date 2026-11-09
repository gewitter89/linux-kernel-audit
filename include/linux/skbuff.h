/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef _LINUX_SKBUFF_H
#define _LINUX_SKBUFF_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_SKB_FRAGS 16
#define SKBFL_SHARED_FRAG (1 << 0)

typedef struct {
    uint32_t page_offset;
    uint32_t size;
    void *page;
} skb_frag_t;

struct skb_shared_info {
    uint8_t flags;
    uint8_t nr_frags;
    void *frag_list;
    skb_frag_t frags[MAX_SKB_FRAGS];
};

struct sk_buff {
    void *head;
    void *data;
    uint32_t len;
    uint32_t data_len;
    struct skb_shared_info *shinfo;
};

static inline bool skb_zcopy_is_shared(const struct sk_buff *skb) {
    return skb->shinfo && (skb->shinfo->flags & SKBFL_SHARED_FRAG);
}

void skb_release_data(struct sk_buff *skb);

#endif /* _LINUX_SKBUFF_H */
