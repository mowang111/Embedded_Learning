#include "leddrv.h"

/* register */
/* IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER2 0x2290014 */
static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER2;
/* GPIO4_GDIR 0x020AC000 + 0x4 */
static volatile unsigned int *GPIO4_GDIR;
/* GPIO4_DR 0x020AC000 + 0 */
static volatile unsigned int *GPIO4_DR;

static led_resource led_rsc;

static int board_led_init(int which)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    if(which == 0)
    {
        if(!led_rsc)
        {
            led_rsc = get_board_led_resource();
        }
        printk("led_res: group = %d, pin = %d\n", GROUP(led_rsc->pin), PIN(led_rsc->pin));

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
    }
    return 0;
}


static int board_led_ctl(int which, char status)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
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