#include <stdbool.h>
#include <stdint.h>
#include "aes.h"
void AddRoundKey(u8 state[][4], u32 w[])
{
   u8 subkey[4];
   // memcpy(subkey,&w[idx],4); // Not accurate for big endian machines
   // Subkey 1
   subkey[0] = w[0] >> 24;
   subkey[1] = w[0] >> 16;
   subkey[2] = w[0] >> 8;
   subkey[3] = w[0];
   state[0][0] ^= subkey[0];
   state[1][0] ^= subkey[1];
   state[2][0] ^= subkey[2];
   state[3][0] ^= subkey[3];
   // Subkey 2
   subkey[0] = w[1] >> 24;
   subkey[1] = w[1] >> 16;
   subkey[2] = w[1] >> 8;
   subkey[3] = w[1];
   state[0][1] ^= subkey[0];
   state[1][1] ^= subkey[1];
   state[2][1] ^= subkey[2];
   state[3][1] ^= subkey[3];
   // Subkey 3
   subkey[0] = w[2] >> 24;
   subkey[1] = w[2] >> 16;
   subkey[2] = w[2] >> 8;
   subkey[3] = w[2];
   state[0][2] ^= subkey[0];
   state[1][2] ^= subkey[1];
   state[2][2] ^= subkey[2];
   state[3][2] ^= subkey[3];
   // Subkey 4
   subkey[0] = w[3] >> 24;
   subkey[1] = w[3] >> 16;
   subkey[2] = w[3] >> 8;
   subkey[3] = w[3];
   state[0][3] ^= subkey[0];
   state[1][3] ^= subkey[1];
   state[2][3] ^= subkey[2];
   state[3][3] ^= subkey[3];
}
void InvSubBytes(u8 state[][4])
{
   state[0][0] = aes_invsbox[state[0][0] >> 4][state[0][0] & 0x0F];
   state[0][1] = aes_invsbox[state[0][1] >> 4][state[0][1] & 0x0F];
   state[0][2] = aes_invsbox[state[0][2] >> 4][state[0][2] & 0x0F];
   state[0][3] = aes_invsbox[state[0][3] >> 4][state[0][3] & 0x0F];
   state[1][0] = aes_invsbox[state[1][0] >> 4][state[1][0] & 0x0F];
   state[1][1] = aes_invsbox[state[1][1] >> 4][state[1][1] & 0x0F];
   state[1][2] = aes_invsbox[state[1][2] >> 4][state[1][2] & 0x0F];
   state[1][3] = aes_invsbox[state[1][3] >> 4][state[1][3] & 0x0F];
   state[2][0] = aes_invsbox[state[2][0] >> 4][state[2][0] & 0x0F];
   state[2][1] = aes_invsbox[state[2][1] >> 4][state[2][1] & 0x0F];
   state[2][2] = aes_invsbox[state[2][2] >> 4][state[2][2] & 0x0F];
   state[2][3] = aes_invsbox[state[2][3] >> 4][state[2][3] & 0x0F];
   state[3][0] = aes_invsbox[state[3][0] >> 4][state[3][0] & 0x0F];
   state[3][1] = aes_invsbox[state[3][1] >> 4][state[3][1] & 0x0F];
   state[3][2] = aes_invsbox[state[3][2] >> 4][state[3][2] & 0x0F];
   state[3][3] = aes_invsbox[state[3][3] >> 4][state[3][3] & 0x0F];
}
void InvShiftRows(u8 state[][4])
{
   int t;
   // Shift right by 1
   t = state[1][3];
   state[1][3] = state[1][2];
   state[1][2] = state[1][1];
   state[1][1] = state[1][0];
   state[1][0] = t;
   // Shift right by 2
   t = state[2][3];
   state[2][3] = state[2][1];
   state[2][1] = t;
   t = state[2][2];
   state[2][2] = state[2][0];
   state[2][0] = t;
   // Shift right by 3
   t = state[3][3];
   state[3][3] = state[3][0];
   state[3][0] = state[3][1];
   state[3][1] = state[3][2];
   state[3][2] = t;
}

void InvMixColumns(u8 state[][4])
{
   int idx;
   u8 col[4],t;
   // Column 1
   col[0] = state[0][0];
   col[1] = state[1][0];
   col[2] = state[2][0];
   col[3] = state[3][0];
   state[0][0] = gf_mul[col[0]][5];
   state[0][0] ^= gf_mul[col[1]][3];
   state[0][0] ^= gf_mul[col[2]][4];
   state[0][0] ^= gf_mul[col[3]][2];
   state[1][0] = gf_mul[col[0]][2];
   state[1][0] ^= gf_mul[col[1]][5];
   state[1][0] ^= gf_mul[col[2]][3];
   state[1][0] ^= gf_mul[col[3]][4];
   state[2][0] = gf_mul[col[0]][4];
   state[2][0] ^= gf_mul[col[1]][2];
   state[2][0] ^= gf_mul[col[2]][5];
   state[2][0] ^= gf_mul[col[3]][3];
   state[3][0] = gf_mul[col[0]][3];
   state[3][0] ^= gf_mul[col[1]][4];
   state[3][0] ^= gf_mul[col[2]][2];
   state[3][0] ^= gf_mul[col[3]][5];
   // Column 2
   col[0] = state[0][1];
   col[1] = state[1][1];
   col[2] = state[2][1];
   col[3] = state[3][1];
   state[0][1] = gf_mul[col[0]][5];
   state[0][1] ^= gf_mul[col[1]][3];
   state[0][1] ^= gf_mul[col[2]][4];
   state[0][1] ^= gf_mul[col[3]][2];
   state[1][1] = gf_mul[col[0]][2];
   state[1][1] ^= gf_mul[col[1]][5];
   state[1][1] ^= gf_mul[col[2]][3];
   state[1][1] ^= gf_mul[col[3]][4];
   state[2][1] = gf_mul[col[0]][4];
   state[2][1] ^= gf_mul[col[1]][2];
   state[2][1] ^= gf_mul[col[2]][5];
   state[2][1] ^= gf_mul[col[3]][3];
   state[3][1] = gf_mul[col[0]][3];
   state[3][1] ^= gf_mul[col[1]][4];
   state[3][1] ^= gf_mul[col[2]][2];
   state[3][1] ^= gf_mul[col[3]][5];
   // Column 3
   col[0] = state[0][2];
   col[1] = state[1][2];
   col[2] = state[2][2];
   col[3] = state[3][2];
   state[0][2] = gf_mul[col[0]][5];
   state[0][2] ^= gf_mul[col[1]][3];
   state[0][2] ^= gf_mul[col[2]][4];
   state[0][2] ^= gf_mul[col[3]][2];
   state[1][2] = gf_mul[col[0]][2];
   state[1][2] ^= gf_mul[col[1]][5];
   state[1][2] ^= gf_mul[col[2]][3];
   state[1][2] ^= gf_mul[col[3]][4];
   state[2][2] = gf_mul[col[0]][4];
   state[2][2] ^= gf_mul[col[1]][2];
   state[2][2] ^= gf_mul[col[2]][5];
   state[2][2] ^= gf_mul[col[3]][3];
   state[3][2] = gf_mul[col[0]][3];
   state[3][2] ^= gf_mul[col[1]][4];
   state[3][2] ^= gf_mul[col[2]][2];
   state[3][2] ^= gf_mul[col[3]][5];
   // Column 4
   col[0] = state[0][3];
   col[1] = state[1][3];
   col[2] = state[2][3];
   col[3] = state[3][3];
   state[0][3] = gf_mul[col[0]][5];
   state[0][3] ^= gf_mul[col[1]][3];
   state[0][3] ^= gf_mul[col[2]][4];
   state[0][3] ^= gf_mul[col[3]][2];
   state[1][3] = gf_mul[col[0]][2];
   state[1][3] ^= gf_mul[col[1]][5];
   state[1][3] ^= gf_mul[col[2]][3];
   state[1][3] ^= gf_mul[col[3]][4];
   state[2][3] = gf_mul[col[0]][4];
   state[2][3] ^= gf_mul[col[1]][2];
   state[2][3] ^= gf_mul[col[2]][5];
   state[2][3] ^= gf_mul[col[3]][3];
   state[3][3] = gf_mul[col[0]][3];
   state[3][3] ^= gf_mul[col[1]][4];
   state[3][3] ^= gf_mul[col[2]][2];
   state[3][3] ^= gf_mul[col[3]][5];
}

u32 SubWord(u32 word)
{
   unsigned int result;

   result = (int)aes_sbox[(word >> 4) & 0x0000000F][word & 0x0000000F];
   result += (int)aes_sbox[(word >> 12) & 0x0000000F][(word >> 8) & 0x0000000F] << 8;
   result += (int)aes_sbox[(word >> 20) & 0x0000000F][(word >> 16) & 0x0000000F] << 16;
   result += (int)aes_sbox[(word >> 28) & 0x0000000F][(word >> 24) & 0x0000000F] << 24;
   return(result);
}
void KeyExpansion(u8 key[], u32 w[], int keysize)
{
   int Nb=4,Nr,Nk,idx;
   u32 temp,Rcon[]={0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,
                     0x40000000,0x80000000,0x1b000000,0x36000000,0x6c000000,0xd8000000,
                     0xab000000,0x4d000000,0x9a000000};
   switch (keysize) {
      case 128: Nr = 10; Nk = 4; break;
      case 192: Nr = 12; Nk = 6; break;
      case 256: Nr = 14; Nk = 8; break;
      default: return;
   }

   for (idx=0; idx < Nk; ++idx) {
      w[idx] = ((key[4 * idx]) << 24) | ((key[4 * idx + 1]) << 16) |
               ((key[4 * idx + 2]) << 8) | ((key[4 * idx + 3]));
   }

   for (idx = Nk; idx < Nb * (Nr+1); ++idx) {
      temp = w[idx - 1];
      if ((idx % Nk) == 0)
         temp = SubWord(KE_ROTWORD(temp)) ^ Rcon[(idx-1)/Nk];
      else if (Nk > 6 && (idx % Nk) == 4)
         temp = SubWord(temp);
      w[idx] = w[idx-Nk] ^ temp;
   }
}

void aes_decrypt(u8 in[], u8 out[], u32 key[], int keysize)
{
   u8 state[4][4];
   // Copy the input to the state.
   state[0][0] = in[0];
   state[1][0] = in[1];
   state[2][0] = in[2];
   state[3][0] = in[3];
   state[0][1] = in[4];
   state[1][1] = in[5];
   state[2][1] = in[6];
   state[3][1] = in[7];
   state[0][2] = in[8];
   state[1][2] = in[9];
   state[2][2] = in[10];
   state[3][2] = in[11];
   state[0][3] = in[12];
   state[1][3] = in[13];
   state[2][3] = in[14];
   state[3][3] = in[15];

   // Perform the necessary number of rounds. The round key is added first.
   // The last round does not perform the MixColumns step.
   if (keysize > 128) {
      if (keysize > 192) {
         AddRoundKey(state,&key[56]);
         InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[52]);InvMixColumns(state);
         InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[48]);InvMixColumns(state);
      }
      else {
         AddRoundKey(state,&key[48]);
      }
      InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[44]);InvMixColumns(state);
      InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[40]);InvMixColumns(state);
   }
   else {
      AddRoundKey(state,&key[40]);
   }
   InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[36]);InvMixColumns(state);
   InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[32]);InvMixColumns(state);
   InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[28]);InvMixColumns(state);
   InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[24]);InvMixColumns(state);
   InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[20]);InvMixColumns(state);
   InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[16]);InvMixColumns(state);
   InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[12]);InvMixColumns(state);
   InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[8]);InvMixColumns(state);
   InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[4]);InvMixColumns(state);
   InvShiftRows(state);InvSubBytes(state);AddRoundKey(state,&key[0]);

   // Copy the state to the output array
   out[0] = state[0][0];
   out[1] = state[1][0];
   out[2] = state[2][0];
   out[3] = state[3][0];
   out[4] = state[0][1];
   out[5] = state[1][1];
   out[6] = state[2][1];
   out[7] = state[3][1];
   out[8] = state[0][2];
   out[9] = state[1][2];
   out[10] = state[2][2];
   out[11] = state[3][2];
   out[12] = state[0][3];
   out[13] = state[1][3];
   out[14] = state[2][3];
   out[15] = state[3][3];
}
void aes_encrypt(u8 in[], u8 out[], u32 key[], int keysize)
{
   u8 state[4][4];
   // Copy input array (should be 16 bytes long) to a matrix (sequential bytes are ordered
   // by row, not col) called "state" for processing.
   // *** Implementation note: The official AES documentation references the state by
   // column, then row. Accessing an element in C requires row then column. Thus, all state
   // references in AES must have the column and row indexes reversed for C implementation.
   state[0][0] = in[0];
   state[1][0] = in[1];
   state[2][0] = in[2];
   state[3][0] = in[3];
   state[0][1] = in[4];
   state[1][1] = in[5];
   state[2][1] = in[6];
   state[3][1] = in[7];
   state[0][2] = in[8];
   state[1][2] = in[9];
   state[2][2] = in[10];
   state[3][2] = in[11];
   state[0][3] = in[12];
   state[1][3] = in[13];
   state[2][3] = in[14];
   state[3][3] = in[15];

   // Perform the necessary number of rounds. The round key is added first.
   // The last round does not perform the MixColumns step.
   AddRoundKey(state,&key[0]);
   SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[4]);
   SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[8]);
   SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[12]);
   SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[16]);
   SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[20]);
   SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[24]);
   SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[28]);
   SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[32]);
   SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[36]);
   if (keysize != 128) {
      SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[40]);
      SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[44]);
      if (keysize != 192) {
         SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[48]);
         SubBytes(state); ShiftRows(state); MixColumns(state); AddRoundKey(state,&key[52]);
         SubBytes(state); ShiftRows(state); AddRoundKey(state,&key[56]);
      }
      else {
         SubBytes(state); ShiftRows(state); AddRoundKey(state,&key[48]);
      }
   }
   else {
      SubBytes(state); ShiftRows(state); AddRoundKey(state,&key[40]);
   }

   // Copy the state to the output array
   out[0] = state[0][0];
   out[1] = state[1][0];
   out[2] = state[2][0];
   out[3] = state[3][0];
   out[4] = state[0][1];
   out[5] = state[1][1];
   out[6] = state[2][1];
   out[7] = state[3][1];
   out[8] = state[0][2];
   out[9] = state[1][2];
   out[10] = state[2][2];
   out[11] = state[3][2];
   out[12] = state[0][3];
   out[13] = state[1][3];
   out[14] = state[2][3];
   out[15] = state[3][3];
}

