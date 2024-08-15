#include "led_resource.h"

/*GPIO5_0*/
static struct led_resource board_A_led_resource = {
    .pin = GROUP_PIN(5, 0),
}

struct led_resource* get_board_A_led_resource(void)
{
    return &board_A_led_resource;
}

static struct resource board_A_led_resources[] = {
    {
        .start = GROUP_PIN(3, 1),
        .flags = IORESOURCE_IRQ,
    },
    {
        .start = GROUP_PIN(5, 8),
        .flags = IORESOURCE_IRQ,
    },
};

struct platform_device board_A_led_dev = {
    .name = "my_led",
    .id = -1,
    .num_resources = ARRAY_SIZE(board_A_led_resources),
    .resource = board_A_led_resources
};

static int led_dev_init(void)
{
    int err;
    
    err = platform_device_register(&board_A_led_dev);

    return 0;
}

static void led_dev_exit(void)
{
    platform_device_unregister(&board_A_led_dev);
}

module_init(led_dev_init);
module_exit(led_dev_exit);
MODULE_LICENSE("GPL");