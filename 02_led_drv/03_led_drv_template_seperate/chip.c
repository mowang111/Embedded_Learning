#include "led_resource.h"
#include "leddrv.h"
#include "chip_gpio.h"

/* register */
/* IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER2 0x2290014 */
static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER2;
/* GPIO4_GDIR 0x020AC000 + 0x4 */
static volatile unsigned int *GPIO4_GDIR;
/* GPIO4_DR 0x020AC000 + 0 */
static volatile unsigned int *GPIO4_DR;


static int chip_enable_gpio(int which)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

static int chip_select_gpio(int which)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

static int chip_gpio_direction(int which, char status)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

static int chip_gpio_data(int which, char status)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

static struct gpio_opration chip_gpio_opr = {
    .enable = chip_enable_gpio,
    .select = chip_select_gpio,
    .direction = chip_gpio_direction,
    .data = chip_gpio_data,
};

static struct gpio_opration* get_chip_gpio_opr(void)
{
    return &chip_gpio_opr;
}
