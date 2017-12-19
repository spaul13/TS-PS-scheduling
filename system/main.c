/*  main.c  - main */

#include <xinu.h>

uint32 Total_ticks, time1, time2, time3, time4, time5;
pri32 group_priority[2];

void name(void){
	for (int i=0; i<=1000;i++){
		kprintf("\n the value of i = %d \n", i);
		kprintf("info %d %d %d %d\n",currpid,i,proctab[currpid].prprio,preempt);
}
	kprintf("\n my process name is ending here");
	time1=Total_ticks;
	return ;
}

void prename (void){
	int s=0;
	int i=0;
	while(i<=1000){
		s=s+i;
		kprintf("\n we are at the second function\n");
		kprintf("info %d %d %d %d\n",currpid,i,proctab[currpid].prprio,preempt);
		i++;
}
	kprintf("\n my process prename is ending here");
	time2=Total_ticks;
	return ;
}

void dhoni(void){
	int s=10;
	int i=1;
	kprintf("\n we are at the third function\n");
	s=s+i;
	kprintf("info %d %d %d %d\n",currpid,i,proctab[currpid].prprio,preempt);
	kprintf("\n my process dhoni is ending here");
	time3=Total_ticks;
	return ;
}
process cpubound(void)

{

    char a[10] = {0,0,0,0,0,0,0,0,0,0};

    char b[10];

    int i;

    int j;

    for (i = 0; i < 10; i ++){

        for (j = 0; j < 10; j ++){

            memcpy(b,a,10);

        }

        kprintf("info %d %d %d %d\n",currpid,i,proctab[currpid].prprio,preempt);

    }
    time4=Total_ticks;
    kprintf("\n my process cpubound is ending here");
    return OK;

}


process iobound(void)

{

    char a[10] = {0,0,0,0,0,0,0,0,0,0};

    char b[10];

    int i;

    int j;

    for (i = 0; i < 10; i ++){

        for (j = 0; j < 10; j ++){

           sleepms(200);
        }

        kprintf("info %d %d %d %d\n",currpid,i,proctab[currpid].prprio,preempt);

    }
    time5=Total_ticks;
    kprintf("\n my process iobound is ending here");
    return OK;

}

void sample_proc_cpu() {
        int i, j;
        int LOOP1 = 10; 
        int LOOP2 = 10000000;

        struct procent *pr = &proctab[currpid];

        int v = 0;
        for (i=0; i<LOOP1; i++) {
                for (j=0; j<LOOP2; j++) {
                        v += i * j;
                }   
                kprintf("PID: %d, Loop: %d\n", 
                                currpid, i); 
        }   

        kprintf("===== CPU BOUNDED PID %d ends\n", currpid);
}

void sample_proc_io(uint32 time) {
        int i;
        int LOOP1 = 30; 

        struct procent *pr = &proctab[currpid];

        for (i=0; i<LOOP1; i++) {
                sleepms(time);
                kprintf("PID: %d, Sleep time: %d, Loop: %d\n", 
                                currpid, time, i); 
        }   

        kprintf("===== IO BOUNDED PID %d ends\n", currpid);
}


process	main(void)
{
	kprintf("===TS TEST3===\n");
        resched_cntl(DEFER_START);
	for (int i = 0; i < 4; i++) {
                resume(create(sample_proc_cpu, 1024, 0, 25, "cpu-intense", 0, NULL));
        }   
        for (int i = 0; i < 6; i++) {
                if (i % 2 == 0) {
                        resume(create(sample_proc_cpu, 1024, 1, 20, "cpu-intense", 0));
                }
                else {
                        resume(create(sample_proc_io, 1024, 1, 20, "io-intense", 1, 32));
                }
        }
        resched_cntl(DEFER_STOP);
	/*kprintf("\n the priority of the two groups initially are for TS= %5d and for PS= %5d \n", group_priority[1], group_priority[0]);
	kprintf("\n the main is running\n");
	kprintf("\n the main is running\n");
	resume(create(prename, 8192, 1, 20, "siben", 0));
	kprintf("\n the sibendu22 is running\n");
	resume(create(name, 8192, 1, 20, "sibendu",0));
	kprintf("\n the sibendu is running\n");
	resume(create(dhoni, 8192, 1, 20, "dhoni", 0));
	kprintf("\n the dhoni is running\n");
	resume(create(cpubound, 8192, 1, 20, "dhoni1 ", 0));
	kprintf("\n the CPUbound is running\n");
	resume(create(iobound, 8192, 1, 20, "dhoni 2", 0));
	kprintf("\n the IObound is running\n");
	kprintf("\n the time when prename ends =%5d , when name ends =%5d and finally dhoni ends = %5d and CPUbound ends at= %5d, IO bound ends at= %5d", time1, time2, time3, time4, time5);*/
	return OK;
}
    
/*pid32 pidShell=create(shell, 8192, 0, 40, "shell", 1, CONSOLE);
	resume(pidShell);
	qid16 q=newqueue();
	uint64 ret= getticks();
      resume(create(shell, 8192, 50, "shell", 1, CONSOLE)); 
	kprintf("\n \n we are dsnlers %d\n \n and the number of ticks CPU consumed %d and qid is =%d \n\n ",pidShell, ret, q);*/
	/* Wait for shell to exit and recreate it */

/*	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 0, 20, "shell", 1, CONSOLE));
	}*/

