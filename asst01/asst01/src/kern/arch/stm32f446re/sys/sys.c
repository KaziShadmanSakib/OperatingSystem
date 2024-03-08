#include "../include/sys/sys.h"
#include "../../../include/kstdio.h"

uint32_t mscount = 0;
uint32_t ticksCount = 0;

/* Functions of SysTick */

/* Enables SysTick */
void sysTick_enable(void){

	/* Check if SysTick is disabled or not
	if disabled then initializing the mscount to 0 */
	if((SysTick->CTRL) & (0<<0)){
		mscount = 0;
		ticksCount = 0;
	}

	/* Enables SysTick */
	SysTick->CTRL |= (1<<0);

}

/* Disables SysTick*/
void sysTick_disable(void){

	/* Disables SysTick */
	SysTick->CTRL &= ~(1<<0);	

}

/* Returns the current value of SysTick's VAL register */
uint32_t getSysTickCount(void){

	/* Returns the current value of SysTick's VAL register */
	return SysTick->VAL;

}

/* Configures SysTick */
void sysTick_init(uint32_t ticker){

	/* Disables SysTick */
	SysTick->CTRL &= ~(1<<0);
	/* Sets contents of VAL register to 0 */
	SysTick->VAL = 0;
	/* Sets Clock source to processor clock AHB 180Mhz */
	SysTick->CTRL |= (1<<2);
	/* 1ms requires 180000 clock cycles as clock source is AHB */
	SysTick->LOAD = 180000U * ticker - 1;
	mscount = 0;
	ticksCount = 0;
	/* SysTick exception request enabled (Enable SysTick interrupt) */
	SysTick->CTRL |= (1<<1);
	/* Enables SysTick */
	SysTick->CTRL |= (1<<0);

}

/* Updates SysTick */
void updateSysTick(uint32_t updatedTicker){

	/* Disables SysTick */
	SysTick->CTRL &= ~(1<<0);
	/* Sets contents of VAL register to 0 */
	SysTick->VAL = 0;
	/* 1ms requires 180000 clock cycles as clock source is AHB */
	SysTick->LOAD = 180000U * updatedTicker - 1;
	mscount = 0;
	ticksCount = 0;
	/* Enables SysTick */
	SysTick->CTRL |= (1<<0);

}

/* Returns execution time of code block in ms */
uint32_t getTime(void){

	/* Execution time in ms */
	return mscount + ((SysTick->LOAD - SysTick->VAL) / 180000);
}

/* Updates mscount */
void SysTick_Handler(void){

	mscount = mscount + ((SysTick->LOAD + 1) / 180000);
	ticksCount++;

}

/* Functions of NVIC */

//int regNumber = IRQn/32;
//int offset = IRQn % 32;

void __NVIC_SetPriority (IRQn_TypeDef IRQn,uint32_t priority){
	if(IRQn >= 0){
		NVIC->IP[IRQn] = (uint8_t)((priority << 4));
	}
}

uint32_t __NVIC_GetPriority(IRQn_TypeDef IRQn){
	if(IRQn >= 0){
		return (NVIC->IP[IRQn] >> 4);
	}
}

void __NVIC_EnableIRQn(IRQn_TypeDef IRQn){
    if(IRQn >= 0){
        NVIC -> ISER[IRQn/32] |= (1 << (IRQn%32));
    }
}

void __NVIC_DisableIRQn(IRQn_TypeDef IRQn){
    if(IRQn >= 0){
        NVIC -> ICER[IRQn/32] |= (1 << (IRQn%32));
    }
}

uint32_t __get_pending_IRQn(IRQn_TypeDef IRQn){
    if(IRQn >= 0) {
        return (uint32_t) ( NVIC->ISPR[IRQn/32] & (uint32_t)( 1 << IRQn%32 ) );
    }
    return 0;
}

void __clear_pending_IRQn(IRQn_TypeDef IRQn) {
    if(IRQn >= 0) {
        NVIC->ICPR[IRQn/32] &= ~( (uint32_t)(1u << IRQn%32) );
    }
}

void __set_pending_IRQn(IRQn_TypeDef IRQn){
    if(IRQn >= 0) {
        NVIC->ISPR[IRQn/32] |= ( (uint32_t)(1u << IRQn%32) );
    }

}

uint32_t __NVIC_GetActive(IRQn_TypeDef IRQn){
    uint32_t activeState;
    if(IRQn >= 0){
        activeState = NVIC->IABR[IRQn/32] & (1 << IRQn % 32);
        activeState = activeState >> (IRQn % 32);
        return activeState;
    }
}

void __disable_irq(void){
    __asm volatile ("cpsid i" : : : "memory"); //CPSID I == Disable Interrupts (SET PRIMASK)
}


void __enable_irq(){
    __asm volatile ("CPSIE i"); // clears primask == enables interrupts
}


void __set_BASEPRI(uint32_t basePri){
    basePri = basePri << 4;
    __asm volatile ("MSR basepri, %0" : : "r" (basePri) : "memory");
}

// #0 for unset
void __unset_BASEPRI(uint32_t value){
    // unmask interrupts greater or equal to the given argument/priority number
    __asm volatile ("MOVS R0, #0x0");
    __asm volatile ("MSR BASEPRI, R0");
    __set_BASEPRI(value);
}


// #1 to disable all interrupts 
// #0 to allow interrupts
void __set_PRIMASK(uint32_t priMask){
    __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}

uint32_t __get_PRIMASK(void){
    uint32_t result;
    __asm volatile ("MRS %0, primask" : "=r" (result) );
    return (result);
}

void __enable_fault_irq(void){
    __asm volatile ("CPSIE f" : : : "memory");
}

// #1 to disable all interrupts 
// #0 to allow interrupts
void __set_FAULTMASK(uint32_t faultMask){
    __asm volatile ("MSR faultmask, %0" : : "r" (faultMask) : "memory");
}

void __disable_fault_irq(void){
    __asm volatile ("CPSID f" : : : "memory");  
}

uint32_t __get_FAULTMASK(void){
    uint32_t result;
    __asm volatile ("MRS %0, faultmask" : "=r" (result) );
    return (result);
}

uint32_t __get_BASEPRI(void){
    uint32_t result;
    __asm volatile ("MRS %0, basepri" : "=r" (result) );
    return (result>>4);
}
