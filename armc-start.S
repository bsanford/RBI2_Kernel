//Startup modified from the Valvers start up to work
//with the Raspberry PI v1.1 which puts the system in
//Hyp mode on initialization. The stack set up is
//different. There is only one hypervisor stack
//uses the architecture extentions so that eret can
//be used when returning from the prologue of the
//the Interrupt

.arch_extension sec
.arch_extension virt

.section ".text.startup"

.global _start
.global _get_stack_pointer
.global _exception_table
.global _enable_interrupts
.global _soft_reset


.equ    CPSR_MODE_USER,         0x10
.equ    CPSR_MODE_FIQ,          0x11
.equ    CPSR_MODE_IRQ,          0x12
.equ    CPSR_MODE_SVR,          0x13
.equ    CPSR_MODE_ABORT,        0x17
.equ    CPSR_MODE_UNDEFINED,    0x1B
.equ    CPSR_MODE_SYSTEM,       0x1F

// See ARM section A2.5 (Program status registers)
.equ    CPSR_IRQ_INHIBIT,       0x80
.equ    CPSR_FIQ_INHIBIT,       0x40
.equ    CPSR_THUMB,             0x20

.equ	SCTLR_ENABLE_DATA_CACHE,        0x4
.equ	SCTLR_ENABLE_BRANCH_PREDICTION, 0x800
.equ	SCTLR_ENABLE_INSTRUCTION_CACHE, 0x1000



_start:
   ldr  pc, _reset_
   ldr  pc, _undefined_instruction_vector
   ldr  pc, _software_interrupt_vector
   ldr  pc, _prefetch_abort_vector
   ldr  pc, _data_abort_vector
   ldr  pc, _data_abort_vector
   ldr  pc, _interrupt_vector
   ldr  pc, _fast_interrupt_vector

   _reset_:                          .word   _reset
   _undefined_instruction_vector:    .word   undefined_instruction_vector
   _software_interrupt_vector:       .word   software_interrupt_vector
   _prefetch_abort_vector:           .word   prefetch_abort_vector
   _data_abort_vector:               .word   data_abort_vector
   _interrupt_vector:                .word    _irq_handler
   _fast_interrupt_vector:           .word   fast_interrupt_vector




_reset:
    mov     r0, #0x8000
    mcr     P15, 4, r0, c12, c0, 0
    mov sp, #0x8000


    // Enable L1 Cache -------------------------------------------------------

    // R0 = System Control Register
    mrc p15,0,r0,c1,c0,0

    // Enable caches and branch prediction
    orr r0,#SCTLR_ENABLE_BRANCH_PREDICTION
    orr r0,#SCTLR_ENABLE_DATA_CACHE
    orr r0,#SCTLR_ENABLE_INSTRUCTION_CACHE

    // System Control Register = R0
    mcr p15,0,r0,c1,c0,0

    // Enable VFP ------------------------------------------------------------

    // r1 = Access Control Register
    MRC p15, #0, r1, c1, c0, #2
    // enable full access for p10,11
    ORR r1, r1, #(0xf << 20)
    // Access Control Register = r1
    MCR p15, #0, r1, c1, c0, #2
    MOV r1, #0
    // flush prefetch buffer because of FMXR below
    MCR p15, #0, r1, c7, c5, #4
    // and CP 10 & 11 were only just enabled
    // Enable VFP itself
    MOV r0,#0x40000000
    // FPEXC = r0
    FMXR FPEXC, r0


    bl      _cstartup

    // If main does return for some reason, just catch it and stay here.
_inf_loop:
    b       _inf_loop


_get_stack_pointer:
    // Return the stack pointer value
    str     sp, [sp]
    ldr     r0, [sp]

    // Return from the function
    mov     pc, lr


_enable_interrupts:
    mrs     r0, cpsr
    bic     r0, r0, #0x80
    msr     cpsr_c, r0

    mov     pc, lr


_disable_irq:
    mrs    r0, cpsr
    orr     r0, r0, #0x80
    msr     cpsr_c, r1

    mov      pc, lr


_irq_handler:
   push {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
   bl       irq_handler
   pop  {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
   eret


//added this for any future protection required
_soft_reset:
    b _reset

