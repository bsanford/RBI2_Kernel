#include <stddef.h>
#include "gpio_api.h"

/*Contains system driver api featrues that are supported by this Kernel*/

/*TODO get a JTAG interface working */




/*Function: send_gpio_sig
 * GIven a GPIO pin structure the function will
 * write a one to the GPIO out register
 */
int send_gpio_sig(struct gpio_pin *pin){

    if(pin == NULL)
        return (-1);

    *(pin->gpio_out_reg) = (1 << (pin->p_nmb));

    return (0);
}



/*Function: clear_gpio_sig
 *Given a GPIO pin structure the function will
 *write a one to its location in the the clear
 *register
 */
int clear_gpio_sig(struct gpio_pin *pin){
    if(pin == NULL)
        return (-1);

     *(pin->gpio_clr_reg) = (1 << (pin->p_nmb));
     return (0);

}


/*Function set fncslct_reg
 *This is used so the registers don't get clobbered when
 *ORing in different function selects.
 */
int set_fncslct_reg(struct gpio_pin *pin, int pin_func, int reg_local)
{
    int fsel_copy = *(pin->fnc_slt);
    fsel_copy &= ~(7 << reg_local);
    fsel_copy |= (pin_func << reg_local);
    return fsel_copy;
}

/*Function: set_gpio_fnct
 *Given a gpio_pin and its associated GPIO function
 *this will take the modulus of the pin number and which finds lower
 * order bits of its mapping in its function slelect location. Function
 * will then write the GPIO function assignment to the particular register:
 *
 */

int set_gpio_fnct(struct gpio_pin *pin, int pin_fnc)
{
   int fun_reg_bits;
   if(pin == NULL)
        return -1;

   fun_reg_bits = pin->p_nmb % 10;

   switch(fun_reg_bits){

   case 0:
    *(pin->fnc_slt) = set_fncslct_reg(pin,pin_fnc, 0);
    break;

   case 1:
    *(pin->fnc_slt) = set_fncslct_reg(pin,pin_fnc, 3);
    break;

   case 2:
    *(pin->fnc_slt) = set_fncslct_reg(pin,pin_fnc, 6);
    break;

   case 3:
    *(pin->fnc_slt) = set_fncslct_reg(pin,pin_fnc, 9);
    break;

   case 4:
    *(pin->fnc_slt) = set_fncslct_reg(pin,pin_fnc, 12);
    break;

   case 5:
    *(pin->fnc_slt) = set_fncslct_reg(pin,pin_fnc, 15);
    break;

   case 6:
    *(pin->fnc_slt) = set_fncslct_reg(pin,pin_fnc, 18);
    break;

   case 7:
    *(pin->fnc_slt) = set_fncslct_reg(pin,pin_fnc, 21);
    break;

   case 8:
    *(pin->fnc_slt) = set_fncslct_reg(pin,pin_fnc, 24);
    break;

   case 9:
     *(pin->fnc_slt) = set_fncslct_reg(pin,pin_fnc, 27);
    break;

   default:
    return (-1);
   }
    return(0);

}

/*Function Initializes the Mini Uart for Read and Write
 * The BCM2836 manual states that you must set the pull up reg to 0
 * then must wait for 150 cycles for the setting to take. Then set a one to the
 * pull up pull down clock to initialize the pin.
 *
 */
void init_uart_pins(struct gpio_pin *txd_pin, struct gpio_pin *rxd_pin)
{
    volatile int i;
    set_gpio_fnct(txd_pin, ALTFIVE);
    set_gpio_fnct(rxd_pin, ALTFIVE);

     *(txd_pin->gpio_pupdown) = 0;
    for( i=0; i<150; i++ ) { }
     *(txd_pin->gpio_up_dn_clk) = ( 1 << 14) | (1 << 15); /**Writes 11 to pin 14 this will enable pin 14 and 15 */
    for( i=0; i<150; i++ ) { }

     *(txd_pin->gpio_pupdown)= 0;

     *(txd_pin->gpio_up_dn_clk) = 0;

}






