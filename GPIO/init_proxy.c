#include <stdlib.h>
#include <stdio.h>
#include "gpio.h"



struct gpio_pin *gpio_pins = NULL;


/**Function prxy_init
  *
  *Controls the initialization of the GPIO sub system
  *
  *If the sub system has not been initialized then the
  *the proxy calls the gpio sub system initialization function
  *
  *If the GPIO sub system has already been initialized then the
  *function simply returns the start address of the GPIO PIN_SET
  */

struct gpio_pin *prxy_init(void){

if(gpio_pins == NULL){
    printf("Initializing GPIO sub-system \r \n");
    init_gpio(pin_set, PIN_SET_SIZE);
    gpio_pins = pin_set;
    return gpio_pins;
    }

    printf("Subsystem is already initialized, returning address %d \r \n", (int)gpio_pins);

  return gpio_pins;

}
