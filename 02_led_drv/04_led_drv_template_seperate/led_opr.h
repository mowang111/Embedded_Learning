#ifndef _LED_OPR_H_
#define _LED_OPR_H_

struct led_opration {
    int (*init)(int which);/*init which led*/
    int (*ctl)(int which, char status);/*control which led*/
};

struct led_opration *get_board_led_opr(void);

#endif