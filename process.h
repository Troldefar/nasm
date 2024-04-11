int processes_count, curr_pid;

void process_init();
process_t *process_create(int *);

typedef enum process_state {READY, RUNNING} process_state_t;

/**
 * 
 * Process table setup
 * 
 * PCBs which enables us to snapshot @ a context switch
 * From example: PID N+1 to PID N+2
*/


/**
 * Actual process context
*/

typedef struct process_context {
    int eax, edx, ecx, ehx, ebx, esp, esb, esi, edi, eip, ebp;
} process_context_t;

/**
 * PCB
*/

typedef struct process {
    int pid;
    process_context_t context;
    process_state_t state;
    int *base_address; /** jmp EIP when process should be run */
} process_t;

process_t *processes[15];