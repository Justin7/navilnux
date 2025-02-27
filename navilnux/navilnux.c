#include <navilnux.h>

extern Navil_mem_mng memmng;
extern Navil_task_mng taskmng;

Navil_free_task *navilnux_current;
Navil_free_task *navilnux_next;
Navil_free_task dummyTCB;
int navilnux_current_index;
unsigned int navilnux_time_tick;

int (*navilnux_irq_vector[IRQNUM])(void);

void scheduler(void){
    navilnux_current_index++;
    navilnux_current_index %= (taskmng.max_task_id+1);

    navilnux_next = &taskmng.free_task_pool[navilnux_current_index];
    navilnux_current = navilnux_next;
    // printf("navilnux_current: %d\n", navilnux_current_index);
}

int sched_init(void){
    if(taskmng.max_task_id < 0){
        return -1;
    }

    navilnux_current = &dummyTCB;
    navilnux_next = &taskmng.free_task_pool[0];
    navilnux_current_index = -1;

    return 0;

}

void swiHandler(unsigned int syscallnum)
{
    printf("system call %d\n", syscallnum);
}

void irqHandler(void)
{
    if((ICIP&(1<<27)) != 0){
        OSSR = OSSR_M1;
        OSMR1 = OSCR + 3686400;

        navilnux_time_tick++;

        scheduler();
    }

    if (ICIP&(1<<8) != 0) {
        GEDR0 = 1;
        if (navilnux_irq_vector[IRQ8] != NULL) navilnux_irq_vector[IRQ8]();
    }
}

void navilnux_init(void){
    navilnux_time_tick = 0;
    mem_init();
    task_init();
    msg_init();
    drv_init();
    syscall_init();

    os_timer_init();
    os_timer_start();
}

void os_timer_init(void)
{
    ICCR = 0x01;

    ICMR |= (1 << 27);      
    ICLR &= ~(1 << 27);    

    OSCR = 0;
    OSMR1 = OSCR + 3686400; 

    OSSR = OSSR_M1;
}

void os_timer_start(void)
{
    OIER |= (1<<1);
    OSSR = OSSR_M1;
}

void irq_enable(void){
    __asm__("msr    cpsr_c,#0x40|0x13");
}

void irq_disable(void){
    __asm__("msr    cpsr_c,#0xc0|0x13");
}

int main(void)
{

    navilnux_init();
    navilnux_user();


    if(sched_init() < 0){
        printf("Kerenel Panic\n");
        return -1;
    }

    int i;
    for(i=0;i<=taskmng.max_task_id;i++){
        printf("TCB : TASK%d - init PC(%p) \t init SP(%p)\n", i+1, taskmng.free_task_pool[i].context_pc, taskmng.free_task_pool[i].context_sp);
    }

    // printf("REAL func TASK1 : %p\n", user_task_1);
    // printf("REAL func TASK2 : %p\n", user_task_2);
    // printf("REAL func TASK3 : %p\n", user_task_3);

    irq_enable();

    while(1){
        msleep(1000);
    }
    return 0;
}	
