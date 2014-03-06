/****************************************************************************
*
*  Title:     bstream.h
*
*  Synopsis:  This module contains routines to perform the following
*             processing:
*
*             1. Prototypes for bit stream I/O
*
*  Created by: C. Alvin
*
****************************************************************************/

#ifndef  _BIT_STREAM_GUARD
#define  _BIT_STREAM_GUARD 1


/*
 * if C++ compiler, indicate bit stream functions are C source
 */

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Bit Stream Structure
 * stream is implemented via an unsigned character array (buffer)
 * access should be via the provided functions for safety for this
 * implementation as well as possible endian issues.
 */

typedef struct {
  unsigned char* stream;       /* beginning stream position */
  unsigned char* end;          /* end of the stream */
  unsigned char* current;      /* moveable stream pointer */
  unsigned char mask;          /* extracts current bits */
  int stream_length;           /* number of bytes */
  unsigned short garbage_bits; /* number of garbage bits: should be < 8 */
  unsigned MAX_SIZE;
} bstream;


/*
 * Bit stream interface functions
 */

/* make a writeable stream readable */
void resetBitStream(bstream*);

/* free dynamically allocated mem */
void freeBitStream(bstream*);

/* erase and reset stream for rewriting */
void clearBitStream(bstream* s);


bstream* openBitStream(unsigned);

/* returns num garbage bits */
unsigned short closeBitStream(bstream*);

/* put a single bit */
void putBit(bstream*, unsigned char bit);

/* put up to 32 bits */
void putBits(bstream*, unsigned val, unsigned short n);


/* input stream */
/* Just look at the specified number of bits in the stream (no removal) */
unsigned peekBits(bstream* in, unsigned short num_bits)

/* get 1 bit */
unsigned char getBit(bstream*);

/* get up to 32 bits */
unsigned getBits(bstream*, unsigned short);

void dumpStream(bstream*);


/*
 * if C++ compiler, indicate bit stream functions are C source
 */
#ifdef __cplusplus
}
#endif


#endif /* _BIT_STREAM_GUARD */
