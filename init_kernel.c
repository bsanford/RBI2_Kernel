#include <stdio.h>
#include "user_cntrl.h"
#include "rpi-interrupts.h"




/*Func: Kernel_Main
 *
 * ARGS: r0, r1 and atags. TODO get definitions from arm processor manual
 *
 *Currently just initializes the GPIO in set and runs a GPIO test
 */

void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{

    struct gpio_api_funcs *gpio = init_gpio_api_funcs();
    gpio->init_gpio();

    gpio->init_uart_pins(gpio->itor.get_node_at_index(&(gpio->itor), 14),
                         gpio->itor.get_node_at_index(&(gpio->itor), 15)); // Need to init the uart before the pins
    gpio->mini_uart_init(115200, 8);
    printf("Initializing interrupt controller \r \n");
    gpio->set_gpio_pin_on(gpio->itor.get_node_at_index(&(gpio->itor), 21)); /*Initalize reset line*/
    printf("Setting Pin 21 as reset line \r \n");
    printf("Setting GPIO pin 21 to high \r \n");
    gpio->low_lvl_dtct(gpio->itor.get_node_at_index(&(gpio->itor),21));

    printf("Enabling pin 21 as low level detect \r \n");

    rpi_irq_controller_t *myirq = RPI_GetIrqController();
    printf("Enabled IRQ on pin bank 0 \r \n");
    myirq->Enable_IRQs_2 =IRQ_GPIO_ENABLE_B0;
    _enable_interrupts();
    gpio_sys();

}








