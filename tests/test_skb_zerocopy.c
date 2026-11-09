// Test harness for skbuff zero-copy barrier
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/linux/skbuff.h"

int main(void) {
    struct skb_shared_info shinfo = {0};
    struct sk_buff skb = {0};
    int dummy_page = 42;

    shinfo.nr_frags = 2;
    shinfo.flags = SKBFL_SHARED_FRAG;
    shinfo.frags[0].page = &dummy_page;
    shinfo.frags[1].page = &dummy_page;
    skb.shinfo = &shinfo;

    printf("[INFO] Testing skb_release_data zero-copy recycling...\n");
    skb_release_data(&skb);
    assert(shinfo.frags[0].page == NULL);
    assert(shinfo.frags[1].page == NULL);
    printf("[PASS] SKB release test passed successfully!\n");
    return 0;
}
