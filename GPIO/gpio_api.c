#include <stddef.h>
#include <stdio.h>
#include "gpio_api.h"
#include "init_proxy.h"



/*Contains system driver api featrues that are supported by this Kernel*/

/*TODO get a JTAG interface working */
static struct gpio_api_funcs gpio;
void set_gpio_pin_on(struct gpio_pin *pin);
void set_gpio_pin_off(struct gpio_pin *pin);
int send_gpio_sig(struct gpio_pin *pin);
int clear_gpio_sig(struct gpio_pin *pin);
int set_fncslct_reg(struct gpio_pin *pin, int pin_func, int reg_local);
int set_gpio_fnct(struct gpio_pin *pin, int pin_fnc);
void init_uart_pins(struct gpio_pin *txd_pin, struct gpio_pin *rxd_pin);



/** Function: Init JTAG
    Initilizes the set of GPIO pins for use with a JTAG emulator. This requires
    Additional hardware for the JTAG interface pins.
*/
void init_jtag(void){



}


/** Function set_gpio_pin_on
 *
 *  Sets the signal and waits for the
 *  appropriate period of time for the hardware
 *  change to take effect (150 cycles)
 */

void set_gpio_pin_on(struct gpio_pin *pin){

   volatile int count;

    printf("Setting Hardware Lock on PIN %d \r \n", pin->p_nmb);

    if(pin->hw_lock.islocked(&(pin->hw_lock))){
        printf("ERROR- PIN %d IS CURRENTLY LOCKED ! \r \n", pin->p_nmb);
        return;
        }

     pin->hw_lock.set_mutex_lock(&(pin->hw_lock));

    if(set_gpio_fnct(pin, OUTPUT) == -1){
        printf("ERROR - could not set pin as output \r \n");
    }

    for(count = 0; count < 150; count++);

    send_gpio_sig(pin);

}




/** Function set_gpio_pin_off
 *  waits 150 cycles and clears the pin
 *  150 cycles is required by the hardware for
 *  the change to take effect.
 *
 *  Always wait 150 cycles in case it is turned on and
 *  then immediatly turned off again.
 */

void set_gpio_pin_off(struct gpio_pin *pin){

    volatile int count;

    for(count = 0; count < 150; count++);

    pin->hw_lock.rmv_mutex_lock(&(pin->hw_lock));
    clear_gpio_sig(pin);

}



/**Function: send_gpio_sig
 * Create a 3.3v signal to the specfied RP5810
 * signal.
 *
 */
int send_gpio_sig(struct gpio_pin *pin){

   volatile unsigned int tmp_reg_val = 0;

    if(pin == NULL)
        return (-1);

    tmp_reg_val |= 1 << (pin->p_nmb);

    *(pin->gpio_out_reg) = tmp_reg_val;

    return (0);
}



/**Function: clear_gpio_sig
 *Given a GPIO pin structure the function will
 *write a one to its location in the the clear
 *register
 */
int clear_gpio_sig(struct gpio_pin *pin){

  volatile unsigned int tmp_reg_val = 0;

    if(pin == NULL)
        return (-1);

     tmp_reg_val |= 1 << (pin->p_nmb);

     *(pin->gpio_clr_reg) = tmp_reg_val;
     return (0);

}


/**Function: set fncslct_reg
 *This is used so the registers don't get clobbered when
 *ORing in different function selects.
 */
int set_fncslct_reg(struct gpio_pin *pin, int pin_func, int reg_local){
    int fsel_copy = *(pin->fnc_slt);
    fsel_copy &= ~(7 << reg_local);
    fsel_copy |= (pin_func << reg_local);
    return fsel_copy;
}

/**Function: set_gpio_fnct
 *Given a gpio_pin and its associated GPIO function
 *this will take the modulus of the pin number and which finds lower
 * order bits of its mapping in its function slelect location. Function
 * will then write the GPIO function assignment to the particular register:
 *
 */

int set_gpio_fnct(struct gpio_pin *pin, int pin_fnc){

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

/**Function Initializes the Mini Uart for Read and Write
 * The BCM2836 manual states that you must set the pull up reg to 0
 * then must wait for 150 cycles for the setting to take. Then set a one to the
 * pull up pull down clock to initialize the pin.
 */

void init_uart_pins(struct gpio_pin *txd_pin, struct gpio_pin *rxd_pin)
{
    volatile int i;

    set_gpio_fnct(txd_pin, ALTFIVE);
    set_gpio_fnct(rxd_pin, ALTFIVE);
    txd_pin->hw_lock.set_mutex_lock(&(txd_pin->hw_lock));
    txd_pin->hw_lock.set_mutex_lock(&(rxd_pin->hw_lock));

     *(txd_pin->gpio_pupdown) = 0;
    for( i=0; i<150; i++ ) { }
     *(txd_pin->gpio_up_dn_clk) = ( 1 << 14) | (1 << 15); /**Writes 11 to pin 14 this will enable pin 14 and 15 */
    for( i=0; i<150; i++ ) { }

     *(txd_pin->gpio_pupdown)= 0;

     *(txd_pin->gpio_up_dn_clk) = 0;

}




/**Function init_gpio_api
  *
  *Initializes the GPIO facade for the system
  *In this way all of the functions necessary for the GPIO
  *are embedded in the gpio_api_funcs structucture and can
  *be accessed by returning the singleton address;
  */


struct gpio_api_funcs *init_gpio_api_funcs(void){
gpio.init_uart_pins = &init_uart_pins;
gpio.set_gpio_fnct = &set_gpio_fnct;
gpio.set_gpio_pin_off = &set_gpio_pin_off;
gpio.set_gpio_pin_on = &set_gpio_pin_on;
gpio.init_gpio = &prxy_init;
gpio.mini_uart_init = &mini_uart_init;
gpio.uart_buff_read = &uart_buff_read;
init_gpitor(&(gpio.itor), pin_set, PIN_SET_SIZE);
return &gpio;
}




