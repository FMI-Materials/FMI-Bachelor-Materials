/* Thanks to Chien-Ning Chen for correcting a bug in previous version
 *
 * This is the simple implementation with table lookup
 * The fastest implementation is yet to be posted.  
 * 
 * Last Modified:04 December 2013
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "photon.h"

#if	defined(_PHOTON256_) || defined(_AES_) || defined(_PHOTONAES_)
#define S				8
const byte ReductionPoly = 0x1b;
#else
#define S				4
const byte ReductionPoly = 0x3;
#endif
const byte WORDFILTER = ((byte) 1<<S)-1;

int DEBUG = 0;

/* to be completed for one time pass mode */
unsigned long long MessBitLen = 0;

const byte RC[D][12] = {
#if defined(_PHOTON80_)
	{1, 3, 7, 14, 13, 11, 6, 12,  9, 2, 5, 10},
	{0, 2, 6, 15, 12, 10, 7, 13,  8, 3, 4, 11},
	{2, 0, 4, 13, 14,  8, 5, 15, 10, 1, 6,  9},
	{7, 5, 1,  8, 11, 13, 0, 10, 15, 4, 3, 12},
	{5, 7, 3, 10,  9, 15, 2,  8, 13, 6, 1, 14}

#elif defined(_PHOTON128_) || defined(_PHOTON256_)
	{1, 3, 7, 14, 13, 11, 6, 12, 9, 2, 5, 10},
		{0, 2, 6, 15, 12, 10, 7, 13, 8, 3, 4, 11},
		{2, 0, 4, 13, 14, 8, 5, 15, 10, 1, 6, 9},
		{6, 4, 0, 9, 10, 12, 1, 11, 14, 5, 2, 13},
		{7, 5, 1, 8, 11, 13, 0, 10, 15, 4, 3, 12},
		{5, 7, 3, 10, 9, 15, 2, 8, 13, 6, 1, 14}

#elif defined(_PHOTON160_) || defined(_PHOTON192_)
	{1, 3, 7, 14, 13, 11, 6, 12, 9, 2, 5, 10},
		{0, 2, 6, 15, 12, 10, 7, 13, 8, 3, 4, 11},
		{3, 1, 5, 12, 15, 9, 4, 14, 11, 0, 7, 8},
		{4, 6, 2, 11, 8, 14, 3, 9, 12, 7, 0, 15},
		{2, 0, 4, 13, 14, 8, 5, 15, 10, 1, 6, 9},
		{7, 5, 1, 8, 11, 13, 0, 10, 15, 4, 3, 12},
		{5, 7, 3, 10, 9, 15, 2, 8, 13, 6, 1, 14}

#elif defined(_PHOTON224_)
	{1, 3, 7, 14, 13, 11, 6, 12, 9, 2, 5, 10},
		{0, 2, 6, 15, 12, 10, 7, 13, 8, 3, 4, 11},
		{2, 0, 4, 13, 14, 8, 5, 15, 10, 1, 6, 9},
		{6, 4, 0, 9, 10, 12, 1, 11, 14, 5, 2, 13},
		{14, 12, 8, 1, 2, 4, 9, 3, 6, 13, 10, 5},
		{15, 13, 9, 0, 3, 5, 8, 2, 7, 12, 11, 4},
		{13, 15, 11, 2, 1, 7, 10, 0, 5, 14, 9, 6},
		{9, 11, 15, 6, 5, 3, 14, 4, 1, 10, 13, 2}
#elif defined(_AES_) || defined(_PHOTONAES_)
	{1, 3, 7, 14, 13, 11, 6, 12,  9, 2, 5, 10},
		{0, 2, 6, 15, 12, 10, 7, 13,  8, 3, 4, 11},
		{2, 0, 4, 13, 14,  8, 5, 15, 10, 1, 6,  9},
		{7, 5, 1,  8, 11, 13, 0, 10, 15, 4, 3, 12}
#endif
};

const byte MixColMatrix[D][D] = {
#if defined(_PHOTON80_)
	{ 1,  2,  9,  9,  2},
	{ 2,  5,  3,  8, 13},
	{13, 11, 10, 12,  1},
	{ 1, 15,  2,  3, 14},
	{14, 14,  8,  5, 12}

#elif defined(_PHOTON128_)
	{ 1,  2,  8,  5,  8,  2},
		{ 2,  5,  1,  2,  6, 12},
		{12,  9, 15,  8,  8, 13},
		{13,  5, 11,  3, 10,  1},
		{ 1, 15, 13, 14, 11,  8},
		{ 8,  2,  3,  3,  2,  8}
#elif defined(_PHOTON160_) || defined(_PHOTON192_)
	{ 1,  4,  6,  1,  1,  6,  4},
		{ 4,  2, 15,  2,  5, 10,  5},
		{ 5,  3, 15, 10,  7,  8, 13},
		{13,  4, 11,  2,  7, 15,  9},
		{ 9, 15,  7,  2, 11,  4, 13},
		{13,  8,  7, 10, 15,  3,  5},
		{ 5, 10,  5, 2 , 15,  2,  4}
#elif defined(_PHOTON224_)
	{ 2,  4,  2, 11,  2,  8,  5,  6},
		{12,  9,  8, 13,  7,  7,  5,  2},
		{ 4,  4, 13, 13,  9,  4, 13,  9},
		{ 1,  6,  5,  1, 12, 13, 15, 14},
		{15, 12,  9, 13, 14,  5, 14, 13},
		{ 9, 14,  5, 15,  4, 12,  9,  6},
		{12,  2,  2, 10,  3,  1,  1, 14},
		{15,  1, 13, 10,  5, 10,  2,  3}
#elif defined(_PHOTON256_)
	{  2,   3,   1,   2,   1,   4},
		{  8,  14,   7,   9,   6,  17},
		{ 34,  59,  31,  37,  24,  66},
		{132, 228, 121, 155, 103,  11},
		{ 22, 153, 239, 111, 144,  75},
		{150, 203, 210, 121,  36, 167}
#elif defined(_AES_)
	{2,3,1,1},
		{1,2,3,1},
		{1,1,2,3},
		{3,1,1,2}
#elif defined(_PHOTONAES_)
	{ 1,  2,    1,  4},
		{ 4,  9,    6, 17},
		{17, 38,   24, 66},
		{66, 149, 100, 11}
#endif
};

#if defined(_PHOTON256_) || defined(_AES_) || defined(_PHOTONAES_)
byte sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
#else
byte sbox[16] = {12, 5, 6, 11, 9, 0, 10, 13, 3, 14, 15, 8, 4, 7, 1, 2};
#endif

byte FieldMult(byte a, byte b)
{
	byte x = a, ret = 0;
	int i;
	for(i = 0; i < S; i++) {
		if((b>>i)&1) ret ^= x;
		if((x>>(S-1))&1) {
			x <<= 1;
			x ^= ReductionPoly;
		}
		else x <<= 1;
	}
	return ret&WORDFILTER;
}


void PrintState(byte state[D][D])
{
	if(!DEBUG) return;
	int i, j;
	for(i = 0; i < D; i++){
		for(j = 0; j < D; j++)
			printf("%2X ", state[i][j]);
		printf("\n");
	}
	printf("\n");
}

void PrintState_Column(CWord state[D])
{
	if(!DEBUG) return;
	int i, j;
	for(i = 0; i < D; i++){
		for(j = 0; j < D; j++)
			printf("%2X ", (state[j]>>(i*S)) & WORDFILTER);
		printf("\n");
	}
	printf("\n");
}

void printDigest(const byte* digest)
{
	int i;
	for(i = 0; i < DIGESTSIZE/8; i++)
		printf("%.2x", digest[i]);
	printf("\n");
}


void AddKey(byte state[D][D], int round)
{
	int i;
	for(i = 0; i < D; i++)
		state[i][0] ^= RC[i][round];
}

void SubCell(byte state[D][D])
{
	int i,j;
	for(i = 0; i < D; i++)
		for(j = 0; j <  D; j++)
			state[i][j] = sbox[state[i][j]];
}

void ShiftRow(byte state[D][D])
{
	int i, j;
	byte tmp[D];
	for(i = 1; i < D; i++) {
		for(j = 0; j < D; j++)
			tmp[j] = state[i][j];
		for(j = 0; j < D; j++)
			state[i][j] = tmp[(j+i)%D];
	}
}

void MixColumn(byte state[D][D])
{
	int i, j, k;
	byte tmp[D];
	for(j = 0; j < D; j++){
		for(i = 0; i < D; i++) {
			byte sum = 0;
			for(k = 0; k < D; k++)
				sum ^= FieldMult(MixColMatrix[i][k], state[k][j]);
			tmp[i] = sum;
		}
		for(i = 0; i < D; i++)
			state[i][j] = tmp[i];
	}
}

#ifdef _TABLE_
tword Table[D][1<<S];
void BuildTableSCShRMCS()
{
	int c, v, r;
	tword tv;
	for(v = 0; v < (1<<S); v++) {
		for(c = 0; c < D; c++){ // compute the entry Table[c][v]
			tv = 0;
			for(r = 0; r < D; r++){
				tv <<= S;
				tv |= (tword) FieldMult(MixColMatrix[r][c], sbox[v]);
			}
			Table[c][v] = tv;
		}
	}
	if(DEBUG){
		printf("tword Table[D][1<<S] = {\n");
		for(v = 0; v < (1<<S); v++) {
			printf("\t{");
			for(c = 0; c < D; c++){ 
#ifndef _PHOTON256_
				printf("0x%.8XU, ", Table[c][v]);
#else
				printf("0x%.16llXULL, ", Table[c][v]);
#endif
			}
			printf("\b\b}");
			if(v != (1<<S)-1) printf(",");
			printf("\n");
		}
		printf("};\n");
	}
}

void SCShRMCS(byte state[D][D])
{
	int c,r;
	tword v;
	byte os[D][D];
	memcpy(os, state, D*D);

	for(c = 0; c < D; c++){ // for all columns
		v = 0;
		for(r = 0; r < D; r++) // for all rows in this column i after ShiftRow
			v ^= Table[r][os[r][(r+c)%D]];

		for(r = 1; r <= D; r++){
			state[D-r][c] = (byte)v & WORDFILTER;
			v >>= S;
		}
	}
}
#endif

void Permutation(byte state[D][D], int R)
{
	int i;
	for(i = 0; i < R; i++) {
		if(DEBUG) printf("--- Round %d ---\n", i);
		AddKey(state, i); PrintState(state);
#ifndef _TABLE_
		SubCell(state); PrintState(state);
		ShiftRow(state); PrintState(state);
		MixColumn(state); 
#else
		SCShRMCS(state);
#endif
		PrintState(state);
	}
}

/* get NoOfBits bits values from str starting from BitOffSet-th bit 
 * Requirement: NoOfBits <= 8 */
byte GetByte(const byte*str, int BitOffSet, int NoOfBits)
{
#if S==8
	if(BitOffSet&0x7) return ((str[BitOffSet>>3]<<4) | (str[(BitOffSet>>3)+1]>>4));
	else return str[BitOffSet>>3];
#else
#if 0
	int ByteIndex = BitOffSet >> 3;
	int BitIndex = BitOffSet & 0x7;
	byte localFilter = (((byte)1)<<NoOfBits) - 1;
	if(BitIndex+ NoOfBits <= 8) {
		return (str[ByteIndex] >>(8-BitIndex-NoOfBits)) & localFilter;
	}
	else {
		u32 tmp = ((((u32) str[ByteIndex])<<8)&0xFF00) | (((u32) str[ByteIndex+1])&0xFF);
		return ((byte)(tmp>>(16-BitIndex-NoOfBits))) & localFilter;
	}
#endif
	return (str[BitOffSet>>3] >> (4-(BitOffSet&0x4))) & WORDFILTER;
#endif
}

void WordXorByte(byte state[D][D], const byte*str, int BitOffSet, int WordOffSet, int NoOfBits)
{
	int i = 0;
	while(i < NoOfBits)
	{
		state[(WordOffSet+(i/S))/D][(WordOffSet+(i/S))%D] ^= GetByte(str, BitOffSet+i, min(S, NoOfBits-i))<<(S-min(S,NoOfBits-i));
		i += S;
	}
}

/* ensure NoOfBits <=8 */
void WriteByte(byte*str, byte value, int BitOffSet, int NoOfBits)
{
	int ByteIndex = BitOffSet >> 3;
	int BitIndex = BitOffSet & 0x7;
	byte localFilter = (((byte)1)<<NoOfBits) - 1;
	value &= localFilter;
	if(BitIndex+ NoOfBits <= 8) {
		str[ByteIndex] &= ~(localFilter<<(8-BitIndex-NoOfBits));
		str[ByteIndex] |= value<<(8-BitIndex-NoOfBits);
	}
	else {
		u32 tmp = ((((u32) str[ByteIndex])<<8)&0xFF00) | (((u32) str[ByteIndex+1])&0xFF);
		tmp &= ~((((u32)localFilter)&0xFF)<<(16-BitIndex-NoOfBits));
		tmp |= (((u32)(value))&0xFF)<<(16-BitIndex-NoOfBits);
		str[ByteIndex] = (tmp>>8)&0xFF;
		str[ByteIndex+1] = tmp&0xFF;
	}
}

void WordToByte(byte state[D][D], byte*str, int BitOffSet, int NoOfBits)
{
	int i = 0;
	while(i < NoOfBits)
	{
		WriteByte(str, (state[i/(S*D)][(i/S)%D] & WORDFILTER)>>(S-min(S, NoOfBits-i)), BitOffSet+i, min(S, NoOfBits-i));
		i += S;
	}
}

void PermutationOnByte(byte* in, int R)
{
	byte state[D][D];
	int i;
	for(i = 0; i < D*D; i++)
		state[i/D][i%D] = GetByte(in, i*S, S);
	Permutation(state, R);
	WordToByte(state, in, 0, D*D*S);
}


void Init(byte state[D][D])
{

	int i,j;
	MessBitLen = 0;

	for(i = 0; i < D; i++)
		for(j = 0; j < D; j++)
			state[i][j] = 0;
	byte presets[3];
	presets[0] = (DIGESTSIZE>>2) & 0xFF;
	presets[1] = RATE & 0xFF;
	presets[2] = RATEP  & 0xFF;
	WordXorByte(state, presets, 0, D*D-24/S, 24);
}

void CompressFunction(byte state[D][D], const byte* mess, int BitOffSet)
{
	WordXorByte(state, mess, BitOffSet, 0, RATE);
	Permutation(state, ROUND);
}

/* assume DIGESTSIZE is multiple of RATEP, RATEP is multiple of S */
void Squeeze(byte state[D][D], byte*digest)
{
	int i = 0;
	while(1){
		WordToByte(state, digest, i, min(RATEP, DIGESTSIZE-i));
		i += RATEP;
		if(i >= DIGESTSIZE) break;
		Permutation(state, ROUND);
	}
}

void hash(byte* digest,const byte* mess, int BitLen)
{
	byte state[D][D], padded[(int)ceil(RATE/8.0) + 1];
	Init(state);
	int MessIndex = 0;
	while(MessIndex <= (BitLen-RATE)) {
		CompressFunction(state, mess, MessIndex);
		MessIndex += RATE;
	}
	int i,j;
	for(i = 0; i < (ceil(RATE/8.0)+1); i++) padded[i] = 0;
	j = ceil((BitLen - MessIndex)/8.0);
	for(i = 0; i < j; i++)
		padded[i]=mess[(MessIndex/8)+i];
	padded[i] = 0x80;
	CompressFunction(state, padded, MessIndex&0x7);
	Squeeze(state, digest);
}

