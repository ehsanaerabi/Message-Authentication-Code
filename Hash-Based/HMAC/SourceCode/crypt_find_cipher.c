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
  @file crypt_find_cipher.c
  Find a cipher in the descriptor tables, Tom St Denis
*/

/**
   Find a registered cipher by name
   @param name   The name of the cipher to look for
   @return >= 0 if found, -1 if not present
*/
int find_cipher(const char *name)
{
   int x;
   LTC_ARGCHK(name != NULL);
   LTC_MUTEX_LOCK(&ltc_cipher_mutex);
   for (x = 0; x < TAB_SIZE; x++) {
       if (cipher_descriptor[x].name != NULL && !XSTRCMP(cipher_descriptor[x].name, name)) {
          LTC_MUTEX_UNLOCK(&ltc_cipher_mutex);
          return x;
       }
   }
   LTC_MUTEX_UNLOCK(&ltc_cipher_mutex);
   return -1;
}


/* ref:         HEAD -> develop */
/* git commit:  e1fcd3ab04868f60685e97f09ee329ce7e3bed1c */
/* commit time: 2017-07-05 14:26:53 +0200 */
