#ifndef CHIP_GPIO_H
#define CHIP_GPIO_H

struct gpio_operation {
    int (*enable)(int which);
    int (*select)(int which);
    int (*direction)(int which, char status);
    int (*data)(int which, char status);
};

struct gpio_operation* get_chip_gpio_opr(void);

#endif