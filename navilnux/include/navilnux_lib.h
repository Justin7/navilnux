#ifndef _NAVIL_LIB
#define _NAVIL_LIB

extern int mysyscall(int, int, int);


extern int itc_send(int,int);
extern int itc_get(int,int*);

extern int sem_p(int);
extern int sem_v(int);

extern void call_scheduler(void);

extern int open(int, int);
extern int read(int, void*, int);
extern int write(int, void*, int);
extern int close(int);

int navilnux_itc_send(int, int);
int navilnux_itc_get(int);
int navilnux_sem_p(int);
int navilnux_sem_v(int);
int navilnux_mutex_wait(int);
int navilnux_mutex_release(int);
void* navilnux_malloc(int);
int navilnux_free(void*);
int open(int, int);
int read(int, void*, int);
int write(int, void*, int);
int close(int);

int navilnux_sleep(int);

#endif
