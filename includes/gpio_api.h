#include "gpio.h"
#ifndef GPIO_API_H_INCLUDED
#define GPIO_API_H_INCLUDED


int set_gpio_fnct(struct gpio_pin *pin, int pin_fnc); /*Sets the function type on the stored function select register*/

int set_gpio_input(struct gpio_pin *pin);

int send_gpio_sig(struct gpio_pin *pin); /*Send 3.3v on the rail to the specified pin*/

int clear_gpio_sig(struct gpio_pin *pin); /*Clear 3.3v off the rail to the specified pin*/

/*
int get_signal(struct gpio_pin *pin);

int is_gpio_lvl_hgh(struct gpio_pin *pin);

int is_gpio_lvl_low(struct gpio_pin *pin);

int set_mutex(struct gpio_pin *pin);
*/

#endif // GPIO_API_H_INCLUDED
