#ifndef _FLAC_CONFIG_H
#define _FLAC_CONFIG_H

#define FLAC__INTEGER_ONLY_LIBRARY (1)
//#define CPU_IS_BIG_ENDIAN
#define ENABLE_64_BIT_WORDS (0)
#define HAVE_INTTYPES_H (1)
// Max block size in Bytes Implemented
#define FLAC__MAX_BLOCK_SIZE_IMPLD (10000) /* 4096 */
//#define NDEBUG

// If non zero, it keeps a big endian input as such assuming 
// the platform is big endian. 
// Else, it swaps the bytes to Little endian. 
// We need this altered to LE via a swapping, so.
// Here, Compiler is little endian, So.
#define WORDS_BIGENDIAN (0)
// Compiler is little endian, So.
#define CPU_IS_BIG_ENDIAN (0)
#define HAVE_BSWAP32 (0)
#define HAVE_STDINT_H (1)
#define PACKAGE_VERSION "1.0"
#define FLAC__HAS_OGG (0)

#define SUPPORT_DECODE_ONLY_1_FRAME_AT_A_TIME (1)

#endif /* _FLAC_CONFIG_H */