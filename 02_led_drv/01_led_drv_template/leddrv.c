#include <stdio.h>
#include "leddrv.h"

/*register drive init function*/
static int __init led_init(void){
    /* device number */
    register_chardev();
}

