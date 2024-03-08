#include "../include/sys_init.h"
#include "../include/kmain.h"
#include "../include/kstdio.h"
#include "../arch/stm32f446re/include/sys/sys.h"
#include "../arch/stm32f446re/include/sys/stm32_peps.h"
#include <stdint.h>

//External Interrupt Handler for EXTI0
void EXTI0_Handler(void){
	kprintf("%s", "--------------BEGIN--------------\n");
	kprintf("%s", "Entering to External Interrupt 0 Handler.\n");
	kprintf("%s", "Clearing pending interrupt.\n");
	kprintf("%s", "--------------END----------------\n");
	kprintf("%s", "\n");
	__clear_pending_IRQn(EXTI0_IRQn);
}

//External Interrupt Handler for EXTI1
void EXTI1_Handler(void){
	kprintf("%s", "----------BEGIN----------------\n");
	kprintf("%s", "Entered External Interrupt 1 Handler.\n");
	kprintf("%s", "Clearing pending interrupt.\n");
	kprintf("%s", "--------------END--------------\n");
	kprintf("%s", "\n");
	__clear_pending_IRQn(EXTI1_IRQn);
}


void kmain(void){

	__sys_init();

	kprintf((uint8_t*)"%s",(uint8_t*)"Booting OS CSE: \r");
	kprintf((uint8_t*)"%s",(uint8_t*)"Version: 1.0\r\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"Welcome .... \r\n");
	
	sysTick_disable();
	sysTick_enable();


	int exti0Priority = 0;
	int exti1Priority = 0;
	while(1){
		kprintf("%s", "--------------Setup Interrupts--------------\n");
		kprintf("%s", "1. Enable EXTI0 interrupt with priority.\n");
		kprintf("%s", "2. Enable EXTI1 interrupt with priority.\n");
		kprintf("%s", "3. Exit interrupt setup.\n");
		int cmd = 0;
		kscanf("%d", &cmd);
		kprintf("%s", "\n");
		if(cmd == 1){
			kprintf("%s", "Enter priority for EXTI0 interrupt: ");
			int x = 0;
			kscanf("%d", &x);
			exti0Priority = x;
			kprintf("%s", "\n");
		}
		else if(cmd == 2){
			kprintf("%s", "Enter priority for EXTI1 interrupt: ");
			int x = 0;
			kscanf("%d", &x);
			exti1Priority = x;
			kprintf("%s", "\n");
		}
		else if(cmd == 3){
			break;
		}

	}

	__NVIC_EnableIRQn(EXTI0_IRQn);
	__NVIC_SetPriority(EXTI0_IRQn, exti0Priority);

	__NVIC_EnableIRQn(EXTI1_IRQn);
	__NVIC_SetPriority(EXTI1_IRQn, exti1Priority);


	while(1){
		kprintf("%s", "--------------Main Menu--------------\n");
		kprintf("%s", "1. Get EXTI0 interrupt priority.\n");
		kprintf("%s", "2. Get EXTI1 interrupt priority.\n");
		kprintf("%s", "3. Set PRIMASK.\n");
		kprintf("%s", "4. Clear PRIMASK.\n");
		kprintf("%s", "5. Get PRIMASK.\n");
		kprintf("%s", "6. Set BASEPRI.\n");
		kprintf("%s", "4. Unset BASEPRI.\n");
		kprintf("%s", "5. Get BASEPRI.\n");
		kprintf("%s", "9. Set FAULTMASK.\n");
		kprintf("%s", "10. Clear FAULTMASK.\n");
		kprintf("%s", "11. Get FAULTMASK.\n");
		kprintf("%s", "12. Generate EXTI0 interrupt.\n");
		kprintf("%s", "13. Generate EXTI1 interrupt.\n");
		kprintf("%s", "14. Exit Forever.\n");
		kprintf("%s", "----------------END-----------------\n");
		kprintf("%s", "Enter Choice: ");
		
		int d = 0;
		int x = 0;
		kscanf("%d", &d); 
		kprintf("%s", "\n");
		switch (d){
		case 1:
			kprintf("%s", "\n");
			kprintf("%s", "Priority for EXTI0 interrupt: ");
			x = __NVIC_GetPriority(EXTI0_IRQn);
			kprintf("%d", &x);
			kprintf("%s", "\n");
			break;
		case 2:
			kprintf("%s", "\n");
			kprintf("%s", "Priority for EXTI1 interrupt: ");
			x = __NVIC_GetPriority(EXTI1_IRQn);
			kprintf("%d", &x);
			kprintf("%s", "\n");
			break;
		case 3:
			kprintf("%s", "\n");
			__set_PRIMASK(1);
			break;
		case 4:
			kprintf("%s", "\n");
			
			kprintf("%s", "PRIMASK is cleared.");
			__enable_irq();
			break;
		case 5:
			kprintf("%s", "\n");
			kprintf("%s", "PRIMASK is set to: ");
			x = __get_PRIMASK();
			kprintf("%d", &x);
			kprintf("%s", "\n");
		case 6:
			kprintf("%s", "\n");
			kprintf("%s", "Set base priority of: ");
			kscanf("%d", &x);
			__set_BASEPRI(x);
			kprintf("%s", "\n");
			break;
		case 7:
			kprintf("%s", "\n");
			kprintf("%s", "Set new base priority of: ");
			kscanf("%d", &x);
			__unset_BASEPRI(x);
			kprintf("%s", "\n");
			break;
		case 8:
			kprintf("%s", "\n");
			kprintf("%s", "BASEPRI is set to: ");
			x = __get_BASEPRI();
			kprintf("%d", &x);
			kprintf("%s", "\n");
			break;
		case 9:
			kprintf("%s", "\n");
			__set_FAULTMASK(1);
			break;
		case 10:
			kprintf("%s", "\n");
			kprintf("%s", "FAULTMASK is cleared.");
			__enable_fault_irq();
			break;
		case 11:
			kprintf("%s", "\n");
			kprintf("%s", "FAULTMASK is set to: ");
			x = __get_FAULTMASK();
			kprintf("%d", &x);
			kprintf("%s", "\n");
			break;
		case 12:
			kprintf("%s", "\n");
			__set_pending_IRQn(EXTI0_IRQn);
			break;
		case 13:
			kprintf("%s", "\n");
			__set_pending_IRQn(EXTI1_IRQn);
			break;	
		case 14:
			kprintf("%s", "Good Bye :D\n");
			break;
		default:
			break;
		}
	}

while(1){

	
	//you can change the following line by replacing a delay function
	for(uint32_t i=0;i<1000000;i++){}	
	}

}


/*Assignment 02 Part 01 comments*/
	/* Floating point */
	/*
	float floatNum1;
	uint32_t updater = 10;
	uint32_t timeTaken = 0;
	int mainIter = 0;
	int i;
	
	kprintf((uint8_t*)"%s", (uint32_t*) "Let us print one float type now\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "Give an input for float print: ");
	kscanf((uint8_t*)"%f", (uint32_t*) &floatNum1);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "The float you have chosen is: ");
	kprintf((uint8_t*)"%f", (uint32_t*) &floatNum1);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");

	/* In all the 4 iterations SysTick will Enable first */
	/*
	sysTick_enable();
	
	for(i=1;i<5;i++){

		/* Here execution time is calculated using SysTick's getTime() function */
		/*
		timeTaken = getTime();
		kprintf((uint8_t*)"%s", (uint32_t*) "Time Taken on ");
		kprintf((uint8_t*)"%d", (uint32_t*) &i);
		kprintf((uint8_t*)"%s", (uint32_t*) "th iteration is: ");
		kprintf((uint8_t*)"%d", (uint32_t*) &timeTaken);
		kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	}

	/* We are updating the SysTick after every 1 iteration */
	/*
	updater += 10;
	updateSysTick(updater);

	/* We are printing the current value of SysTick using VAL register
	 to check if the SysTick is updating or not*/
	/*
	uint32_t valReg = getSysTickCount();
	kprintf((uint8_t*)"%s", (uint32_t*) "Current Value of VAL register of SysTick: ");
	kprintf((uint8_t*)"%d", (uint32_t*) &valReg);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");

	/* In all the 4 iterations SysTick will Disable in last */
	/*
	sysTick_disable();

	if(mainIter>4){
		break;
	}

	mainIter++;
*/


/*Assignment 01 comments*/
	/* Character */
	/*

	char c;
	char string[50];
	int digit1;
	int digit2;
	uint32_t hexa;

	/*for printf*/
	/*kprintf((uint8_t*)"%s",(uint32_t*)"Booting OS CSE: ");
	kprintf((uint8_t*)"%s",(uint32_t*)"Version: 1.0\n");
	kprintf((uint8_t*)"%s",(uint32_t*)"Welcome .... \n");


	kprintf((uint8_t*)"%s", (uint32_t*) "Let us first print a Character type\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "Give an input for character print: ");
	kscanf((uint8_t*)"%c", (uint32_t*) &c);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "The character you have chosen is: ");
	kprintf((uint8_t*)"%c", (uint32_t*) &c);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");

	/* String */
	/*
	kprintf((uint8_t*)"%s", (uint32_t*) "Let us print a String type now\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "Give an input for string print: ");
	kscanf((uint8_t*)"%s", (uint32_t*) string);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "The string you have chosen is: ");
	kprintf((uint8_t*)"%s", (uint32_t*) string);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");

	/* Integer */
	/*
	kprintf((uint8_t*)"%s", (uint32_t*) "Let us print two Integer type now\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "Give an input for integer print: ");
	kscanf((uint8_t*)"%d", (uint32_t*) &digit1);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "The first integer you have chosen is: ");
	kprintf((uint8_t*)"%d", (uint32_t*) &digit1);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");

	kprintf((uint8_t*)"%s", (uint32_t*) "Give another input for integer print: ");
	kscanf((uint8_t*)"%d", (uint32_t*) &digit2);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "The second integer you have chosen is: ");
	kprintf((uint8_t*)"%d", (uint32_t*) &digit2);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");

	int sumInt = digit1+digit2;
	kprintf((uint8_t*)"%s", (uint32_t*) "Their summation is: ");
	kprintf((uint8_t*)"%d", (uint32_t*) &sumInt);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "It's hexadecimal number is: ");
	kprintf((uint8_t*)"%x", (uint32_t*) &sumInt);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");

	/* Hexadecimal */
	/*
	kprintf((uint8_t*)"%s", (uint32_t*) "Let us print a Hexadecimal number type now\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "Give an input for hexadecimal number print: ");
	kscanf((uint8_t*)"%x", (uint32_t*) &hexa);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "The hexadecimal number you have chosen is: ");
	kprintf((uint8_t*)"%x", (uint32_t*) &hexa);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "It's decimal number is: ");
	kprintf((uint8_t*)"%d", (uint32_t*) &hexa);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");


	/* Floating Point */
	/*
	kprintf((uint8_t*)"%s", (uint32_t*) "Let us print a floating point number type now\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "Give an input for floating point number print: ");
	kscanf((uint8_t*)"%f", (uint32_t*) &floatNum1);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "The first floating point number you have chosen is: ");
	kprintf((uint8_t*)"%f", (uint32_t*) &floatNum1);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");

	kprintf((uint8_t*)"%s", (uint32_t*) "Give another input for floating point number print: ");
	kprintf((uint8_t*)"%f", (uint32_t*) &floatNum2);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	kprintf((uint8_t*)"%s", (uint32_t*) "The second floating point number you have chosen is: ");
	kprintf((uint8_t*)"%f", (uint32_t*) &floatNum2);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");

	float sumFloat = floatNum1+floatNum2;
	kprintf((uint8_t*)"%s", (uint32_t*) "Their summation is: ");
	kprintf((uint8_t*)"%f", (uint32_t*) &sumFloat);
	kprintf((uint8_t*)"%s", (uint32_t*) "\n");
	*/

