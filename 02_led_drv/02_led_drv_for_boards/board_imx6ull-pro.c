#include "leddrv.h"

/* enable GPIO */
static volatile unsigned int *CCM_CCGR1;
/* select GPIO */
static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;
/* GPIO direction */
static volatile unsigned int *GPIO5_GDIR;
/* GPIO data */
static volatile unsigned int *GPIO5_DR;

static int board_demo_led_init(int which)
{
    unsigned int val;
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    /*ioremap*/
    if(which == 0)
    {
        if(CCM_CCGR1 == NULL)
        {
            CCM_CCGR1 = ioremap(0x020C406C, 4);
            IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = ioremap(0x2290014, 4);
            GPIO5_GDIR = ioremap(0x020AC000 + 0x4, 4);
            GPIO5_DR = ioremap(0x020AC000 + 0, 4);
        }
        *CCM_CCGR1 |= (3 << 30);
        val = *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;
        val &= ~(0xf);
        val |= 5;
        *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = val;
        *GPIO5_GDIR &= ~(1 << 3);
    }
    return 0;
}


static int board_demo_led_ctl(int which, char status)
{
    printk("%s %s %s\n", __FILE__, __FUNCTION__, __LINE__);
    if (status == 1)
    {
        
        *GPIO5_DR &= ~(1 << 3);
    }
    else
    {
        
        *GPIO5_DR |= (1 << 3);
    }
    return 0;
}

static struct led_opration board_demo_led_opr = {
    .num = 1;
    .init = board_demo_led_init,
    .ctl = board_demo_led_ctl,
};

static struct led_opration* get_board_demo_led_opr(void)
{
    return &board_demo_led_opr;
}