CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2 -Iinclude

all: test

test: net/core/skbuff.c tests/test_skb_zerocopy.c
	$(CC) $(CFLAGS) net/core/skbuff.c tests/test_skb_zerocopy.c -o tests/runner
	./tests/runner

clean:
	rm -f tests/runner
