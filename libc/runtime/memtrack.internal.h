#ifndef COSMOPOLITAN_LIBC_RUNTIME_MEMTRACK_H_
#define COSMOPOLITAN_LIBC_RUNTIME_MEMTRACK_H_
COSMOPOLITAN_C_START_

#ifndef __SANITIZE_ADDRESS__
#define kFixedmapStart      0x300000000
#define kFixedmapSize       (0x400000000 - kFixedmapStart)
#define kMemtrackFdsStart   0x6fe000000
#define kMemtrackFdsSize    (0x6ff000000 - kMemtrackFdsStart)
#define kMemtrackZiposStart 0x6fd000000
#define kMemtrackZiposSize  (0xafe000000 - kMemtrackZiposStart)
#else
#define kFixedmapStart      0x300000040000
#define kFixedmapSize       (0x400000040000 - kFixedmapStart)
#define kMemtrackFdsStart   0x6fe000040000
#define kMemtrackFdsSize    (0x6feffffc0000 - kMemtrackFdsStart)
#define kMemtrackZiposStart 0x6fd000040000
#define kMemtrackZiposSize  (0x6fdffffc0000 - kMemtrackZiposStart)
#endif

COSMOPOLITAN_C_END_
#endif /* COSMOPOLITAN_LIBC_RUNTIME_MEMTRACK_H_ */
