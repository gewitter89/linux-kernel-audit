// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * net/core/skbuff.c - Socket buffer management routines
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../include/linux/skbuff.h"

static void __skb_frag_unref(skb_frag_t *frag, void *head) {
    if (frag && frag->page) {
        frag->page = NULL;
    }
}

void skb_release_data(struct sk_buff *skb) {
    struct skb_shared_info *shinfo = skb->shinfo;
    int i;

    if (!shinfo)
        return;

    /*
     * VULNERABLE: Direct decrement loop without memory barrier.
     * Can trigger out-of-order execution on weakly-ordered CPUs.
     */
    for (i = 0; i < shinfo->nr_frags; i++) {
        __skb_frag_unref(&shinfo->frags[i], skb->head);
    }
}
