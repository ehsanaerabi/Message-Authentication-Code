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
  @file crypt_argchk.c
  Perform argument checking, Tom St Denis
*/

#if (ARGTYPE == 0)
void crypt_argchk(char *v, char *s, int d)
{
 fprintf(stderr, "LTC_ARGCHK '%s' failure on line %d of file %s\n",
         v, d, s);
 abort();
}
#endif

/* ref:         HEAD -> develop */
/* git commit:  e1fcd3ab04868f60685e97f09ee329ce7e3bed1c */
/* commit time: 2017-07-05 14:26:53 +0200 */
