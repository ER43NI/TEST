/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/calls/calls.h"
#include "libc/intrin/bits.h"
#include "libc/stdio/rand.h"
#include "libc/stdio/temp.h"
#include "libc/str/str.h"
#include "libc/sysv/consts/o.h"
#include "libc/sysv/errfuns.h"

/**
 * Creates temporary file name and descriptor, e.g.
 *
 *     char path[PATH_MAX+1];
 *     strlcat(path, kTmpDir, sizeof(path));
 *     strlcat(path, "sauce.XXXXXX", sizeof(path));
 *     close(mkstemp(path));
 *     puts(path);
 *
 * @param template is mutated to replace last six X's with rng
 * @return open file descriptor r + w exclusive or -1 w/ errno
 * @raise EINVAL if `template` didn't end with `XXXXXX`
 */
int mkstemp(char *template) {
  int i, n;
  uint64_t w;
  if ((n = strlen(template)) < 6 ||
      READ16LE(template + n - 2) != READ16LE("XX") ||
      READ32LE(template + n - 6) != READ32LE("XXXX")) {
    return einval();
  }
  w = _rand64();
  for (i = 0; i < 6; ++i) {
    template[n - 6 + i] = "0123456789abcdefghijklmnopqrstuvwxyz"[w % 36];
    w /= 36;
  }
  return open(template, O_RDWR | O_CREAT | O_EXCL, 0600);
}