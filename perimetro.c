#include "types.h"
#include "defs.h"
#include <stdarg.h>

int
perimetro(int lados, ...) {
    va_list ap;  //ponteiro para a lista de argumentos variáveis

    va_start(ap, lados); 
    int per = 0;
    int i;

    for(i = 0; i < lados; i++) {
        per += va_arg(ap, int);
    }
    return per;
}