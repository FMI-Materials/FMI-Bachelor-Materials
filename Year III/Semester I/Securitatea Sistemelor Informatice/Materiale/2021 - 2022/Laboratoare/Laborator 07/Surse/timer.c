#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


typedef uint64_t u64;
#if 0
static inline u64 T2L()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return 1000000ULL * tv.tv_sec + tv.tv_usec;
}
#endif
static __inline__ uint64_t T2L(void)
{
	unsigned long long int x;
	__asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
	return x;
}
static u64 _t_start_;
u64 tstart()
{
	_t_start_ = T2L();
	return _t_start_;
}

u64 tdiff()
{
	return T2L() - _t_start_;
}

void ptdiff()
{
	u64 d = T2L() - _t_start_;
	printf("%llu cycles\n", (unsigned long long)d);
} 
