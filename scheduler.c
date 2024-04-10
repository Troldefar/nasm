#include "scheduler.h"

/**
 * Scheduler definitions
 * 
*/

void scheduler_init() {
    next_sch_pid, curr_sch_pid = 0;
}

/**
 * Use round robin algorithm for initial setup
*/

process_t *get_next_process() {
    process_t *next_process = processes[next_sch_pid];
    curr_sch_pid = next_sch_pid;
    next_sch_pid++;
    next_sch_pid = next_sch_pid % processes_count;
    return next_process;
}

/**
 * Scheduler
 * 
 * Get values "automatically" by the pusha asm instruction
*/

void scheduler(
    int eip, int edi, int esi, int ebp, int esp, int ebx, int edx, int ecx, int eax
) {
    process_t *curr_process;

    /**
     * Process definitions
    */

   curr_process = processes[curr_sch_pid];
   next_process = get_next_process();

   /**
    * If running we should snapshot
    * and set current process to ready
   */

   if (curr_process->state == RUNNING) {
        curr_process->context.eax = eax;
        curr_process->context.ecx = ecx;
        curr_process->context.edx = edx;
        curr_process->context.ebx = ebx;
        curr_process->context.esp = esp;
        curr_process->context.ebp = ebp;
        curr_process->context.esi = esi;
        curr_process->context.edi = edi;
        curr_process->context.eip = eip;
   }

   curr_process->state = READY;

   /**
    * mov next process context into registers
   */

    asm("mov %0, %%eax; \
        mov %0, %%ecx; \
        mov %0, %%edx; \
        mov %0, %%ebx; \
        mov %0, %%esi; \
        mov %0, %%edi;" 
        : : "r" (next_process->context.eax), "r" (next_process->context.ecx), "r" (next_process->context.edx), "r" (next_process->context.ebx), "r" (next_process->context.esi), "r" (next_process->context.edi)
    );

    /**
     * Next process is now being flagged as running
    */

   next_process->state = RUNNING;

}

/**
 * Enable interrupts via sti
 * jmp to next process' EIP
*/

void run_next_process() {
    asm("sti; \
        jmp *%0" : : "r" (next_process->context.eip));
}