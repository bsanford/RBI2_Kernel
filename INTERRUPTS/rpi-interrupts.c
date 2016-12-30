#include "rpi-armtimer.h"
#include "rpi-interrupts.h"
#include "user_cntrl.h"





/**There is something still not working correctly with the interrupt handler
 * The processor does not seem to be in the correct mode when the exception should be
 * vectored to the exception handler. Vector table is correct and Interrupt handlers are
 * mapped correctly. The interrupt controller on the peripheral is working as excpected as well.
 * ---Using the function below I am able to see that CPSR value is 0x600001DA which puts the mode
 *    bits in HYP mode. This is not as expected, my understanding is the processor would be in
 *    SVC mode.
 *    TODO - Research and understand what is happening with ARM processor modes and understand how and
 *           when they change.
 */



/** @brief The BCM2835/6 Interupt controller peripheral at it's base address */
static rpi_irq_controller_t* rpiIRQController =
        (rpi_irq_controller_t*)RPI_INTERRUPT_CONTROLLER_BASE;



/*TODO Needs to go into its own source file with other ARM inline assember functions */
/** Function get_cpsr
 *
 * @brief returns the ARM specific CPSR (current program status register)
 *
 * @note used to detect current processor modes and flags, see arm v7 architecture manual
 *
 * @return value stored in the cpsr reg
 */
int get_cpsr(void){

     unsigned int cpsr_reg;
     __asm__ __volatile__("mrs %0, cpsr" : "=r" (cpsr_reg));
     return cpsr_reg;
}



/**Function get_spsr
 * @brief fetches the ARM spsr (banked cpsr register)
 *
 * @return 32 bit value of the ARM spsr register
 */
int get_spsr(void){

    unsigned int spsr_reg;
    __asm__ __volatile__("mrs %0, spsr" : "=r" (spsr_reg));

    return spsr_reg;
}







/**Function RPI_GetIrqController
    @brief Return the IRQ Controller register set

    @return the pointer to the rpi_irq_controller_t structure
*/
rpi_irq_controller_t* RPI_GetIrqController( void )
{
    return rpiIRQController;
}







void __attribute__((interrupt("IRQ")))interrupt_vector(void)
{
    rpi_arm_timer_t *mytime  = RPI_GetArmTimer();
    mytime->IRQClear = 1;
}

/**
    @brief The Reset vector interrupt handler

    This can never be called, since an ARM core reset would also reset the
    GPU and therefore cause the GPU to start running code again until
    the ARM is handed control at the end of boot loading
*/
void __attribute__((interrupt("ABORT"))) reset_vector(void) {
}

/**
    @brief The undefined instruction interrupt handler

    If an undefined intstruction is encountered, the CPU will start
    executing this function. Just trap here as a debug solution.
*/
void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void) {
}


/**
    @brief The supervisor call interrupt handler

    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
void __attribute__((interrupt("SWI"))) software_interrupt_vector(void) {
}


/**
    @brief The prefetch abort interrupt handler

    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{

}


/**
    @brief The Data Abort interrupt handler

    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{

}


/**
    @brief The IRQ Interrupt handler

    This handler is run every time an interrupt source is triggered. It's
    up to the handler to determine the source of the interrupt and most
    importantly clear the interrupt flag so that the interrupt won't
    immediately put us back into the start of the handler again.
*/



/**
    @brief The FIQ Interrupt Handler

    The FIQ handler can only be allocated to one interrupt source. The FIQ has
    a full CPU shadow register set. Upon entry to this function the CPU
    switches to the shadow register set so that there is no need to save
    registers before using them in the interrupt.

    In C you can't see the difference between the IRQ and the FIQ interrupt
    handlers except for the FIQ knowing it's source of interrupt as there can
    only be one source, but the prologue and epilogue code is quite different.
    It's much faster on the FIQ interrupt handler.

    The prologue is the code that the compiler inserts at the start of the
    function, if you like, think of the opening curly brace of the function as
    being the prologue code. For the FIQ interrupt handler this is nearly
    empty because the CPU has switched to a fresh set of registers, there's
    nothing we need to save.

    The epilogue is the code that the compiler inserts at the end of the
    function, if you like, think of the closing curly brace of the function as
    being the epilogue code. For the FIQ interrupt handler this is nearly
    empty because the CPU has switched to a fresh set of registers and so has
    not altered the main set of registers.
*/
void __attribute__((interrupt("FIQ")))fast_interrupt_vector(void)
{
    rpi_arm_timer_t *mytime  = RPI_GetArmTimer();
    mytime->IRQClear = 1;
}
