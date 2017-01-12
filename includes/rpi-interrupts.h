#ifndef RPI_INTERRUPTS_H
#define RPI_INTERRUPTS_H

#include <stdint.h>

/** @brief See Section 7.5 of the BCM2836 ARM Peripherals documentation, the base
    address of the controller is actually xxxxB000, but there is a 0x200 offset
    to the first addressable register for the interrupt controller, so offset the
    base to the first register */
#define RPI_INTERRUPT_CONTROLLER_BASE    0x3F00B200UL

/** @brief Bits in the Enable_Basic_IRQs register to enable various interrupts.
    See the BCM2835 ARM Peripherals manual, section 7.5 */
#define RPI_BASIC_ARM_TIMER_IRQ         (1 << 0)
#define RPI_BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define RPI_BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define RPI_BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define RPI_BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define RPI_BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define RPI_BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define RPI_BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)



/*IRQ Registers Bank 1 */
#define AUX_INT                         (1 << 29)

/*Register Bank 2 */
#define I2C_SPI_SLV_INT                 (1 << 11)
#define PWA0                            (1 << 13)
#define PWA1                            (1 << 14)
#define SMI                             (1 << 16)
#define IRQ_GPIO_ENABLE_B0              (1 << 17)
#define IRQ_GPIO_ENABLE_B1              (1 << 18)
#define IRQ_GPIO_ENABLE_B2              (1 << 19)
#define I2C_IRQ                         (1 << 20)
#define SPI_IRQ                         (1 << 21)
#define PCM_IRQ                         (1 << 22)
#define UART_IRQ                        (1 << 24)



/** @brief The interrupt controller memory mapped register set */
typedef struct {
    volatile uint32_t IRQ_basic_pending;
    volatile uint32_t IRQ_pending_1;
    volatile uint32_t IRQ_pending_2;
    volatile uint32_t FIQ_control;
    volatile uint32_t Enable_IRQs_1;
    volatile uint32_t Enable_IRQs_2;
    volatile uint32_t Enable_Basic_IRQs;
    volatile uint32_t Disable_IRQs_1;
    volatile uint32_t Disable_IRQs_2;
    volatile uint32_t Disable_Basic_IRQs;
    } rpi_irq_controller_t;

extern volatile int calculate_frame_count;

/* Found in the *start.S file, implemented in assembler */
extern int get_cpsr(void);
extern int get_spsr(void);
extern void _enable_interrupts( void );
extern void _soft_reset(void);
extern rpi_irq_controller_t* RPI_GetIrqController( void );
extern void c_irq_handler(void);

#endif
