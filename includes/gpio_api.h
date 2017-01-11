#ifndef GPIO_API_H_INCLUDED
#define GPIO_API_H_INCLUDED
#include "gpio.h"
#include "gpio_aux_uart.h"
#include "gpio_iterator.h"


/**GPIO_API
  *
  *Facade Design Pattern in which all the
  *api functions are accessed through.
  *
  *Call the init_gpio_api_func to get the address
  *of the strucutre of pointers containing all the
  *functions available to the GPIO sub system
  */


struct gpio_api_funcs{

void (* set_gpio_pin_on)  (struct gpio_pin *pin);
void (* set_gpio_pin_off) (struct gpio_pin *pin);
int  (* set_gpio_fnct) (struct gpio_pin *pin, int pin_fnc);
void (* init_uart_pins) (struct gpio_pin *txd_pin, struct gpio_pin *rxd_pin);
struct gpio_pin * (* init_gpio )(void); /*Need to consider this carefully*/
void (* mini_uart_init)(int baud, int bits);
void (* uart_buff_read)(char *ptr, int len, char delim);
int  (* low_lvl_dtct) (struct gpio_pin *pin);
int  (* clr_evnt) (struct gpio_pin *pin);
struct gpio_itor itor;
};


extern struct gpio_api_funcs *init_gpio_api_funcs(void);
#endif // GPIO_API_H_INCLUDED
