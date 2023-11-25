# C From strach

### Motivation:

When i was learning assembly, i notice that i have to implement some methods by myself. <br>
So i started to create thease libs as prof of concept.<br> 
This are simple implementations that i'm sharing with you so don't expect to see professional things.<br>

## an experimental implementation of C standard libs.

* no use of stdlib
* no use of libc

### C methods from strach

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
    For now the project was not compiled as shared libs so you i have to link all together as a single binary.
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
