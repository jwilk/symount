/* Copyright © 2022 Jakub Wilk <jwilk@jwilk.net>
 * SPDX-License-Identifier: MIT
 */

#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <unistd.h>

typedef char fdpath[25];

static void usage(FILE *fp)
{
    fprintf(fp, "Usage: symount SOURCE TARGET\n");
}

static int xopen(const char *path, fdpath xpath)
{
    int fd = open(path, O_PATH | O_NOFOLLOW);
    if (fd < 0) {
        perror(path);
        exit(1);
    }
    int n = sprintf(xpath, "/proc/self/fd/%d", fd);
    if (n < 0) {
        perror("sprintf()");
        exit(1);
    }
    return fd;
}

int main(int argc, char **argv)
{
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        usage(stdout);
        exit(0);
    }
    if (argc != 3) {
        usage(stderr);
        exit(1);
    }
    fdpath xsrc, xdst;
    int srcfd = xopen(argv[1], xsrc);
    int dstfd = xopen(argv[2], xdst);
    int rc = mount(xsrc, xdst, "", MS_BIND, "");
    if (rc < 0) {
        perror("mount()");
        exit(1);
    }
    close(srcfd);
    close(dstfd);
    return 0;
}

/* vim:set ts=4 sts=4 sw=4 et:*/
