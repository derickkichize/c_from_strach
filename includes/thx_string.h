#include <thx_types.h>
#include <thx_io.h>

extern void*  __x64_memcats (void*, void*);
extern void*  __x64_memcatc (void*, char);

extern void*  __x64_memset (void *, int, size_t); 
long unsigned int strlen (const char*);

void* memset (void *, int, size_t); 
int   atoi   (char);
void  ftoa   (float, char*, int);
