#include<xinu.h>

pid32 currentpid;
pri32 group_priority[2];

/*pid32 select_process(int group_id){
	pri32 priority=0;
	pid32 process_id;
	pid32 pid;
	pid=firstid(readylist); 
	struct procent *pt_process;
	while(queuetab[pid].qnext != NULL){
		pt_process=&proctab[pid]; 
		if (pt_process->group==group_id){
			if (pt_process->prprio > priority){
				priority=pt_process->prprio;
				process_id=pid;}	}
		pid=queuetab[pid].qnext;}

	return process_id;	
	}
*/
void aging(pid32 currpid){
	uint32 PS_count=0;
	uint32 TS_count=0;
	pri32 PS_priority, TS_priority;
	pid32 pid;
	pri32 priority;
	pid=firstid(readylist); /*fetching the first processid in the ready list*/
	struct procent *pt_process;
	pt_process=&proctab[pid]; /*storing the process table corresponding to the pid into the structure pt_process*/
	if (pt_process->group==0){
		PS_count+=1;
	}
	else{
		TS_count+=1;
	}

	while(queuetab[pid].qnext != NULL){ /*traversing the readylist*/
		pid=queuetab[pid].qnext;
		pt_process=&proctab[pid];
		
		if (pt_process->group==0) {
			PS_count+=1;}
		else{
			TS_count+=1;}
	}
	chgprio (0, group_priority[0]+PS_count);
	chgprio (1,group_priority[1]+TS_count); /*in order to change the group priority*/

	PS_priority=group_priority[0];
	TS_priority=group_priority[1];
/*	if (PS_priority > TS_priority)
		currentpid=select_process(0);
	else
		currentpid=select_process(1);
	*/
	return ;
}
