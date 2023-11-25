# C From scratch

### Motivation:

When you develop in assembly sometimes it's necessery to implement auxiliary methods by yourself.<br>
Things like: printing, converting data types and extract data from strings.<br>
So i started to create thease libs for practice.<br> 
This are simple implementations that i'm sharing with you so don't expect to see great things.<br>

## an experimental implementation of C standard libs.

* no use of stdlib
* no use of libc

### C methods from scratch

- printf  (c)
- sprintf (c)
- fprintf (c)
- sscanf  (c)
- strlen  (c)
- memset  (asm)
- atoi    (asm)

### Custom methods

- memcats (asm)
- memcatc (asm)
- atoh    (asm)
- atof    (asm)
- itoa    (c)
- ctoi    (c)
- ftoa    (c)

---

#### Observation:
    *Don't use it in production!*
    Just for learning purpose edit the make file and add your own source file.
    For now the project was not compiled as shared libs so you have to link all together as a single binary.
#### Usage:

   
```c
#include <thx_io.h>

int 
main()
{
    thxio.printf("Hello, world");
    return 0;
}

```
