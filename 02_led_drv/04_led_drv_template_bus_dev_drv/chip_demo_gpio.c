#include "leddrv.h"

static int led_pin[100];
static int led_pin_num = 0;
static struct class *led_class;

static int board_demo_led_init(int which)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    if(!led_rsc)
    {
        led_rsc = get_board_demo_led_resource();
    }
    printk("led_res: group = %d, pin = %d\n", GROUP(led_rsc->pin), PIN(led_rsc->pin));

    register_led_operations(get_board_demo_led_opr());

    switch(GROUP(led_rsc->pin))
    {
        case 0:
        {
            printk("init group 0\n");
            break;
        }
        case 1:
        {
            printk("init group 1\n");
            break;
        }
        default:
            printk("group %d not support\n", GROUP(led_rsc->pin));
            return -1;
    }
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

static struct led_opration* get_board_led_opr(void)
{
    return &board_demo_led_opr;
}

static int chip_demo_gpio_probe(struct platform_device *pdev)
{
    int i = 0;
    struct resource *res;
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    /* record pin */
    // for(i = 0; i < pdev->num_resources; i++)
    // {
    //     if(pdev->resource[i].flags == IORESOURCE_IRQ)
    //     {
    //         led_pin[led_pin_num++] = pdev->resource[i].start;
    //     }
    // }
    while(1)
    {
        res = platform_get_resource(pdev, IORESOURCE_IRQ, i++);
        if(!res)
        {
            break;
        }
        led_pin[led_pin_num++] = res->start;
    }
    

    /* device_create */
    for(i = 0; i < led_pin_num; i++)
    {
        printk("create device %d\n", i);
        led_device_create(i);
    }

    return 0;
}

static int chip_demo_gpio_remove(struct platform_device *pdev)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    int i;
    for(i = 0; i < led_pin_num; i++)
    {
        led_device_destroy(i);
    }
    led_pin_num = 0;
    return 0;
}

static struct platform_driver chip_demo_gpio_drv = {
    .probe = chip_demo_gpio_probe,
    .remove = chip_demo_gpio_remove,
    .driver = {
        .name = "my_led",
        .owner = THIS_MODULE,
    },
};

static int board_demo_led_init(void)
{
    int err;
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    err = platform_driver_register(&chip_demo_gpio_drv);
    return 0;
}

static void board_demo_led_exit(void)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    platform_driver_unregister(&board_demo_led_driver);
}

module_init(board_demo_led_init);
module_exit(board_demo_led_exit);
MODULE_LICENSE("GPL");
