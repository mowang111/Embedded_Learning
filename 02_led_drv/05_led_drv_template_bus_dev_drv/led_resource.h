#ifndefine _LED_RESOURCE_H_
#define _LED_RESOURCE_H_

#define GROUP_PIN(g, p) ((g << 16) | p)
#define GROUP(x) (x >> 16)
#define PIN(x) (x & 0xffff)
/* GPIO3_0 */
/* bit[31:16] = group */
/* bit[15:0] = pin */
struct led_resource {
    int pin;
}

#endif
