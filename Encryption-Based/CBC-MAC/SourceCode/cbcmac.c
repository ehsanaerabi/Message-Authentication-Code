/*
CBC-MAC

Author: Ehsan Aerabi
Date: 8/21/2017

This code is a basic CBCMAC algorithm used for message authentication. 

The padding is done simply by adding enough zeros '0' started by a '1', in order to make
 the message multiple of block size. 
 
This code was written to be efficiently compiled on 32-bit compilers with minimum
 featuers because we wanted to use it in our benchmarking research. 
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define AES_BLOCK_CIPHER
#ifdef AES_BLOCK_CIPHER 
#include "aes.h"
#endif

#define DEBUG_MODE

//This CBC code was written to work with 128-bit block size. Do not change it!
#define blocksize 128 

//#define CPUDataPathWidth 32

#ifdef AES_BLOCK_CIPHER 
void blockcipher(u8 in[], u8 out[], u32 key[], int keysize)
{
	aes_encrypt(in, out, key, keysize);
}
#endif
void cbc_mac(u32 msg[], int msgSize, u32 iv[], u32 out[], u32 key[], int keySize)
{
	int padSize;
	//u32 MAC[4];
	u32  lastBlock[4];
	u8 padIndex;
	u8 partiallyPaddedRegisterNumber ;
	u32  padMask[4] = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF};
// if padding is required

	for (int j=0 ;j<4; j++)
	{
		out[j] = iv[j];	
	}
	
	int blockIndex;	
 	//CBC-MAC until the last block


	if(msgSize % blocksize){	//Padding required
		padSize = blocksize - (msgSize % blocksize);
		padIndex = padSize % 32;
		partiallyPaddedRegisterNumber = padSize / 32;
		if(partiallyPaddedRegisterNumber>0){
			padMask[0] = 0;
		}
		else if(partiallyPaddedRegisterNumber>1){
			padMask[1] = 0;
		}
		else if(partiallyPaddedRegisterNumber>2){
			padMask[2] = 0;
		}
		else if(partiallyPaddedRegisterNumber>3){
			padMask[3] = 0;
		}
	
			padMask[partiallyPaddedRegisterNumber] = padMask[partiallyPaddedRegisterNumber] << padIndex;

		#ifdef DEBUG_MODE
		printf("\r\n Padding:");
		for(int i=3; i >= 0; i--)
			printf("%x",padMask[i]);	
		printf("\r\n");
		#endif
		for(int i=3; i>=partiallyPaddedRegisterNumber; i-- )
		{
			lastBlock[i] = msg[(msgSize/blocksize)+i];
		}
		for(int i=0; i<4; i++ )
		{
			lastBlock[i] &= padMask[i];
		}	
		padMask[partiallyPaddedRegisterNumber] = 1;
		padMask[partiallyPaddedRegisterNumber]  = padMask[partiallyPaddedRegisterNumber] << (padIndex-1);
		lastBlock[partiallyPaddedRegisterNumber] |= padMask[partiallyPaddedRegisterNumber];
	
	}
	else{//No Padding
		for(int i=0; i<4; i++ )
		{
			
			lastBlock[i] = msg[((msgSize/blocksize)-1)*4+i];
		}	
	}


	for ( blockIndex=0; blockIndex<((msgSize/blocksize)-1)*4; blockIndex=blockIndex+4)
	{
		for (int j=0 ;j<4; j++)
		{
			out[j] = out[j]^msg[blockIndex+j];
		}		
		blockcipher(out,out,key,keySize);

		#ifdef DEBUG_MODE
		printf("MSG block#%d: ",blockIndex/4);
		for(int k=3; k >= 0; k--)
			printf("%x",msg[blockIndex+k]);	
		printf("\tDigest #%d: ",blockIndex/4);
		for(int k=3; k>= 0; k--)
			printf("%x",out[k]);	
		printf("\r\n");
		#endif	
	}
	//Final Block
	for (int j=0 ;j<4; j++)
	{
		out[j] = out[j]^lastBlock[j];
	}
	blockcipher(out,out,key,keySize);

	#ifdef DEBUG_MODE
	printf("Final block#%d: ",blockIndex/4);
	for(int k=3; k >= 0; k--)
		printf("%x",lastBlock[k]);	
	printf("\tDigest #%d: ",blockIndex/4);
	for(int k=3; k>= 0; k--)
		printf("%x",out[k]);	
	printf("\r\n");
	#endif	
}
void Xor128bit(u32 input1[], u32 input2[], u32 output[])
{
//	u32 output[4];
	output[0]= input1[0] ^ input2[0];
	output[1]= input1[1] ^ input2[1];
	output[2]= input1[2] ^ input2[2];
	output[3]= input1[3] ^ input2[3];
}
#define msgSize 62
int main()
{
	u8 msg[msgSize];
	for(int i=0; i<msgSize; i++)
		msg[i]=i;
	u8 output [blocksize/8];
	u8 IV[]={0x01,0x02,0x03,0x04,
					0x05,0x06,0x07,0x08,
					0x09,0x0a,0x0b,0x0c,
					0x0d,0x0e,0x0f,0x10};
	u32 key[4]=	{0xffffffff,0x11111111,0x22222222,0x33333333};
	
					
	cbc_mac(msg,msgSize*8,IV,output,key,128);
	#ifdef DEBUG_MODE
	printf("\r\nCBC-MAC:  ");
	for(int i=(blocksize/8)-1; i>=0; i-- )
	{
		printf("%x",output[i]);
	}
	printf("\r\n");
	#endif
	//printf("%x",output);
	return 0;
	
}
