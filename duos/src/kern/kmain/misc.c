// 	// // works, reads as 4, 100, floating point context active
// 	// // __asm volatile("MRS R0, CONTROL"); // read control_varreg value into r0
// 	// // int baal = 0;
// 	// // __asm volatile ("MOV %0, R0" : "=r" (baal) );
// 	// // kprintf("initial control_varreg value r0 = %x\n\r", baal);

// 	// // __asm volatile ("MOV R0, %0" : : "r" (input) : "memory"); // writes value to r0
// 	// // __asm volatile ("MOV %0, R0" : "=r" (control_var) ); // reads value from r0

// 	// // __asm volatile ("MRS R0, PSP");
// 	// // int control_var = 0;
// 	// // __asm volatile ("MOV %0, R0" : "=r" (control_var) );
// 	// // kprintf("reading control reg after setting = %x\n\r", control_var);

// 	// // kprintf("line 106\n\r");
// 	// // __asm volatile ("MRS R0, PSP");

// 	// // kprintf("under reading control into r0\n\r");
	
// 	// // int baal = 0;
// 	// // __asm volatile ("MOV %0, R0" : "=r" (baal) );
// 	// // kprintf("immediately before orring r0 = %x\n\r", baal);

// 	// // control_var= 0;
// 	// // __asm volatile ("MOV %0, R0" : "=r" (control_var) );
// 	// // kprintf("r0 after orring = %x\n\r", control_var);

// 	// // kprintf("under writing r0 into control\n\r");

// 	// int control_var= 0;
// 	// __asm volatile ("MOV %0, R0" : "=r" (control_var) );
// 	// kprintf("initial control_varreg value = %x\n\r", control_var);

// 	// kprintf("\n\r\n\rahahahahahahha\n\r\n\r");
// 	// __asm volatile("MRS R0, CONTROL");

// 	// control_var= 0;
// 	// __asm volatile ("MOV %0, R0" : "=r" (control_var) );
// 	// kprintf("reading control_varreg after setting = %x\n\r", control_var);

	
// 	// // __asm volatile("MSR CONTROL, R0");

// 	// kprintf("i set a lot of things and died, r0\n\r");
	
// 	// // __asm volatile("MRS R0, CONTROL");

//     // __asm volatile ("MRS R0, CONTROL");


// 	// __asm volatile ("POP {LR}");
// 	// uint32_t lr;
// 	// __asm volatile ("MOV %0, LR" : "=r" (lr));
// 	// __asm volatile ("PUSH {LR}");
// 	// kprintf("\tlr = %x\n\r", lr);

// // int a = 10;
// // int b = -1;
// // __asm volatile ("MOV R4, %0": : "r"(a));
// // __asm volatile ("MOV %0, R4": "=r" (b): );
// // kprintf("a = %d, b = %d\n\r", a, b);

// 	// __asm volatile ("BKPT 2");
// 	// __asm volatile ("MSR CONTROL, R0");
// 	// task1.task_id = 1001;
// 	// task1.run = task_func;
// 	// task1.psp = T1_STACK_START;
// 	// task1.run();

// 	// TCB_TypeDef task2;
// 	// task2.task_id = 1002;
// 	// task2.run = task_func;
// 	// task2.psp = T2_STACK_START;
// 	// task2.run();
// 	// kprintf("")






// /*
//  * Copyright (c) 2022 
//  * Computer Science and Engineering, University of Dhaka
//  * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the University nor the names of its contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
 
// #include <sys_init.h>
// #include <cm4.h>
// #include <kmain.h>
// #include <kstdio.h>
// #include <kstring.h>
// #include <stdint.h>
// #include <usart.h>
// #include <syscall_def.h>
// #include <types.h>
// #include <unistd.h>


// // TCB_TypeDef tasks[5];


// // Data use by OS
// uint32_t curr_task=0; // Current task
// uint32_t next_task=1; // Next task
// // uint32_t PSP_array[4]; // Process Stack Pointer for each task




// void task_func(void) {
// 	for(int i = 1; i <= 100000; i++) {
// 		if(i % 9091 == 0) {
// 			kprintf("i = %d\n\r", i);
// 			for(int j = 1; j <= 100000; j++);
// 		}
// 	}
// 	while(1);
// }

// void task_func2(void) {
// 	for(int i = 1; i <= 100000; i++) {
// 		if(i % 9092 == 0) {
// 			kprintf("i = %d\n\r", i);
// 			for(int j = 1; j <= 1000000; j++);
// 		}
// 	}
// 	while(1);
// }

// int last = 1000;
// int generate_task_id(void) {
// 	return last++;
// } 

// void create_task(TCB_TypeDef *tcb, void (*task_func)(void), uint32_t *stack) {
//     // Initialize the TCB fields
//     tcb->task_id = generate_task_id();  // Generate a unique ID for the task

//     // Initialize the stack for the task
// 	tcb->run = task_func;
//     tcb->psp = stack;  // Point to the top of the stack
//     *(--tcb->psp) = DUMMY_XPSR;  // xPSR
//     *(--tcb->psp) = (uint32_t) task_func;  // PC (task entry point)
//     *(--tcb->psp) = 0xFFFFFFFD;  // LR
// 	// kprintf("curr = %x\n\r", *(tcb->psp));
//     *(--tcb->psp) = 0x0000000;  // R12
//     *(--tcb->psp) = 0x0000000;  // R3
//     *(--tcb->psp) = 0x0000000;  // R2
//     *(--tcb->psp) = 0x0000000;  // R1
//     *(--tcb->psp) = 0x0000000;  // R0
	
// 	//r11 to r4
// 	for(int i = 0; i < 8; i++) {
// 		*(--tcb->psp) = 0x0000000;
// 	}
// 	__asm volatile ("BKPT 3");
// }

// void ready_queue_add(struct ready_queue *queue, TCB_TypeDef *tcb, struct TCB_node *node) {
//     // struct TCB_node *node;
//     node->tcb = *tcb;
//     node->next = NULL;

//     if (queue->tail) {
//         queue->tail->next = node;
//     } else {
//         queue->head = node;
//     }
//     queue->tail = node;
// }

// void kmain(void)
// {
// 	__sys_init();
// 	__sysTick_disable();
// 	int k = uprintf("pointless\n\r");
// 	kprintf("am i back? k = %d\n\r", uprintf("jaosidfjasd %d=k\n\r", k));
// 	// reboot();
// 	kprintf("am i dead? time = %d\n\r", get_time());

// 	TCB_TypeDef task[2];
// 	// void (*) func_list[2] = {task_func, task_func2};
// 	void (*func_list[256])(void);
// 	func_list[0] = task_func;
// 	func_list[1] = task_func2;
	
// 	create_task(task+1, task_func, (uint32_t*)(TASK_STACK_START - (TASK_STACK_SIZE)) );
// 	// for(int i = 0; i < 2; i++) {
// 	// 	create_task(task+i, task_func, (uint32_t*)(TASK_STACK_START - (i * TASK_STACK_SIZE)) );
// 	// }
// 	// struct ready_queue rq;
// 	// rq.head = NULL;
// 	// rq.tail = NULL;
// 	// struct TCB_node node;
// 	// ready_queue_add(&rq, &task[0], &node);


	
// 	// create_task(&task1, task_func, (uint32_t*)T2_STACK_START);
// 	// TCB_TypeDef * t = (&task1);
// 	// uint32_t q = (uint32_t)t;
// 	// kprintf("%x t.psp = %x, t.taskid = %d, t.run = %x\n\r", t, (*t).psp, (*t).task_id, (*t).run); //alright here
// 	// kprintf("q = %x\n\r", q);

	
// 	// uint32_t* pps = task1.psp;
// 	// for(int i = 0; i < 8; i++) {
// 	// 	kprintf("stack: i=%d: address %x: %x\n\r",i, pps, *pps ); //stack okay
// 	// 	pps++;
// 	// }

// 	// __asm volatile ("MOV R12, %0" : : "r"(q));

	
// 	// __asm volatile ("SVC #255");
// 	uprintf("\n\r\twhere am i\n\r");

// 	while(1);
// }




// TCB_TypeDef * get_current_tcb(void) {
// 	return (task + curr_task);
// }

// TCB_TypeDef * get_next_task(void) {
// 	return (task + next_task);
// }

// void set_current_tcb(TCB_TypeDef *n ) {
// 	curr_task = (curr_task + 1) % 3;
// 	next_task = (next_task + 1) % 3;
// 	return;
// }

// int cnt = 0;
// void PendSV_Handler(void)
// {
// 	// Save current context
// 	__asm volatile("MRS R0,PSP"); // Get current process stack pointer value
// 	__asm volatile("STMDB R0!,{R4-R11}"); // Save R4 to R11 in task stack (8 regs)

// 	__asm volatile("PUSH {LR}");


// 	__asm volatile("PUSH {R0}");
// 	TCB_TypeDef *t = get_current_tcb();
// 	cnt++;
// 	kprintf("curr task id = %d c = %d\n\r", t->task_id, cnt);
// 	// kprintf("t1 = %d, t2 = %d, t3 = %d\n\r", t2, t3);
// 	__asm volatile("POP {R0}");


// 	__asm volatile ("MOV %0, R0": "=r"( (*t).psp ): ); // Save current psp value


// 	// Load next context
// 	TCB_TypeDef *n = get_next_task();
// 	set_current_tcb(n);


// 	__asm volatile ("MOV R0, %0" : : "r"((*n).psp)); // Get new task psp value

// 	__asm volatile ("LDMIA R0!,{R4-R11}"); // Load R4 to R11 from taskstack (8 regs)

// 	__asm volatile("MSR PSP,R0");

// 	__asm volatile("POP {LR}");

// 	__asm volatile("BX LR");
// }

