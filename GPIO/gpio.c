#include<stddef.h>
#include "gpio.h"

static int set_fnc_slct(struct gpio_pin *pin);
static int set_clr_out_dtct_reg(struct gpio_pin *pin);



/*Function init_gpio
 *Braeden Sanford 10-11-2016
 *
 *Args: *pin_arr pointer to the start of the gpio_pin set
 *       size - size of the the array (52 elements)
 *
 *       Loops over the array set and does any initialization for static
 *       register location offsets.
 */

int init_gpio(struct gpio_pin *pin_arr, unsigned int size){

unsigned int index;

if(pin_arr == NULL)
    return -1;

/*TODO add in support for appropriate func select register*/
for(index = 0; index < size; index++){
     (pin_arr + index)->mtex = 0;
     (pin_arr + index)->p_nmb = index;

     if((set_fnc_slct(pin_arr + index)) == -1)
          return (-1);

     if(set_clr_out_dtct_reg(pin_arr + index) == -1)
         return (-1);
}
return 0;
}


/*Function set_fnc_slct
 *Braeden Sanford 10-15-2016
 *
 *Args struct gpio_pin *pin this is the pin sructure
 *that is held in the gpio pin_set array
 *
 *The BCM2835 Arm Peripheral has the offsets of the function select registers
 *broken up into 5 different registers
 * pins 0 - 9 at GPIO_GPFSEL1
 *      10 -19 at GPIO_GPFSEL2
 *      .
 *       .
 *       52 at GPIO_GPFSEL 5
 */


static int set_fnc_slct(struct gpio_pin *pin){

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
    return(-1);
}


/*Function set_clr_out_dtct_reg
 * Args - Struct gpio_pin
 * Recieves a GPIO pin as an argument and based on its pin number
 * sets up the register location for gpio Pin output, Pin clear and Pin
 * Level select registers
 *
 * Todo: Add in support for the other types of registers
 */
static int set_clr_out_dtct_reg(struct gpio_pin *pin)
{

    if(pin == NULL)
        return (-1);

    if(pin->p_nmb <= 31){
        pin->gpio_clr_reg = (unsigned int *) GPIO_BASE + GPIO_GPCLR0;
        pin->gpio_lvl_reg = (unsigned int *) GPIO_BASE + GPIO_GPLEV0;
        pin->gpio_out_reg = (unsigned int *) GPIO_BASE + GPIO_GPSET0;
        return (0);
    }
    if(pin->p_nmb <= 53){
        pin->gpio_clr_reg = (unsigned int *) GPIO_BASE + GPIO_GPCLR1;
        pin->gpio_lvl_reg = (unsigned int *) GPIO_BASE + GPIO_GPLEV1;
        pin->gpio_out_reg = (unsigned int *) GPIO_BASE + GPIO_GPSET1;
        return (0);
    }

    return (-1); /*Should never reach this*/
}




