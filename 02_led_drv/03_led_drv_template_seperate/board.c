#include "leddrv.h"

static led_resource led_rsc;
static chip_gpio_opr *chip_gpio;

static int board_led_init(int which)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    if(!chip_gpio)
    {
        chip_gpio = get_chip_gpio_opr();
    }
    chip_gpio->enable(which);
    chip_gpio->select(which);
    chip_gpio->direction(which, 1);
    return 0;
}


static int board_led_ctl(int which, char status)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    if(!chip_gpio)
    {
        printk("chip_gpio is NULL\n");
    }
    chip_gpio->data(which, status);
    return 0;
}

static struct led_opration board_led_opr = {
    .init = board_led_init,
    .ctl = board_led_ctl,
};

static struct led_opration* get_board_led_opr(void)
{
    return &board_led_opr;
}