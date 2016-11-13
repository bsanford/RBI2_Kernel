#ifndef GPIO_API_H_INCLUDED
#define GPIO_API_H_INCLUDED
#include "gpio.h"
#include "gpio_aux_uart.h"



extern int set_gpio_fnct(struct gpio_pin *pin, int pin_fnc); /*Sets the function type on the stored function select register*/

extern int set_gpio_input(struct gpio_pin *pin);

extern int send_gpio_sig(struct gpio_pin *pin); /*Send 3.3v on the rail to the specified pin*/

extern int clear_gpio_sig(struct gpio_pin *pin); /*Clear 3.3v off the rail to the specified pin*/

extern void init_gpio_pins(struct gpio_pin txd_pin, struct gpio_pin rxd_pin);

extern void init_uart_pins(struct gpio_pin *txd_pin, struct gpio_pin *rxd_pin);
/*
int get_signal(struct gpio_pin *pin);

int is_gpio_lvl_hgh(struct gpio_pin *pin);

int is_gpio_lvl_low(struct gpio_pin *pin);

int set_mutex(struct gpio_pin *pin);
*/

#endif // GPIO_API_H_INCLUDED
