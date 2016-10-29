#include "gpio_aux_uart.h"
#define SYS_FREQ 250000000

/*Function returns the singleton UART base address from the broadcom
  2835 peripheral.
*/

static struct gpio_uart  *aux_uart  = (struct gpio_uart*) AUX_BASE;
void RPI_SetGpioPinFunction(struct gpio_pin *pin, int pin_func );

struct gpio_uart* RPI_GetAux( void )
{
    return aux_uart;
}



/* Function was used from www.valvers.com baremetal tutorials Part5 graphics progoramming. I
   used this to integrate into my implmentation of GPIO interface.
   Define the system clock frequency in MHz for the baud rate calculation.
   This is clearly defined on the BCM2835 datasheet errata page:
   http://elinux.org/BCM2835_datasheet_errata */


void RPI_AuxMiniUartInit( int baud, int bits, struct gpio_pin *txd_pin, struct gpio_pin *rxd_pin)
{

    /* As this is a mini uart the configuration is complete! Now just
       enable the uart. Note from the documentation in section 2.1.1 of
       the ARM peripherals manual:

       If the enable bits are clear you will have no access to a
       peripheral. You can not even read or write the registers */
     aux_uart->ENABLES = AUX_ENA_MINIUART;
    /* Disable interrupts for now */
    /* auxillary->IRQ &= ~AUX_IRQ_MU; */

    aux_uart->MU_IER = 0;
    /* Disable flow control,enable transmitter and receiver! */
    aux_uart->MU_CNTL = 0;

    /* Decide between seven or eight-bit mode */
    if( bits == 8 )
        aux_uart->MU_LCR = AUX_MULCR_8BIT_MODE;
    else
        aux_uart->MU_LCR = 0;

    aux_uart->MU_MCR = 0;

    /* Disable all interrupts from MU and clear the fifos */
    aux_uart->MU_IER = 0;

    aux_uart->MU_IIR = 0xC6;

    /* Transposed calculation from Section 2.2.1 of the ARM peripherals
       manual */
    aux_uart->MU_BAUD = ( (SYS_FREQ / ( 8 * baud )) ) - 1;
    /* Disable flow control,enable transmitter and receiver! */
    aux_uart->MU_CNTL = AUX_MUCNTL_TX_ENABLE;
}





/*Function RPI AuxMiniUartWrite was used from www.valvers.com baremetal tutorials
  part5*/
void RPI_AuxMiniUartWrite( char c )
{
    //struct gpio_uart *auxillary = RPI_GetAux();
    /* Wait until the UART has an empty space in the FIFO */
    while( ((aux_uart->MU_LSR) & AUX_MULSR_TX_EMPTY)  == 0 ) { }

    /* Write the character to the FIFO for transmission */
    aux_uart->MU_IO = c;
}