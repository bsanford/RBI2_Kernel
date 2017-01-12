#include<stddef.h>
#include "gpio.h"


static int init_fnc_slct(struct gpio_pin *pin);
static int init_clr_out_dtct_reg(struct gpio_pin *pin);

/**
 * Function init_gpio
 * @brief takes a pointer to the start of a pin array iterates of the
 *        gpio pin structure array and initializes all of its registers
 * @param pin_arr
 * @param size
 * @return
 */

int init_gpio(struct gpio_pin *pin_arr, unsigned int size){

int index;

if(pin_arr == NULL)
    return -1;

/*TODO add in support for appropriate func select register*/
for(index = 0; index < size; index++){

     (pin_arr + index)->p_nmb = index;

     init_lock(&((pin_arr + index)->hw_lock)); /*address of the hwlock at that index */

     if((init_fnc_slct(pin_arr + index)) == -1)
          return (-1);

     if(init_clr_out_dtct_reg(pin_arr + index) == -1)
         return (-1);
}
return 0;
}



/**Function init_func_slct
 *
 * @brief takes a pin number and initializes the pin to the correct function select
 *         register
 *
 * @param pin
 * @return returns 0 on success and returns -1 on failure would only fail if
 *          this got a value greater than 53.
 */

static int init_fnc_slct(struct gpio_pin *pin){

    if(pin == NULL)
        return (-1);

    if(pin->p_nmb <= 9){
         pin->fnc_slt = (unsigned int *) GPIO_BASE + GPIO_GPFSEL0;
         return (0);
         }
    if(pin->p_nmb <= 19){
         pin->fnc_slt = (unsigned int *) GPIO_BASE + GPIO_GPFSEL1;
         return (0);
    }

    if(pin->p_nmb <= 29){
        pin->fnc_slt = (unsigned int *) GPIO_BASE + GPIO_GPFSEL2;
        return (0);
    }

    if(pin->p_nmb <= 39){
        pin->fnc_slt = (unsigned int *) GPIO_BASE + GPIO_GPFSEL3;
        return(0);
    }

   if(pin->p_nmb <= 49){
        pin->fnc_slt = (unsigned int *) GPIO_BASE + GPIO_GPFSEL4;
        return(0);
   }

   if(pin->p_nmb <= 53){
        pin->fnc_slt = (unsigned int *) GPIO_BASE + GPIO_GPFSEL5;
        return (0);
   }

    /*If we have gotten here it is an error*/
    return(-1); /*Would like to trap this with an interrupt to blink an LED at some point*/
}


/**Function init_clr_out_dtct_reg
 * @brief maps the gpio banked registers to the GPIO pin structures
 * @param pin
 * @return returns 0 on success -1 if there is a failure
 */
static int init_clr_out_dtct_reg(struct gpio_pin *pin)
{

    if(pin == NULL)
        return (-1);

    if(pin->p_nmb <= 31){
        pin->gpio_clr_reg   = (unsigned int *) GPIO_BASE + GPIO_GPCLR0;
        pin->gpio_lvl_reg   = (unsigned int *) GPIO_BASE + GPIO_GPLEV0;
        pin->gpio_out_reg   = (unsigned int *) GPIO_BASE + GPIO_GPSET0;
        pin->gpio_up_dn_clk = (unsigned int *) GPIO_BASE + GPIO_GPPUDCLK0;
        pin->gpio_pupdown   = (unsigned int *) GPIO_BASE + GPIO_GPPUD;
        pin->evnt_dtct      = (unsigned int *) GPIO_BASE + GPIO_GPEDS0;
        pin->gpio_low_dtct  = (unsigned int *) GPIO_BASE + GPIO_GPLEN0;
        return (0);
    }
    if(pin->p_nmb <= 53){
        pin->gpio_clr_reg = (unsigned int *) GPIO_BASE + GPIO_GPCLR1;
        pin->gpio_lvl_reg = (unsigned int *) GPIO_BASE + GPIO_GPLEV1;
        pin->gpio_out_reg = (unsigned int *) GPIO_BASE + GPIO_GPSET1;
        pin->gpio_up_dn_clk = (unsigned int *) GPIO_BASE + GPIO_GPPUDCLK1;
        pin->gpio_pupdown = (unsigned int *) GPIO_BASE + GPIO_GPPUD; /*Same for both*/
        pin->evnt_dtct      = (unsigned int *) GPIO_BASE + GPIO_GPEDS1;
        pin->gpio_low_dtct  = (unsigned int *) GPIO_BASE + GPIO_GPLEN1;
        return (0);
    }

    return (-1); /*Should never reach this*/
}









