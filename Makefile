CFLAGS := -Wall -Werror

GCC := gcc

BASE_FILES := address.c argon2.c blake2b.c core.c encoding.c nimiq_native.c ref.c ed25519/collective.c ed25519/fe.c ed25519/ge.c ed25519/keypair.c \
    ed25519/memory.c ed25519/sc.c ed25519/seed.c ed25519/sha512.c ed25519/sign.c ed25519/verify.c

ALL_TARGETS := vanity_generate

default: vanity_generate

vanity_generate: $(BASE_FILES) vanity_generate.c
	$(GCC) $(CFLAGS) -O3 -o $@ $^

clean:
	rm -f $(ALL_TARGETS)
