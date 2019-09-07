#include "tomcrypt.h"
//#define LTC_PMAC
#define LTC_CLEAN_STACK
#define msgSize 62
typedef unsigned char 		u8;
typedef unsigned short 		u16;
typedef unsigned int 		u32;
int main(void)
{
int idx, err;
omac_state omac;
unsigned char dst[MAXBLOCKSIZE];
unsigned long dstlen=16;

unsigned char msg[msgSize];
	for(int i=0; i<msgSize; i++)
		msg[i]=i;
	//u8 output [MAXBLOCKSIZE];

	u32 key[4]=	{0xffffffff,0x11111111,0x22222222,0x33333333};

/* register Rijndael */
if (register_cipher(&rijndael_desc) == -1) {
printf("Error registering Rijndael\n");
return -1;
}
/* get index of Rijndael in cipher descriptor table */
idx = find_cipher("rijndael");
/* we would make up our symmetric key in "key[]" here */
dstlen = sizeof(dst);
// start the OMAC 

if ((err = xcbc_memory(idx,key,16,msg,msgSize,dst,&dstlen)) != CRYPT_OK) {
	printf("Error setting up XCBC-mac: %s\n", error_to_string(err));
	return -1;
}	
/*
if ((err = omac_init(&omac, idx, key, 16)) != CRYPT_OK) {
	printf("Error setting up omac: %s\n", error_to_string(err));
	return -1;
}
// process a few octets 
if((err = omac_process(&omac, msg, msgSize) != CRYPT_OK)) {
	printf("Error processing omac: %s\n", error_to_string(err));
	return -1;
}
// get result (presumably to use it somehow...)
dstlen = sizeof(dst);
if ((err = omac_done(&omac, dst, &dstlen)) != CRYPT_OK) {
	printf("Error finishing omac: %s\n", error_to_string(err));
	return -1;
}*/
	printf("The xcbc-mac is %lu bytes long:\n", dstlen);
	for(int i=0; i < dstlen; i++)
		printf(" %x",dst[i]);
/* return */
return 0;
}
