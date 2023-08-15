#include <navilnux.h>

extern Navil_task_mng taskmng;
extern Navil_msg_mng msgmng;

void user_task_1(void){
	int a,b,c;
	a =1;
	b =2;
	c =a+b;

	int *ptr_a,*ptr_b,*ptr_c,*ptr_d;

	ptr_a =(int*)navilnux_malloc(2048);
	printf("Dynamic mem alloc - %p\n",ptr_a);

	ptr_b =(int*)navilnux_malloc(3072);
	printf("Dynamic mem alloc - %p\n",ptr_b);

	navilnux_free(ptr_b);

	ptr_c =(int*)navilnux_malloc(4096);
	printf("Dynamic mem alloc - %p\n",ptr_c);

	ptr_d =(int*)navilnux_malloc(1024);
	printf("Dynamic mem alloc - %p\n",ptr_d);

	while(1){
		printf("TASK1 - a:%p\t b:%p\t c:%p\t\n", &a,&b,&c);
		msleep(1000);
	}
}

void user_task_2(void){
	int a,b,c;
	a =1;
	b =2;
	c =a+b;
	while(1){
		printf("TASK2 - a:%p\t b:%p\t c:%p\t\n", &a,&b,&c);

		printf("ITC count is %d\n",a);
		if(a == 3){
			navilnux_itc_send(2,342);
			a = 1;
			printf("ITC Send\n");
		}
		a++;
		msleep(1000);
	}
}

void user_task_3(void){
	int a,b,c;
	a =1;
	b =2;
	c =a+b;
	while(1){
		c = navilnux_itc_get(2);
		printf("TASK3 - a:%p\t b:%p\t c:%p\t\n", &a,&b,&c);
		printf("ITC get c:%d\n",c);
		msleep(1000);
	}
}

void user_task_4(void){
	int a,b,c;
	a =1;
	b =2;
	c =a+b;
	while(1){
		navilnux_sem_p(5);
		printf("TASK4 enter ciritical section semaphore\n");
		printf("TASK4 - a:%p\t b:%p\t c:%p\t\n", &a,&b,&c);
		msleep(2000);
		navilnux_sem_v(5);
		printf("task4 out ciritical section\n");
		msleep(4000);
	}
}

void user_task_5(void){
	int a,b,c;
	a =1;
	b =2;
	c =a+b;
	while(1){
		navilnux_sem_p(5);
		printf("TASK5 enter ciritical section semaphore\n");
		printf("TASK5 - a:%p\t b:%p\t c:%p\t\n", &a,&b,&c);
		msleep(2000);
		navilnux_sem_v(5);
		printf("task5 out ciritical section\n");
		msleep(4000);
	}
}

void user_task_6(void){
	int a,b,c;
	a =1;
	b =2;
	c =a+b;
	while(1){
		navilnux_sem_p(5);
		printf("TASK6 enter ciritical section semaphore\n");
		printf("TASK6 - a:%p\t b:%p\t c:%p\t\n", &a,&b,&c);
		msleep(2000);
		navilnux_sem_v(5);
		printf("task6 out ciritical section\n");
		msleep(4000);
	}
}

void navilnux_user(void){
	taskmng.create(user_task_1);
	taskmng.create(user_task_2);
	taskmng.create(user_task_3);
	taskmng.create(user_task_4);
	taskmng.create(user_task_5);
	taskmng.create(user_task_6);

	msgmng.sem_init(5,2);
}
