/* version 20131205 
 * update: rate and ratep changed to 32
 */

#ifndef __PHOTON_H_
#define __PHOTON_H_

#include <stdint.h>

#define ROUND			12
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))

#if defined(_PHOTON80_)
//ROL - 1 line added (value of S)
#define S				4
#define D				5
#define RATE			20
#define RATEP			16
#define DIGESTSIZE	80

//ROL - 2 lines added (input/output filenames)
#define in_file "input.txt"
#define out_file "output.txt"


#elif	defined(_PHOTON128_)
#define D				6
#define RATE			16
#define RATEP			16
#define DIGESTSIZE	128	

#elif	defined(_PHOTON160_)
#define D				7
#define RATE			36
#define RATEP			36
#define DIGESTSIZE	160

#elif	defined(_PHOTON192_)
#define D				7
#define RATE			4
#define RATEP			4
#define DIGESTSIZE	192

#elif defined(_PHOTON224_)
#define D				8
#define RATE			32
#define RATEP			32
#define DIGESTSIZE	224	

#elif defined(_PHOTON256_)
#define D				6
#define RATE			32	
#define RATEP			32
#define DIGESTSIZE	256

#elif defined(_AES_) || defined(_PHOTONAES_)
#define D				4
#define RATE			128
#define RATEP			128
#define DIGESTSIZE	128
#endif

typedef uint8_t	byte;
typedef uint32_t	u32;
typedef uint64_t	u64;

#ifdef _PHOTON256_
typedef u64 tword;
typedef uint64_t CWord; // LSB for the first cell of the column 
#else
typedef uint32_t CWord;
typedef u32 tword;
#endif

typedef struct{
	u64 h;
	u64 l;
}u128; // state word
void PrintState(byte state[D][D]);
void printDigest(const byte* digest);
void PermutationOnByte(byte* in, int R);
void Init(byte state[D][D]);
void hash(byte* digest,const byte* mess, int BitLen);
void CompressFunction(byte state[D][D], const byte* mess, int BitOffSet);

#endif /*  end of photon.h */
