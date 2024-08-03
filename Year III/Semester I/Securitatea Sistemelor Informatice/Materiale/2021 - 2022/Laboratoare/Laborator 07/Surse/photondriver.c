/*
 * =====================================================================================
 *
 *       Filename:  photondriver.c
 *
 *    Description:  driver for the photon hash family
 *
 *        Version:  1.0
 *        Created:  Friday 14,January,2011 09:50:30  SGT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jian Guo
 *          Email:  ntu.guo@gmail.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "photon.h"

extern int DEBUG;
void TestVector2()
{
	DEBUG = 1;
	byte mess[RATE/8+1]; memset(mess, 0, RATE/8+1);
#ifdef _SSBOX_
	CWord state[D];
	Init_Column(state);
	PrintState_Column(state);
	CompressFunction_Column(state, mess, 0);
#else
	byte state[D][D];
	Init(state);
	PrintState(state);
	CompressFunction(state, mess, 0);
#endif
	DEBUG = 0;
}
	

void TestVectorFile()
{
	// Added by ROL, 31 March 2019
	//Read from in_file (one input on each line) and write the inputs and hashes to out_file
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
   	DEBUG = 0;
   	byte digest[DIGESTSIZE/8];
	
	printf("S = %d, D = %d, Rate = %d, Ratep = %d, DigestSize = %d\n", S, D, RATE, RATEP, DIGESTSIZE);
	
	// open file to read
	printf("openfile");
       fp = fopen(in_file, "r");
       if (fp == NULL){
		   printf ("Error at open input file\n");
           exit(1);
	   }
	   
	   //open file to write
	   FILE *f = fopen(out_file, "w");
	   if (f == NULL)
	   {
	       printf("Error opening output file!\n");
	       exit(1);
	   }
	   
	   //compute hash and write to file
	   fprintf(f, "S = %d, D = %d, Rate = %d, Ratep = %d, DigestSize = %d\n", S, D, RATE, RATEP, DIGESTSIZE);
	   
	   while ((read = getline(&line, &len, fp)) != -1) {
	   		hash(digest, (byte*) line, 8*strlen(line));
			// cut newline
			if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;
			fprintf(f, "%s ::::: ", line);
			int i;
			for(i = 0; i < DIGESTSIZE/8; i++)
				fprintf(f, "%.2x", digest[i]);
			fprintf(f, "\n");	
       }

       fclose(fp);
	   fclose(f);
       if (line)
           free(line);
	
 	
}

#ifdef _TABLE_
#define SAMPLE (1<<20)
#else
#define SAMPLE (1<<20)
#endif
void TestSpeed()
{
	byte mess[SAMPLE];
	int i;
	for(i = 0; i < (SAMPLE); i++)
		mess[i] = SHA256RandomByte();
	byte digest[DIGESTSIZE/8];
	tstart();
#ifdef _SSBOX_
	hash_Column(digest, mess, 8*SAMPLE);
#else
	hash(digest, mess, 8*SAMPLE);
#endif
	double tt = (double) tdiff();
	double speed = tt / SAMPLE;
	printf("%.0f cycles per byte\n", speed);
}

int main(int argc, char*argv[])
{
#ifdef _TABLE_
	BuildTableSCShRMCS();
#endif
#ifdef _SSBOX_
	Build_RC_Column();
	BuildTableSCShRMCS_Column();
#endif
	if((argv[1][0] == '-') && (argv[1][1] == 't'))
		TestVector2();
	//DEBUG = 1; BuildTableSCShRMCS(); DEBUG = 0;
	if((argv[1][0] == '-') && (argv[1][1] == 's'))
		TestSpeed();
	
	//ROL - hash all values from in_file  and print results in out_file; use; ./photon80 -f
	if((argv[1][0] == '-') && (argv[1][1] == 'f'))
		TestVectorFile();
	
	return 0;
}
