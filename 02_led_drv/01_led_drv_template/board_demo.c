#include "leddrv.h"

static int board_demo_led_init(int which)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}


static int board_demo_led_ctl(int which, char status)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

static struct led_opration board_demo_led_opr = {
    .init = board_demo_led_init,
    .ctl = board_demo_led_ctl,
};

static struct led_opration* get_board_demo_led_opr(void)
{
    return &board_demo_led_opr;
}