/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */
#include "tomcrypt.h"

/**
   @file zeromem.c
   Zero a block of memory, Tom St Denis
*/

/**
   Zero a block of memory
   @param out    The destination of the area to zero
   @param outlen The length of the area to zero (octets)
*/
void zeromem(volatile void *out, size_t outlen)
{
   volatile char *mem = out;
   LTC_ARGCHKVD(out != NULL);
   while (outlen-- > 0) {
      *mem++ = '\0';
   }
}

/* ref:         HEAD -> develop */
/* git commit:  e1fcd3ab04868f60685e97f09ee329ce7e3bed1c */
/* commit time: 2017-07-05 14:26:53 +0200 */
