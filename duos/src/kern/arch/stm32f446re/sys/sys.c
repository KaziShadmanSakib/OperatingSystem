// #include "../include/sys/sys.h"



// void DRV_FPU_ACTIVE(void) {
//     SCB->CPACR |= ((3UL << 10*2) |  (3UL << 11*2)  );
// }
// /*
// * Systick related functions begin
// */
// static uint32_t mscount;

// void sysTick_init(uint32_t val)
// {
//     sysTick_disable();
//     mscount = 0;
//     SysTick->LOAD = val; // set reload value
//     SysTick->VAL = 0; // set current value
//     SysTick->CTRL |= (1 << 2); // select AHB as clock source AHB clock == 180MHz
//     SysTick->CTRL |= (1 << 1); // enable SysTick exception request 
//     sysTick_enable();
// }

// void sysTick_enable(void)
// {
//     SysTick->CTRL |= 1 << 0; // enable systick
// }

// void sysTick_disable(void)
// {
//     SysTick->CTRL &= ~(1 << 0); // disable systick
// }

// uint32_t sysTick_check_enabled(void)
// {
//     if(SysTick->CTRL & (1<<0))
//     {
//         return 1;
//     }
//     return 0;
// }

// uint32_t getSysTickCount(void)
// {
//     // returns content of the val register
//     uint32_t val = 0;
//     val |= SysTick->VAL;
//     return val;
// }

// void updateSysTick(uint32_t update_val)
// {
//     sysTick_init(update_val);
// }

// uint32_t getTime(void)
// {
//     uint32_t highest_val = 0;
//     highest_val |= SysTick->LOAD;
    
//     int ticks = highest_val - getSysTickCount();
//     float time = ticks / (180 * 1000);

//     int extra = (int) time;
//     return ( (mscount) + extra ); // fix this: microseconds are not accurate
// }

// void update_mscount(void)
// {
//     mscount += 10;
// }

// uint32_t get_mscount(void)
// {
//     return mscount;
// }

// /*
// * Systick related functions end
// */

// /*
// * NVIC related functions begin
// */

// void SetPriorityGroup(uint32_t group) 
// {
//     SCB->AIRCR |= (0x5FA << 16) | (group << 24);
// }

// void __NVIC_SetPriority (IRQn_TypeDef IRQn, uint32_t priority)
// {
//     if(IRQn >= 0) {
//         // setting priority via the interrupt priority register
//         NVIC->IPR[IRQn] |= ( priority << (4) );
//     }
// }

// uint32_t __NVIC_GetPriority (IRQn_TypeDef IRQn) 
// {
//     uint32_t toReturn = 0;
//     if(IRQn >= 0) {
//         toReturn |= ( ( NVIC->IPR[IRQn] >> 4 ) & 0xFF);
//     }
//     return toReturn;
// }

// void __NVIC_EnableIRQn(IRQn_TypeDef IRQn)
// {
//     if(IRQn >= 0) {
//         int8_t index = IRQn / 32;
//         int8_t position = IRQn % 32;
//         // enables via the set enable register
//         NVIC->ISER[index] |= (1 << position);
//     }
// } 

// void __NVIC_DisableIRQn(IRQn_TypeDef IRQn)
// {
//     if(IRQn >= 0) {
//         int8_t index = IRQn / 32;
//         int8_t position = IRQn % 32;
//         // disables via the clear enable register
//         NVIC->ICER[index] &= ~( 1 << position );
//     }
// } 

// uint32_t __NVIC_GetActive (IRQn_TypeDef IRQn)
// {
//     if(IRQn >= 0) {
//         uint32_t index = IRQn / 32;
//         uint32_t position = IRQn % 32;
//         // returns active status of interrupt
//         return (uint32_t) ( NVIC->IABR[index] & (uint32_t)( 1 << position ) );
//     }
//     return 0;
// }

// uint32_t __get_pending_IRQn(IRQn_TypeDef IRQn)
// {
//     if(IRQn >= 0) {
//         uint32_t index = IRQn / 32;
//         uint32_t position = IRQn % 32;        
//         // returns the pending status of an interrupt, 1 = pending, 0 = not pending
//         return (uint32_t) ( NVIC->ISPR[index] & (uint32_t)( 1 << position ) );
//     }
//     return 0;
// }

// void __clear_pending_IRQn(IRQn_TypeDef IRQn) 
// {
//     if(IRQn >= 0) {
//         uint32_t index = IRQn / 32;
//         uint32_t position = IRQn % 32;        
//         // clears the interrupt pending bit
//         NVIC->ICPR[index] &= ~( (uint32_t)(1u << position) );
//     }
// }

// void __set_pending_IRQn(IRQn_TypeDef IRQn)
// {
//     if(IRQn >= 0) {
//         uint32_t index = IRQn / 32;
//         uint32_t position = IRQn % 32;        
//         // clears the interrupt pending bit
//         NVIC->ISPR[index] |= ( (uint32_t)(1u << position) );
//     }

// }

// void __disable_irq(void)
// {
//     __asm volatile ("cpsid i" : : : "memory"); 
// }


// void __enable_irq()
// {
//     __asm volatile ("CPSIE i"); // clears primask == enables interrupts
// }


// void __set_BASEPRI(uint32_t basePri)
// {
//     basePri = basePri <<4;
//     __asm volatile ("MSR basepri, %0" : : "r" (basePri) : "memory");
// }

// void __unset_BASEPRI(uint32_t value)
// {
//     // unmask interrupts greater or equal to the given argument/priority number
//     __asm volatile ("MOVS R0, #0x0");
//     __asm volatile ("MSR BASEPRI, R0");
//     __set_BASEPRI(value);
// }

// void __set_PRIMASK(uint32_t priMask)
// {
//     __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
// }

// uint32_t __get_PRIMASK(void)
// {
//     uint32_t result;
//     __asm volatile ("MRS %0, primask" : "=r" (result) );
//     return (result);
// }

// void __enable_fault_irq(void)
// {
//     __asm volatile ("CPSIE f" : : : "memory");
// }
// void __set_FAULTMASK(uint32_t faultMask)
// {
//     __asm volatile ("MSR faultmask, %0" : : "r" (faultMask) : "memory");
// }

// void __disable_fault_irq(void)
// {
//     __asm volatile ("CPSID f" : : : "memory");  
// }

// uint32_t __get_FAULTMASK(void)
// {
//     uint32_t result;
//     __asm volatile ("MRS %0, faultmask" : "=r" (result) );
//     return (result);
// }

// uint32_t __get_BASEPRI(void)
// {
//     uint32_t result;
//     __asm volatile ("MRS %0, basepri" : "=r" (result) );
//     return (result>>4);
// }
