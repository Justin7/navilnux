#include <navilnux.h>

extern Navil_msg_mng msgmng;
extern Navil_mem_mng memmng;

unsigned int navilnux_syscallvec[SYSCALLNUM];

int sys_mysyscall(int a,int b, int c){
	printf("My systemcall - %d %d %d", a, b, c);
	return 333;
}

int sys_itcsend(int itcnum, int data){
	return msgmng.itc_send(itcnum,data);
}

int sys_itcget(int itcnum, int* data){
	return msgmng.itc_get(itcnum,data);
}

int sys_semp(int semnum){
	return msgmng.sem_p(semnum);
}

int sys_semv(int semnum){
	return msgmng.sem_v(semnum);
}

void* sys_malloc(int size){
	return memmng.malloc(size);
}

int sys_free(void *addr){
	return memmng.free(addr);
}

void syscall_init(void){
	navilnux_syscallvec[SYS_MYSYSCALL] = (unsigned int)sys_mysyscall;
	navilnux_syscallvec[SYS_ITCSEND] = (unsigned int)sys_itcsend;
	navilnux_syscallvec[SYS_ITCGET] = (unsigned int)sys_itcget;
	navilnux_syscallvec[SYS_SEMP] = (unsigned int)sys_semp;
	navilnux_syscallvec[SYS_SEMV] = (unsigned int)sys_semv;
	navilnux_syscallvec[SYS_MALLOC] = (unsigned int)sys_malloc;
	navilnux_syscallvec[SYS_FREE] = (unsigned int)sys_free;
}