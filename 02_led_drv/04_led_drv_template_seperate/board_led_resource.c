#include "led_resource.h"

/*GPIO5_0*/
static struct led_resource board_A_led_resource = {
    .pin = GROUP_PIN(5, 0),
}

struct led_resource* get_board_A_led_resource(void)
{
    return &board_A_led_resource;
}