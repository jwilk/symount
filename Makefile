# Copyright © 2022 Jakub Wilk <jwilk@jwilk.net>
# SPDX-License-Identifier: MIT

CFLAGS ?= -g -O2
CFLAGS += -Wall -Wformat -Wextra -pedantic

.PHONY: all
all: symount

symount: symount.c

.PHONY: clean
clean:
	rm -f symount

# vim:ts=4 sts=4 sw=4 noet
